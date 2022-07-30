#include <iostream>
#include <string>
#include <vector>

#include <H5Cpp.h>


template <typename T>
class Array1D {
public:

    Array1D():
        _nrows(1), _values(1) {}

    Array1D(size_t nrows): 
        _nrows(nrows), _values(nrows) {}

    T &operator () (size_t i) {

        return _values[i];

    }

    T &get(size_t i) {

        return _values[i];

    }

    const T &get(size_t i) const {

        return _values[i];

    }

    const T &operator () (size_t i) const {

        return _values[i];

    }

    size_t nrows() const {

        return _nrows;

    }

    T *data() {

        return _values.data();

    }

    void resize(int nrows) {

        _values.resize(nrows);
        _nrows = nrows;

    }

private:

    size_t _nrows;
    
    std::vector<T> _values;

};


template <typename T>
class Array2D {
public:

    Array2D(): _nrows(1), _ncols(1), _values(1) {}

    Array2D(size_t nrows, size_t ncols): _nrows(nrows), _ncols(ncols), _values(nrows*ncols) {}


    T &operator () (size_t i, size_t j) {

        return _values[i * _ncols + j];

    }

    T &get(size_t i, size_t j) {

        return _values[i * _ncols + j];

    }

    const T &get(size_t i, size_t j) const {

        return _values[i * _ncols + j];

    }

    const T &operator () (size_t i, size_t j) const {

        return _values[i * _ncols + j];

    }

    size_t nrows() const {

        return _nrows;

    }

    size_t ncols() const {

        return _ncols; 

    }

    T *data() { 

        return _values.data(); 

    }

    void resize(size_t nrows, size_t ncols) {

        _values.resize(nrows*ncols);
        _nrows = nrows;
        _ncols = ncols;

    }

private:

    size_t _nrows;
    size_t _ncols;

    std::vector<T> _values;

};

std::ostream &operator << (std::ostream &sout, const Array2D<double> &a2d) {
    using namespace std;

    for (size_t i = 0; i < a2d.nrows(); ++i) {
        for (size_t j = 0; j < a2d.ncols(); ++j) {
            if (j != a2d.ncols() - 1) {
                sout << a2d(i, j) << ", ";
            } else {
                sout << a2d(i, j);
            }
        }
        sout << endl;
    }

    return sout;

}



class TestData2D {
public:
    
    TestData2D(const std::string &file_name) {

        using namespace std;
        using namespace H5;

        // Open the specified file and the specified dataset in the file.
        H5File fp(file_name.c_str(), H5F_ACC_RDONLY);

        read_data(fp, "/x", _x);
        read_data(fp, "/y", _y);
        read_data(fp, "/z", _z);

        fp.close();

    }

    const Array2D<double> &x() const { 

        return _x;

    }

    const Array2D<double> &y() const {

        return _y;

    }

    const Array2D<double> &z() const {

        return _z;

    }

private:

    void read_data(H5::H5File fp, 
                   const std::string &data_set_path, 
                   Array2D<double> &arr) {
        using namespace std;
        using namespace H5;

        // Access the required data set by path name.
        DataSet dset = fp.openDataSet(data_set_path.c_str());

        // Get the dataspace.
        DataSpace dspace = dset.getSpace();

        // Get the size of the data set.
        hsize_t rank;
        hsize_t dims[2];

        rank = dspace.getSimpleExtentDims(dims, NULL);

        DataSpace memspace(rank, dims);

        arr.resize(dims[0], dims[1]);
        dset.read(arr.data(), PredType::NATIVE_DOUBLE, memspace, dspace);

    }

    Array2D<double> _x;
    Array2D<double> _y;
    Array2D<double> _z;

};


std::ostream &operator << (std::ostream &sout, const TestData2D &data) {
    using namespace std;

    sout << "x:" << endl;
    sout << data.x();
    
    sout << "y:" << endl;
    sout << data.y();

    sout << "z:" << endl;
    sout << data.z();

    return sout;

}
