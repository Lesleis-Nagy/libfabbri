//
// Created by Lesleis Nagy on 02/08/2022.
//

#ifndef LIBFABBRI_FILE_IO_HPP
#define LIBFABBRI_FILE_IO_HPP

#include <array>
#include <string>
#include <vector>

#include <H5Cpp.h>

#include "fabbri.hpp"

template <typename T>
void write_h5_file(const std::string &file_name,
                   const std::vector<std::array<T, 3>> &field_vertices,
                   const std::vector<std::array<T, 3>> &field_vectors,
                   const std::array<std::array<T, 3>, 4> &tetra_vert) {

   using H5::H5File;
   using H5::DataSpace;
   using H5::DataSet;
   using H5::PredType;

   H5File fout(file_name.c_str(), H5F_ACC_TRUNC);

   hsize_t field_dims[2] = {field_vertices.size(), 3};
   DataSpace dsp_field(2, field_dims);

   hsize_t tetra_vert_dims[2] = {4, 3};
   hsize_t tetra_conn_dims[2] = {1, 4};
   DataSpace dsp_tetra_vert_dims(2, tetra_vert_dims);
   DataSpace dsp_tetra_conn_dims(2, tetra_conn_dims);
   const std::array<std::array<int, 4>, 1> tetra_conn = {{0, 1, 2, 3}};

   // Write the field vertices.
   DataSet ds_vertices = fout.createDataSet("field-vertices", PredType::NATIVE_DOUBLE, dsp_field);
   ds_vertices.write(field_vertices.data(), PredType::NATIVE_DOUBLE);

   // Write the field vectors.
   DataSet ds_vectors = fout.createDataSet("field-vectors", PredType::NATIVE_DOUBLE, dsp_field);
   ds_vectors.write(field_vectors.data(), PredType::NATIVE_DOUBLE);

   // Write the tetrahedron.
   DataSet ds_tetra_vert = fout.createDataSet("tetrahedron-vert", PredType::NATIVE_DOUBLE, dsp_tetra_vert_dims);
   DataSet ds_tetra_conn = fout.createDataSet("tetrahedron-conn", PredType::NATIVE_UINT64, dsp_tetra_conn_dims);
   ds_tetra_vert.write(tetra_vert.data(), PredType::NATIVE_DOUBLE);
   ds_tetra_conn.write(tetra_conn.data(), PredType::NATIVE_INT);

   fout.close();

}

#endif //LIBFABBRI_FILE_IO_HPP
