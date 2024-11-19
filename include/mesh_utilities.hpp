//
// Created by Lesleis Nagy on 15/06/2024.
//

#ifndef LIBFABBRI_INCLUDE_MESH_UTILITIES_HPP_
#define LIBFABBRI_INCLUDE_MESH_UTILITIES_HPP_

#include <array>

/**
 * Function to check if a value is contained in a vector of values.
 * @tparam T  the underlying type of the vector.
 * @param value  the value being searched for.
 * @param values the vector of values.
 * @return true if `value` is in `values`, otherwise false.
 */
template<typename T>
bool contains(T value, const std::vector<T> values) {

  return std::any_of(values.cbegin(),
                     values.cend(),
                     [value](const T &v) { return v == value; });

}

/**
 * Function to check if two arrays are equal.
 * @tparam T the underlying type of the vector (must support '=' operator).
 * @tparam N the number of elements in each array.
 * @param a the first array.
 * @param b the second array.
 * @return true if the elements of `a` match the elements of `b`.
 */
template<typename T, size_t N>
bool is_equal(const std::array<T, N> &a,
              const std::array<T, N> &b) {

  for (size_t i = 0; i < N; ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }

  return true;

}

/**
 * Swaps two values.
 * @tparam T the underlying type for the swap.
 * @param i the value that will become `j` after the swap.
 * @param j the value that will become `i` after the swap.
 */
template<typename T>
void swap(T &i, T &j) {

  T tmp = i;
  i = j;
  j = tmp;

}

/**
 * Sort an array of four items.
 * @tparam T the underlying type of the input array.
 * @param list the array to be sorted.
 * @return a sorted version of `list`.
 */
template<typename T>
std::array<T, 4> sort(const std::array<T, 4> &list) {

  auto sorted = list;

  if (sorted[0] > sorted[2]) swap(sorted[0], sorted[2]);
  if (sorted[1] > sorted[3]) swap(sorted[1], sorted[3]);
  if (sorted[0] > sorted[1]) swap(sorted[0], sorted[1]);
  if (sorted[2] > sorted[3]) swap(sorted[2], sorted[3]);
  if (sorted[1] > sorted[2]) swap(sorted[1], sorted[2]);

  return sorted;

}

/**
 * Sort an array of three items.
 * @tparam T the underlying type of the input array.
 * @param list the array to be sorted.
 * @return a sorted version of `list`.
 */
template<typename T>
std::array<T, 3> sort(const std::array<T, 3> &list) {

  auto sorted = list;

  if (sorted[0] > sorted[2]) swap(sorted[0], sorted[2]);
  if (sorted[0] > sorted[1]) swap(sorted[0], sorted[1]);
  if (sorted[1] > sorted[2]) swap(sorted[1], sorted[2]);

  return sorted;

}

/**
 * Sort an array of two items.
 * @tparam T the underlying type of the input array.
 * @param list the array to be sorted.
 * @return a sorted version of `list`.
 */
template<typename T>
std::array<T, 2> sort(const std::array<T, 2> &list) {

  auto sorted = list;

  if (sorted[0] > sorted[1]) swap(sorted[0], sorted[1]);

  return sorted;

}

/**
 * Return a list of faces for the given input tetrahedron.
 * @param tet the input tetrahedron.
 * @return an array of 4 faces.
 */
std::array<std::array<size_t, 3>, 4>
faces(const std::array<size_t, 4> &tet) {

  return {tet[1], tet[2], tet[3],
          tet[0], tet[3], tet[2],
          tet[0], tet[1], tet[3],
          tet[0], tet[2], tet[1]};

}

/**
 * Return a list of edges for the given input tetrahedron.
 * @param tet the input tetrahedron.
 * @return an array of 6 edges.
 */
std::array<std::array<size_t, 2>, 6>
edges(const std::array<size_t, 4> &tet) {

  return {tet[0], tet[1],
          tet[0], tet[2],
          tet[0], tet[3],
          tet[1], tet[2],
          tet[1], tet[3],
          tet[2], tet[3]};

}

#endif //LIBFABBRI_INCLUDE_MESH_UTILITIES_HPP_
