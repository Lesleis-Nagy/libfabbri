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

template<typename RealType, typename IntegralType>
class H5Writer {

public:

    H5Writer() : _nodes_per_element("8"), _cartesian_vector_components("3") {}

    void write(const std::string &file_root,
               const std::vector<std::array<RealType, 3>> &field_vertices,
               const std::vector<std::array<IntegralType, 8>> &field_connect,
               const std::vector<std::array<RealType, 3>> &A_field_vectors,
               const std::vector<std::array<RealType, 3>> &B_field_vectors,
               const std::array<std::array<RealType, 3>, 4> &tetra_vert) {

        _hdf_file_name = file_root + ".h5";
        _xdmf_file_name = file_root + ".xdmf";

        _hdf_tetrahedron_connect_path = _hdf_file_name + ":/tetrahedron/connect";
        _hdf_tetrahedron_vertices_path = _hdf_file_name + ":/tetrahedron/vertices";

        _hdf_field_grid_connect_size = std::to_string(field_connect.size());
        _hdf_field_grid_connect_path = _hdf_file_name + ":/field/grid/connect";
        _hdf_field_grid_connect_dims = std::to_string(field_connect.size()) + " " + _nodes_per_element;

        _hdf_field_grid_vertices_path = _hdf_file_name + ":/field/grid/vertices";
        _hdf_field_grid_vertices_dims = std::to_string(field_vertices.size()) + " " + _cartesian_vector_components;

        _hdf_A_field_vectors_path = _hdf_file_name + ":/field/A-vectors/0";
        _hdf_A_field_vectors_dims = std::to_string(A_field_vectors.size()) + " " + _cartesian_vector_components;

        _hdf_B_field_vectors_path = _hdf_file_name + ":/field/B-vectors/0";
        _hdf_B_field_vectors_dims = std::to_string(B_field_vectors.size()) + " " + _cartesian_vector_components;

        write_h5_file(field_vertices, field_connect, A_field_vectors, B_field_vectors, tetra_vert);
        write_xdmf2_file();

    }

private:

    std::string _nodes_per_element;
    std::string _cartesian_vector_components;
    std::string _hdf_file_name;
    std::string _xdmf_file_name;
    std::string _hdf_tetrahedron_connect_path;
    std::string _hdf_tetrahedron_vertices_path;

    std::string _hdf_field_grid_connect_size;
    std::string _hdf_field_grid_connect_path;
    std::string _hdf_field_grid_connect_dims;
    std::string _hdf_field_grid_vertices_path;
    std::string _hdf_field_grid_vertices_dims;
    std::string _hdf_A_field_vectors_path;
    std::string _hdf_A_field_vectors_dims;
    std::string _hdf_B_field_vectors_path;
    std::string _hdf_B_field_vectors_dims;

    void write_h5_file(const std::vector<std::array<RealType, 3>> &field_vertices,
                       const std::vector<std::array<IntegralType, 8>> &field_connect,
                       const std::vector<std::array<RealType, 3>> &A_field_vectors,
                       const std::vector<std::array<RealType, 3>> &B_field_vectors,
                       const std::array<std::array<RealType, 3>, 4> &tetra_vert) {

        using std::string;
        using H5::H5File;
        using H5::DataSpace;
        using H5::DataSet;
        using H5::Group;
        using H5::PredType;

        H5File fout(_hdf_file_name.c_str(), H5F_ACC_TRUNC);

        hsize_t field_dims[2] = {field_vertices.size(), 3};
        hsize_t conn_dims[2] = {field_connect.size(), 8};
        DataSpace dsp_field(2, field_dims);
        DataSpace dsp_conn(2, conn_dims);

        hsize_t tetra_vert_dims[2] = {4, 3};
        hsize_t tetra_conn_dims[2] = {1, 4};
        DataSpace dsp_tetra_vert_dims(2, tetra_vert_dims);
        DataSpace dsp_tetra_conn_dims(2, tetra_conn_dims);
        const std::array<std::array<int, 4>, 1> tetra_conn = {{0, 1, 2, 3}};

        // Write the field vertices.
        Group grp_field = fout.createGroup("field");
        Group grp_grid = grp_field.createGroup("grid");

        DataSet ds_vertices = grp_grid.createDataSet("vertices", PredType::NATIVE_DOUBLE, dsp_field);
        ds_vertices.write(field_vertices.data(), PredType::NATIVE_DOUBLE);

        DataSet ds_connect = grp_grid.createDataSet("connect", PredType::NATIVE_INT, dsp_conn);
        ds_connect.write(field_connect.data(), PredType::NATIVE_UINT64);

        // Write the field vectors.
        Group grp_A_vectors = grp_field.createGroup("A-vectors");
        DataSet ds_A_vectors = grp_A_vectors.createDataSet("0", PredType::NATIVE_DOUBLE, dsp_field);
        ds_A_vectors.write(A_field_vectors.data(), PredType::NATIVE_DOUBLE);

        Group grp_B_vectors = grp_field.createGroup("B-vectors");
        DataSet ds_B_vectors = grp_B_vectors.createDataSet("0", PredType::NATIVE_DOUBLE, dsp_field);
        ds_B_vectors.write(B_field_vectors.data(), PredType::NATIVE_DOUBLE);

        // Write the tetrahedron.
        Group grp_tetrahedron = fout.createGroup("tetrahedron");
        DataSet ds_tetra_vert = grp_tetrahedron.createDataSet("vertices", PredType::NATIVE_DOUBLE, dsp_tetra_vert_dims);
        DataSet ds_tetra_conn = grp_tetrahedron.createDataSet("connect", PredType::NATIVE_UINT64, dsp_tetra_conn_dims);
        ds_tetra_vert.write(tetra_vert.data(), PredType::NATIVE_DOUBLE);
        ds_tetra_conn.write(tetra_conn.data(), PredType::NATIVE_INT);

        fout.close();

    }

    void write_xdmf2_file() {

        using std::ofstream;
        using std::string;
        using std::stringstream;
        using rapidxml::xml_document;
        using rapidxml::xml_node;
        using rapidxml::node_declaration;
        using rapidxml::node_doctype;
        using rapidxml::node_element;

        xml_document<> doc;

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

        string A_field_name = "A";
        string B_field_name = "B";
        xml_node<> *tetrahedron_node = tetrahedron_grid(doc);
        xml_node<> *field_grid_node = field_grid(doc);
        xml_node<> *A_field_vectors_node = field_vectors(doc, A_field_name, _hdf_A_field_vectors_dims,
                                                         _hdf_A_field_vectors_path);
        xml_node<> *B_field_vectors_node = field_vectors(doc, B_field_name, _hdf_B_field_vectors_dims,
                                                         _hdf_B_field_vectors_path);

        domain->append_node(tetrahedron_node);
        domain->append_node(field_grid_node);
        domain->append_node(A_field_vectors_node);
        domain->append_node(B_field_vectors_node);

        ofstream fout(_xdmf_file_name);
        fout << doc;
        fout.close();

    }

    rapidxml::xml_node<> *tetrahedron_grid(rapidxml::xml_document<> &doc) {

        using std::string;
        using rapidxml::xml_node;
        using rapidxml::node_element;

        // The tetrahedron (Grid) node.
        xml_node<> *grid_node = doc.allocate_node(node_element, "Grid");
        grid_node->append_attribute(doc.allocate_attribute("Name", "tetrahedron"));
        grid_node->append_attribute(doc.allocate_attribute("GridType", "Uniform"));

        // Tetrahedron topology node.
        xml_node<> *topology_node = doc.allocate_node(node_element, "Topology");
        topology_node->append_attribute(doc.allocate_attribute("TopologyType", "Tetrahedron"));
        topology_node->append_attribute(doc.allocate_attribute("NumberOfElements", "1"));
        topology_node->append_attribute(doc.allocate_attribute("NodesPerElement", "4"));
        grid_node->append_node(topology_node);

        // Tetrahedron connectivity data item.
        xml_node<> *connect_data_item_node = doc.allocate_node(node_element, "DataItem");
        connect_data_item_node->append_attribute(doc.allocate_attribute("Dimensions", "1 4"));
        connect_data_item_node->append_attribute(doc.allocate_attribute("Format", "HDF"));
        connect_data_item_node->value(_hdf_tetrahedron_connect_path.c_str());
        topology_node->append_node(connect_data_item_node);

        // Tetrahedron geometry node.
        xml_node<> *geometry_node = doc.allocate_node(node_element, "Geometry");
        geometry_node->append_attribute(doc.allocate_attribute("GeometryType", "XYZ"));
        grid_node->append_node(geometry_node);

        // Tetrahedron geometry data item.
        xml_node<> *geometry_data_item_node = doc.allocate_node(node_element, "DataItem");
        geometry_data_item_node->append_attribute(doc.allocate_attribute("Dimensions", "4 3"));
        geometry_data_item_node->append_attribute(doc.allocate_attribute("Format", "HDF"));
        geometry_data_item_node->value(_hdf_tetrahedron_vertices_path.c_str());
        geometry_node->append_node(geometry_data_item_node);

        return grid_node;

    }

    rapidxml::xml_node<> *
    field_grid(rapidxml::xml_document<> &doc) {

        using rapidxml::xml_node;
        using rapidxml::node_element;

        // The field (Grid) node.
        xml_node<> *grid_node = doc.allocate_node(node_element, "Grid");
        grid_node->append_attribute(doc.allocate_attribute("Name", "grid"));
        grid_node->append_attribute(doc.allocate_attribute("GridType", "Uniform"));

        // Field topology node.
        xml_node<> *topology_node = doc.allocate_node(node_element, "Topology");
        topology_node->append_attribute(doc.allocate_attribute("TopologyType", "Hexahedron"));
        topology_node->append_attribute(
                doc.allocate_attribute("NumberOfElements", _hdf_field_grid_connect_size.c_str()));
        topology_node->append_attribute(
                doc.allocate_attribute("NodesPerElement", _nodes_per_element.c_str()));
        grid_node->append_node(topology_node);

        // Field topology data item.
        xml_node<> *topology_data_item_node = doc.allocate_node(node_element, "DataItem");
        topology_data_item_node->append_attribute(
                doc.allocate_attribute("Dimensions", _hdf_field_grid_connect_dims.c_str()));
        topology_data_item_node->append_attribute(doc.allocate_attribute("Format", "HDF"));
        topology_data_item_node->value(_hdf_field_grid_connect_path.c_str());
        topology_node->append_node(topology_data_item_node);

        // Field grid node.
        xml_node<> *geometry_node = doc.allocate_node(node_element, "Geometry");
        geometry_node->append_attribute(doc.allocate_attribute("GeometryType", "XYZ"));
        grid_node->append_node(geometry_node);

        // Field grid data item.
        xml_node<> *vertices_data_item_node = doc.allocate_node(node_element, "DataItem");
        vertices_data_item_node->append_attribute(
                doc.allocate_attribute("Dimensions", _hdf_field_grid_vertices_dims.c_str()));
        vertices_data_item_node->append_attribute(doc.allocate_attribute("Format", "HDF"));
        vertices_data_item_node->value(_hdf_field_grid_vertices_path.c_str());
        geometry_node->append_node(vertices_data_item_node);

        return grid_node;

    }

    rapidxml::xml_node<> *
    field_vectors(rapidxml::xml_document<> &doc, const std::string &name, const std::string &field_vectors_dims,
                  const std::string &field_vectors_path) {

        using rapidxml::xml_node;
        using rapidxml::node_element;

        xml_node<> *temporal_grid_node = doc.allocate_node(node_element, "Grid");
        temporal_grid_node->append_attribute(doc.allocate_attribute("Name", name.c_str()));
        temporal_grid_node->append_attribute(doc.allocate_attribute("GridType", "Collection"));
        temporal_grid_node->append_attribute(doc.allocate_attribute("CollectionType", "Temporal"));

        xml_node<> *grid_node = doc.allocate_node(node_element, "Grid");
        grid_node->append_attribute(doc.allocate_attribute("Name", name.c_str()));
        grid_node->append_attribute(doc.allocate_attribute("GridType", "Uniform"));
        temporal_grid_node->append_node(grid_node);

        xml_node<> *grid_pointer_node = doc.allocate_node(node_element, "xi:include");
        grid_pointer_node->append_attribute(doc.allocate_attribute("xpointer",
                                                                   "xpointer(/Xdmf/Domain/Grid[@Name='grid'][1]/*[self::Topology or self::Geometry])"));
        grid_node->append_node(grid_pointer_node);

        xml_node<> *time_node = doc.allocate_node(node_element, "Time");
        time_node->append_attribute(doc.allocate_attribute("Value", "0"));
        grid_node->append_node(time_node);

        xml_node<> *attribute_node = doc.allocate_node(node_element, "Attribute");
        attribute_node->append_attribute(doc.allocate_attribute("Name", name.c_str()));
        attribute_node->append_attribute(doc.allocate_attribute("AttributeType", "Vector"));
        attribute_node->append_attribute(doc.allocate_attribute("Center", "Node"));
        grid_node->append_node(attribute_node);

        xml_node<> *data_item_node = doc.allocate_node(node_element, "DataItem");
        data_item_node->append_attribute(doc.allocate_attribute("Dimensions", field_vectors_dims.c_str()));
        data_item_node->append_attribute(doc.allocate_attribute("Format", "HDF"));
        data_item_node->value(field_vectors_path.c_str());
        attribute_node->append_node(data_item_node);

        return temporal_grid_node;

    }

};


#endif //LIBFABBRI_FILE_IO_HPP
