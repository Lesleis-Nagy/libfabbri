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

/**
 * Exception thrown when a table row index is out of range.
 */
class RowIndexOutOfRange : public std::exception {
 public:
  /**
   * Retrieve the exception error message.
   * @return the exception error message.
   */
  [[nodiscard]] const char *what() const noexcept override {
    return "Row index out of range.";
  }
};

/**
 * Exception thrown when a table column index is out of range.
 */
class ColumnIndexOutOfRange : public std::exception {
 public:
  /**
   * Retrieve the exception error message.
   * @return the exception error message.
   */
  [[nodiscard]] const char *what() const noexcept override {
    return "Column index out of range.";
  }
};

/**
 * A table object that can be used to display tabular data.
 * @tparam T the underlying data type for a numerical column.
 * @tparam _n_rows  the number of table rows.
 * @tparam _n_cols  the number of table columns.
 * @tparam _precision the display precision of each number.
 * @tparam _scientific a boolean to indicate whether scientific notation will
 *                     be used.
 */
template<typename T, int _n_rows, int _n_cols, int _precision = 18, bool _scientific = false>
class Table {
 public:

  Table() = default;

  /**
   * Retrieve the data in a cell at index i, j as a string.
   * @param i the row index of the cell.
   * @param j the column index of the cell.
   * @return the data at row i, column j as a string.
   */
  [[nodiscard]] const std::optional<std::string> &
  display_data(int i, int j) const {

    check_range(i, j);
    return _display_data[i][j];

  }

  /**
   * Retrieve the data in a cell at index i, j.
   * @param i the row index of the cell.
   * @param j the column index of the cell.
   * @return the data at row i, column j.
   */
  [[nodiscard]] const std::optional<T> &
  data(int i, int j) const {

    check_range(i, j);
    return _data[i][j];

  }

  /**
   * Retrieve the number of rows in the table.
   * @return the number of rows in the table.
   */
  [[nodiscard]] int
  n_rows() const {

    return _n_rows;

  }

  /**
   * Retrieve the number of columns in the table.
   * @return the number of columns in the table.
   */
  [[nodiscard]] int n_cols() const {

    return _n_cols;

  }

  /**
   * Set the data for the cell with row i, column j.
   * @param i the row index.
   * @param j the column index.
   * @param v the value.
   */
  void
  set_data(int i, int j, T v) {

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

  std::array<std::array<std::optional<std::string>, _n_cols>, _n_rows> _display_data;
  std::array<std::array<std::optional<T>, _n_cols>, _n_rows> _data;

  /**
   * Check whether two indices are within the table.
   * @param i the row index of the table.
   * @param j the column index of the table.
   */
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
