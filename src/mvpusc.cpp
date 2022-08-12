//
// Created by Lesleis Nagy on 01/08/22.
//

/**
 * The magnetic vector potential for uniform sources calculator or `mvpusc` is able to calculate the magnetic vector
 * potential at any point in space.
 */


#include <optional>
#include <regex>
#include <sstream>
#include <string>

#include <ncurses.h>

#include "fabbri.hpp"
#include "table.hpp"
#include "file_io.hpp"
#include "regular_grid.hpp"

using RealType = double;
using IntegralType = unsigned long;

class RealTypeValidator {

public:
    RealTypeValidator(): _re_real(R"(^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$)") {}

    bool validate(const std::string &str) {

        using std::cmatch;
        using std::regex_match;

        cmatch match;
        if (regex_match(str.c_str(), match, _re_real)) {
            return true;
        } else {
            return false;
        }

    }

    bool validate(const char *str) {

        using std::cmatch;
        using std::regex_match;

        cmatch match;
        if (regex_match(str, match, _re_real)) {
            return true;
        } else {
            return false;
        }

    }

private:

    std::regex _re_real;

};

void display_help_message() {

    mvprintw(0, 0, "This is the magnetic vector-potential (for) uniform sources calculator (mvpusc)");
    mvprintw(1, 0, "Controls: <q>          - quit");
    mvprintw(2, 0, "          <e>          - edit");
    mvprintw(3, 0, "          <c>          - compute and write output file");
    mvprintw(4, 0, "          <t>          - toggle edit table");
    mvprintw(5, 0, "          <arrow keys> - select value in edit table");

}

void display_model_table(int highlight_row, int highlight_col, const Table<RealType, 5, 3> &model_inputs,
                         bool is_active=false, int row_offset=0) {

    using std::array;
    using std::string;

    // Print table title.
    mvprintw(row_offset, 0, "Model input parameters");

    array<int, 6> row_positions = {1 + row_offset, 2 + row_offset, 3 + row_offset,
                                   4 + row_offset, 5 + row_offset, 6 + row_offset};
    array<int, 4> col_positions = {0, 20, 40, 60};
    array<string, 6> row_names = {"", "mag", "r1", "r2", "r3", "r4"};

    const char *col_str_format = "%-20s";

    mvprintw(row_positions[0], col_positions[1], col_str_format, "x-component");
    mvprintw(row_positions[0], col_positions[2], col_str_format, "y-component");
    mvprintw(row_positions[0], col_positions[3], col_str_format, "z-component");

    for (int row_idx = 1; row_idx < row_positions.size(); ++row_idx) {

        for (int col_idx = 0; col_idx < col_positions.size(); ++col_idx) {

            if (col_idx == 0) {
                // this is the first column, so we display the row name.
                mvprintw(row_positions[row_idx], col_positions[col_idx], row_names[row_idx].c_str());
            } else {

                if ((highlight_row == row_idx-1) && (highlight_col == col_idx-1) && is_active)
                    attron(A_REVERSE);
                if (model_inputs.display_data(row_idx - 1, col_idx - 1).has_value())
                    mvprintw(row_positions[row_idx], col_positions[col_idx], col_str_format, model_inputs.display_data(row_idx - 1, col_idx - 1).value().c_str());
                else
                    mvprintw(row_positions[row_idx], col_positions[col_idx], col_str_format, "<empty>");
                attroff(A_REVERSE);

            }

        }

    }

}

void display_sample_grid_table(int highlight_row, int highlight_col, const Table<RealType, 3, 3> &sampling_table,
                               bool is_active=false, int row_offset=0) {

    using std::array;
    using std::string;

    // Print table title.
    mvprintw(row_offset, 0, "Sample grid parameters");

    array<int, 4> row_positions = {1 + row_offset, 2 + row_offset, 3 + row_offset, 4 + row_offset};
    array<int, 4> col_positions = {0, 20, 40, 60};
    array<string, 6> row_names = {"", "x-sample", "y-sample", "z-sample"};

    const char *col_str_format = "%-20s";

    mvprintw(row_positions[0], col_positions[1], col_str_format, "minimum");
    mvprintw(row_positions[0], col_positions[2], col_str_format, "maximum");
    mvprintw(row_positions[0], col_positions[3], col_str_format, "no. of samples");

    for (int row_idx = 1; row_idx < row_positions.size(); ++row_idx) {

        for (int col_idx = 0; col_idx < col_positions.size(); ++col_idx) {

            if (col_idx == 0) {
                // this is the first column, so we display the row name.
                mvprintw(row_positions[row_idx], col_positions[col_idx], row_names[row_idx].c_str());
            } else {

                if ((highlight_row == row_idx-1) && (highlight_col == col_idx-1) && is_active)
                    attron(A_REVERSE);
                if (sampling_table.display_data(row_idx - 1, col_idx - 1).has_value())
                    mvprintw(row_positions[row_idx], col_positions[col_idx],
                             col_str_format, sampling_table.display_data(row_idx - 1, col_idx - 1).value().c_str());
                else
                    mvprintw(row_positions[row_idx], col_positions[col_idx], col_str_format, "<empty>");
                attroff(A_REVERSE);

            }

        }

    }

}

void display_message(const char *message) {

    int row_max, col_max;
    getmaxyx(stdscr, row_max, col_max);

    mvprintw(row_max-1,  0, "message: %s", message);

}

template <typename T>
void edit_model_table_value(int highlight_row, int highlight_col, T &table) {

    using std::istringstream;
    using std::stringstream;

    static RealTypeValidator real_type_validator;

    WINDOW *win_edit = newwin(5, 50, 10, 10);
    box(win_edit, 0, 0);
    mvwprintw(win_edit, 2, 2, "Value:");
    wmove(win_edit, 2, 9);

    wrefresh(win_edit);

    char str_input[1024];
    echo();
    wgetstr(win_edit, str_input);
    if (real_type_validator.validate(str_input)) {
        RealType input;
        std::istringstream(str_input) >> input;
        table.set_data(highlight_row, highlight_col, input);
        display_message("Updated table value.");
    } else {
        stringstream ss;
        ss << "Format error in input value: '" << str_input << "'.";
        display_message(ss.str().c_str());
    }
    noecho();

    werase(win_edit);
    wrefresh(win_edit);
    delwin(win_edit);

}

std::string get_output_file() {

    using std::string;

    WINDOW *win_output = newwin(5, 50, 10, 10);
    box(win_output, 0, 0);
    mvwprintw(win_output, 2, 2, "Output:");
    wmove(win_output, 2, 10);

    wrefresh(win_output);

    char input[1024];
    echo();
    wgetstr(win_output, input);
    noecho();

    werase(win_output);
    wrefresh(win_output);
    delwin(win_output);

    return {input};

}

void perform_calculation(Table<RealType, 3, 3> &sample_grid_table,
                         Table<RealType, 5, 3> &model_table) {

    using std::array;
    using std::string;
    using std::vector;

    string output_file = get_output_file();

    RealType start_x = sample_grid_table.data(0, 0).value();
    RealType end_x = sample_grid_table.data(0, 1).value();
    RealType n_x = sample_grid_table.data(0, 2).value();

    RealType start_y = sample_grid_table.data(1, 0).value();
    RealType end_y = sample_grid_table.data(1, 1).value();
    RealType n_y = sample_grid_table.data(1, 2).value();

    RealType start_z = sample_grid_table.data(2, 0).value();
    RealType end_z = sample_grid_table.data(2, 1).value();
    RealType n_z = sample_grid_table.data(2, 2).value();


    Vector3D<RealType> m(model_table.data(0, 0).value(),
                         model_table.data(0, 1).value(),
                         model_table.data(0, 2).value());

    Vector3D<RealType> r1(model_table.data(1, 0).value(),
                          model_table.data(1, 1).value(),
                          model_table.data(1, 2).value());

    Vector3D<RealType> r2(model_table.data(2, 0).value(),
                          model_table.data(2, 1).value(),
                          model_table.data(2, 2).value());

    Vector3D<RealType> r3(model_table.data(3, 0).value(),
                          model_table.data(3, 1).value(),
                          model_table.data(3, 2).value());

    Vector3D<RealType> r4(model_table.data(4, 0).value(),
                          model_table.data(4, 1).value(),
                          model_table.data(4, 2).value());

    array<array<RealType, 3>, 4> tetrahedron = {{
                                                        {{r1.x(), r1.y(), r1.z()}},
                                                        {{r2.x(), r2.y(), r2.z()}},
                                                        {{r3.x(), r3.y(), r3.z()}},
                                                        {{r4.x(), r4.y(), r4.z()}}
                                                }};

    RealType dx = (end_x - start_x) / (n_x - 1.0);
    RealType dy = (end_y - start_y) / (n_y - 1.0);
    RealType dz = (end_z - start_z) / (n_z - 1.0);

    auto A_fun = new_uni_tet_A_fun(m, r1, r2, r3, r4);
    auto B_fun = new_uni_tet_B_fun(m, r1, r2, r3, r4);

    std::vector<std::array<RealType, 3>> field_vertices;
    std::vector<std::array<IntegralType, 8>> field_connect;
    std::vector<std::array<RealType, 3>> A_field_vectors;
    std::vector<std::array<RealType, 3>> B_field_vectors;
    RectangularRGridIndexing<IntegralType> grid_connect((IntegralType)n_x, (IntegralType)n_y, (IntegralType)n_z);
    for (int i = 0; i < (int)n_x; ++i) {

        for (int j = 0; j < (int)n_y; ++j) {

            for (int k = 0; k < (int)n_z; ++k) {

                Vector3D<RealType> r(start_x + (RealType)i * dx,
                                     start_y + (RealType)j * dy,
                                     start_z + (RealType)k * dz);
                auto A = A_fun(r);
                auto B = B_fun(r);

                field_vertices.push_back({r.x(), r.y(), r.z()});
                A_field_vectors.push_back({A.x(), A.y(), A.z()});
                B_field_vectors.push_back({B.x(), B.y(), B.z()});

            }

        }

    }

    for (IntegralType i = 0; i < grid_connect.no_of_elements(); ++i) {
        field_connect.push_back(grid_connect(i));
    }

    H5Writer<RealType, IntegralType> file_writer;
    file_writer.write(output_file, field_vertices, field_connect, A_field_vectors, B_field_vectors, tetrahedron);

    display_message("Data written.");

}

enum ActiveTable {
    MODEL_TABLE, SAMPLE_GRID_TABLE
};

void set_default_model_table_values(Table<RealType, 5, 3> &model_table) {

    // Magnetisation.
    model_table.set_data(0, 0, 1.0);
    model_table.set_data(0, 1, 0.0);
    model_table.set_data(0, 2, 0.0);

    // r1
    model_table.set_data(1, 0, 0.0);
    model_table.set_data(1, 1, 0.0);
    model_table.set_data(1, 2, 0.0);

    // r2
    model_table.set_data(2, 0, 1.0);
    model_table.set_data(2, 1, 0.0);
    model_table.set_data(2, 2, 0.0);

    // r3
    model_table.set_data(3, 0, 0.0);
    model_table.set_data(3, 1, 1.0);
    model_table.set_data(3, 2, 0.0);

    // r3
    model_table.set_data(4, 0, 0.0);
    model_table.set_data(4, 1, 0.0);
    model_table.set_data(4, 2, 1.0);

}


void set_default_grid_table_values(Table<RealType, 3, 3> &sample_grid_table) {

    sample_grid_table.set_data(0, 0, -1.0);
    sample_grid_table.set_data(0, 1,  1.0);
    sample_grid_table.set_data(0, 2,  10);

    sample_grid_table.set_data(1, 0, -1.0);
    sample_grid_table.set_data(1, 1,  1.0);
    sample_grid_table.set_data(1, 2,  10);

    sample_grid_table.set_data(2, 0, -1.0);
    sample_grid_table.set_data(2, 1,  1.0);
    sample_grid_table.set_data(2, 2,  10);

}

int main(int argc, char *argv[]) {

    using namespace std;

    using mpfr::mpreal;
    const int digits = 50;
    mpreal::set_default_prec(mpfr::digits2bits(digits));

    initscr();
    cbreak();
    noecho();

    Table<RealType, 5, 3> model_table;
    Table<RealType, 3, 3> sample_grid_table;

    set_default_model_table_values(model_table);
    set_default_grid_table_values(sample_grid_table);

    int model_table_highlight_row = 0, model_table_highlight_col = 0;
    int sample_grid_table_highlight_row = 0, sample_grid_table_highlight_col = 0;

    keypad(stdscr, TRUE);

    ActiveTable active_table = MODEL_TABLE;

    display_message("");
    bool loop = true;
    while(loop) {

        display_help_message();

        switch (active_table) {
            case MODEL_TABLE:
                display_model_table(model_table_highlight_row, model_table_highlight_col, model_table, true, 7);
                display_sample_grid_table(sample_grid_table_highlight_row, sample_grid_table_highlight_col,
                                          sample_grid_table, false, 15);
                break;
            case SAMPLE_GRID_TABLE:
                display_model_table(model_table_highlight_row, model_table_highlight_col, model_table, false, 7);
                display_sample_grid_table(sample_grid_table_highlight_row, sample_grid_table_highlight_col,
                                          sample_grid_table, true, 15);
                break;
        }

        int choice = getch();

        switch (choice) {

            case (int)'k':
            case KEY_UP:
                switch (active_table) {
                    case MODEL_TABLE:
                        model_table_highlight_row--;
                        if (model_table_highlight_row < 0)
                            model_table_highlight_row = 0;
                        break;
                    case SAMPLE_GRID_TABLE:
                        sample_grid_table_highlight_row--;
                        if (sample_grid_table_highlight_row < 0)
                            sample_grid_table_highlight_row = 0;
                        break;
                }
                break;

            case (int)'j':
            case KEY_DOWN:
                switch (active_table) {
                    case MODEL_TABLE:
                        model_table_highlight_row++;
                        if (model_table_highlight_row >= model_table.n_rows())
                            model_table_highlight_row = model_table.n_rows() - 1;
                        break;
                    case SAMPLE_GRID_TABLE:
                        sample_grid_table_highlight_row++;
                        if (sample_grid_table_highlight_row >= sample_grid_table.n_rows())
                            sample_grid_table_highlight_row = sample_grid_table.n_rows() - 1;
                        break;
                }
                break;

            case (int)'h':
            case KEY_LEFT:
                switch (active_table) {
                    case MODEL_TABLE:
                        model_table_highlight_col--;
                        if (model_table_highlight_col < 0)
                            model_table_highlight_col = 0;
                        break;
                    case SAMPLE_GRID_TABLE:
                        sample_grid_table_highlight_col--;
                        if (sample_grid_table_highlight_col < 0)
                            sample_grid_table_highlight_col = 0;
                        break;
                }
                break;

            case (int)'l':
            case KEY_RIGHT:
                switch (active_table) {
                    case MODEL_TABLE:
                        model_table_highlight_col++;
                        if (model_table_highlight_col > 2)
                            model_table_highlight_col = 2;
                        break;
                    case SAMPLE_GRID_TABLE:
                        sample_grid_table_highlight_col++;
                        if (sample_grid_table_highlight_col >= sample_grid_table.n_cols())
                            sample_grid_table_highlight_col = sample_grid_table.n_cols() - 1;
                        break;
                }
                break;

            case (int)'e':
                switch (active_table) {
                    case MODEL_TABLE:
                        edit_model_table_value(model_table_highlight_row, model_table_highlight_col, model_table);
                        break;
                    case SAMPLE_GRID_TABLE:
                        edit_model_table_value(sample_grid_table_highlight_row, sample_grid_table_highlight_col,
                                               sample_grid_table);
                        break;
                }
                refresh();
                break;

            case (int)'t':
                switch (active_table) {
                    case MODEL_TABLE:
                        active_table = SAMPLE_GRID_TABLE;
                        break;
                    case SAMPLE_GRID_TABLE:
                        active_table = MODEL_TABLE;
                        break;
                }
                break;

            case (int)'q':
                loop = false;
                break;

            case (int)'c':
                perform_calculation(sample_grid_table, model_table);
                break;

            default:
                break;
        }
    }

    endwin();

}