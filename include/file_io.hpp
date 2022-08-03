//
// Created by Lesleis Nagy on 02/08/2022.
//

#ifndef LIBFABBRI_FILE_IO_HPP
#define LIBFABBRI_FILE_IO_HPP

#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <H5Cpp.h>

#include <rapidxml_ext.hpp>

#include "fabbri.hpp"

template <typename T>
void write_h5_file(const std::string &file_root,
                   const std::vector<std::array<T, 3>> &field_vertices,
                   const std::vector<std::array<T, 3>> &field_vectors,
                   const std::array<std::array<T, 3>, 4> &tetra_vert) {

    using std::string;
    using H5::H5File;
    using H5::DataSpace;
    using H5::DataSet;
    using H5::PredType;

    string output_file = file_root + ".h5";
    H5File fout(output_file.c_str(), H5F_ACC_TRUNC);

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

template <typename T>
void write_xdmf2_file(const std::string &file_root,
                      const std::vector<std::array<T, 3>> &field_vertices,
                      const std::vector<std::array<T, 3>> &field_vectors,
                      const std::array<std::array<T, 3>, 4> &tetra_vert) {

    using std::ofstream;
    using std::string;
    using std::stringstream;
    using rapidxml::xml_document;
    using rapidxml::xml_node;
    using rapidxml::node_declaration;
    using rapidxml::node_doctype;
    using rapidxml::node_element;

    xml_document<> doc;

    string hdf5_file_name = file_root + ".h5";

    // XML declaration.
    xml_node<> *declaration = doc.allocate_node(node_declaration);
    declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
    doc.append_node(declaration);

    // XDMF doctype
    xml_node<> *doc_type = doc.allocate_node(node_doctype);
    doc_type->value(R"(Xdmf SYSTEM "Xdmf.dtd" [])");
    doc.append_node(doc_type);

    // The root node.
    xml_node<> *xdmf = doc.allocate_node(node_element, "Xdmf");
    xdmf->append_attribute(doc.allocate_attribute("Version", "3.0"));
    xdmf->append_attribute(doc.allocate_attribute("xmlns:xi", R"(http://www.w3.org/2003/XInclude)"));
    doc.append_node(xdmf);

    // The domain node.
    xml_node<> *domain = doc.allocate_node(node_element, "Domain");
    xdmf->append_node(domain);

    //***************************************************************************************************************//
    //* Tetrahedral grid                                                                                            *//
    //***************************************************************************************************************//

    // The tetrahedron (Grid) node.
    xml_node<> *grid_tetrahedron = doc.allocate_node(node_element, "Grid");
    grid_tetrahedron->append_attribute(doc.allocate_attribute("Name", "tetrahedron"));
    grid_tetrahedron->append_attribute(doc.allocate_attribute("GridType", "Uniform"));
    domain->append_node(grid_tetrahedron);

    // Tetrahedron topology node.
    xml_node<> * topology_tetrahedron = doc.allocate_node(node_element, "Topology");
    topology_tetrahedron->append_attribute(doc.allocate_attribute("TopologyType", "Tetrahedron"));
    topology_tetrahedron->append_attribute(doc.allocate_attribute("NumberOfElements", "1"));
    topology_tetrahedron->append_attribute(doc.allocate_attribute("NodesPerElement", "4"));
    grid_tetrahedron->append_node(topology_tetrahedron);

    // Tetrahedron connectivity data item.
    xml_node<> *di_conn_tetrahedron = doc.allocate_node(node_element, "DataItem");
    di_conn_tetrahedron->append_attribute(doc.allocate_attribute("Dimensions", "1 4"));
    di_conn_tetrahedron->append_attribute(doc.allocate_attribute("Format", "HDF"));
    string di_conn_tetrahedron_h5 = hdf5_file_name + ":/tetrahedron-conn";
    di_conn_tetrahedron->value(di_conn_tetrahedron_h5.c_str());
    topology_tetrahedron->append_node(di_conn_tetrahedron);

    // Tetrahedron geometry node.
    xml_node<> *geometry_tetrahedron = doc.allocate_node(node_element, "Geometry");
    geometry_tetrahedron->append_attribute(doc.allocate_attribute("GeometryType", "XYZ"));
    grid_tetrahedron->append_node(geometry_tetrahedron);

    // Tetrahedron geometry data item.
    xml_node<> *di_geom_tetrahedron = doc.allocate_node(node_element, "DataItem");
    di_geom_tetrahedron->append_attribute(doc.allocate_attribute("Dimensions", "4 3"));
    di_geom_tetrahedron->append_attribute(doc.allocate_attribute("Format", "HDF"));
    string di_geom_tetrahedron_h5 = hdf5_file_name + ":/tetrahedron-vert";
    di_geom_tetrahedron->value(di_geom_tetrahedron_h5.c_str());
    geometry_tetrahedron->append_node(di_geom_tetrahedron);

    //***************************************************************************************************************//
    //* Vector field regular grid.                                                                                  *//
    //***************************************************************************************************************//

    // The tetrahedron (Grid) node.
    xml_node<> *grid_field = doc.allocate_node(node_element, "");
    grid_field->append_attribute(doc.allocate_attribute("Name", "grid"));
    grid_field->append_attribute(doc.allocate_attribute("GridType", "Uniform"));
    domain->append_node(grid_field);

    string output_file = file_root + ".xdmf";
    ofstream fout(output_file);
    fout << doc;
    fout.close();

}

#endif //LIBFABBRI_FILE_IO_HPP
