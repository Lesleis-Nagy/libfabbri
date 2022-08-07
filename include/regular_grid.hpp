//
// Created by Lesleis Nagy on 04/08/2022.
//

#ifndef LIBFABBRI_REGULAR_GRID_HPP
#define LIBFABBRI_REGULAR_GRID_HPP

#include <exception>

class RGridElementIndexOutOfRange : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "The element index was out of range.";
    }
};

/**
 * Given a uniformly sampled grid with nx vertices in the x-direction, ny vertices in the y-direction and nz vertices in
 * the z-direction - assuming that the fastest index is z, second fastest is y and slowest index is x (see figure) -
 * this object will, given element indices (i.e. an index of the cuboid with eight vertex indices), return the eight
 * vertex indices associated with the element *in paraview order*.
 * @tparam T the underlying data type for the calculation - this *MUST* be an integral type.
 */
template<typename T>
class RectangularRGridIndexing {
public:

    /**
     * Create a rectangular regular grid indexing object i.e. where element indices represent a cuboid with eight
     * vertex indices.
     * @param nx the number of sample-points in the x direction.
     * @param ny the number of sample-points in the y direction.
     * @param nz the number of sample-points in the z direction.
     */
    RectangularRGridIndexing(T nx, T ny, T nz) : _nx(nx), _ny(ny), _nz(nz),
                                                 _no_of_elements((nx - 1) * (ny - 1) * (nz - 1)) {}

    [[nodiscard]] T nx() const { return _nx; }

    [[nodiscard]] T ny() const { return _ny; }

    [[nodiscard]] T nz() const { return _nz; }

    [[nodiscard]] T no_of_elements() const { return _no_of_elements; }

    void nx(T new_nx) {
        _nx = new_nx;
        update_no_of_elements();
    }

    void ny(T new_ny) {
        _ny = new_ny;
        update_no_of_elements();
    }

    void nz(T new_nz) {
        _nz = new_nz;
        update_no_of_elements();
    }

    /**
     * Retrieve the indices of each vertex for the element with the given input index.
     * @param index the index of the element.
     * @return the eight indices of each corner vertex of the cuboid associate with the `index`-th element.
     */
    std::array<T, 8> operator()(T index) {

        if ((index < 0) || (index >= _no_of_elements)) {
            throw RGridElementIndexOutOfRange();
        }



        T index0 = index + (index / (nz() - 1)) + nz() * (index / ((nz() - 1) * (ny() - 1))) + nz();
        T index1 = index + (index / (nz() - 1)) + nz() * (index / ((nz() - 1) * (ny() - 1)));
        T index2 = index + (index / (nz() - 1)) + nz() * (index / ((nz() - 1) * (ny() - 1))) + nz() * ny();
        T index3 = index + (index / (nz() - 1)) + nz() * (index / ((nz() - 1) * (ny() - 1))) + nz() * ny() + nz();
        T index4 = index + (index / (nz() - 1)) + nz() * (index / ((nz() - 1) * (ny() - 1))) + nz() + 1;
        T index5 = index + (index / (nz() - 1)) + nz() * (index / ((nz() - 1) * (ny() - 1))) + 1;
        T index6 = index + (index / (nz() - 1)) + nz() * (index / ((nz() - 1) * (ny() - 1))) + nz() * ny() + 1;
        T index7 = index + (index / (nz() - 1)) + nz() * (index / ((nz() - 1) * (ny() - 1))) + nz() * ny() + nz() + 1;

        return {index0, index1, index2, index3, index4, index5, index6, index7};

    }

private:

    T _nx;
    T _ny;
    T _nz;
    T _no_of_elements;

    void update_no_of_elements() {

        _no_of_elements = (nx() - 1) * (ny() - 1) * (nz() - 1);

    }

};

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::array<T, 8> &indices) {

    out << "< " << indices[0] << ", "
        << indices[1] << ", "
        << indices[2] << ", "
        << indices[3] << ", "
        << indices[4] << ", "
        << indices[5] << ", "
        << indices[6] << ", "
        << indices[7] << " >";

    return out;

}

#endif //LIBFABBRI_REGULAR_GRID_HPP
