//
// Created by Lesleis Nagy on 02/08/2022.
//

/** @file */

#ifndef LIBFABBRI_TABLE_HPP
#define LIBFABBRI_TABLE_HPP

#include <array>
#include <exception>
#include <optional>
#include <string>
#include <sstream>

class RowIndexOutOfRange : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Row index out of range.";
    }
};

class ColumnIndexOutOfRange : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Column index out of range.";
    }
};

template <typename T, int _n_rows, int _n_cols, int _precision=18, bool _scientific=false>
class Table {
public:

    Table() = default;

    [[nodiscard]] const std::optional<std::string> &display_data(int i, int j) const {

        check_range(i, j);
        return _display_data[i][j];

    }

    [[nodiscard]] const std::optional<T> &data(int i, int j) const {

        check_range(i, j);
        return _data[i][j];

    }

    [[nodiscard]] int n_rows() const {

        return _n_rows;

    }

    [[nodiscard]] int n_cols() const {

        return _n_cols;

    }

    void set_data(int i, int j, T v) {

        using std::stringstream;

        check_range(i, j);

        stringstream ss;
        ss.precision(_precision);
        ss << v;

        _display_data[i][j] = ss.str();
        _data[i][j] = v;

    }

private:

    std::string _real_format;
    std::string _str_format;
    std::string _int_format;

    std::array< std::array<std::optional<std::string>, _n_cols>, _n_rows > _display_data;
    std::array< std::array<std::optional<T>, _n_cols>, _n_rows > _data;

    inline void check_range(int i, int j) const {
        if ((i < 0) || (i >= _n_rows)) {
            throw RowIndexOutOfRange();
        }
        if ((j < 0) || (j >= _n_cols)) {
            throw ColumnIndexOutOfRange();
        }
    }

};

#endif //LIBFABBRI_TABLE_HPP
