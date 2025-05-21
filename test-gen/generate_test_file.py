import os, sys
import numpy as np
import h5py

def print_cpp_vcl(vcl, variable_name="vcl"):
    print(f"VertexList3D<double> {variable_name} = {{");
    for idx, v in enumerate(vcl):
        if idx < len(vcl) - 1:
            comma = ","
        else:
            comma = ""

        print(f"  {{{v[0]:20.15f}, {v[1]:20.15f}, {v[2]:20.15f}}}" + comma)

    print("};")

def print_cpp_til(til, variable_name="til"):
    print(f"IndexTupleList<4> {variable_name} = {{")
    for idx, n in enumerate(til):
        if idx < len(til) - 1:
            comma = ","
        else:
            comma = ""

        print(f" {{{n[0]:3d}, {n[1]:3d}, {n[2]:3d}, {n[3]:3d}}}" + comma)

    print("};")

def print_cpp_centroids(vcl, til, variable_name="centroids"):
    print(f"VertexList3D<double> {variable_name} = {{")
    for idx, (n0, n1, n2, n3) in enumerate(til):
        if idx < len(til) - 1:
            comma = ","
        else:
            comma = ""

        c = (vcl[n0] + vcl[n1] + vcl[n2] + vcl[n3]) / 4.0

        print(f" {{{c[0]:20.15f}, {c[1]:20.15f}, {c[2]:20.15f}}}" + comma)

    print("};")

def print_cpp_volumes(vcl, til, variable_name="volumes"):
    print(f"{variable_name} = {{")
    for idx, (n0, n1, n2, n3) in enumerate(til):
        if idx < len(til) - 1:
            comma = ","
        else:
            comma = ""

        v0 = vcl[n0]
        v1 = vcl[n1]
        v2 = vcl[n2]
        v3 = vcl[n3]

        a = v1 - v0
        b = v2 - v0
        c = v3 - v0

        volume = abs(np.dot(a, np.cross(b, c))) / 6.0

        c = (vcl[n0] + vcl[n1] + vcl[n2] + vcl[n3]) / 4.0

        print(f" {volume:20.15f}" + comma)

    print("};")

if __name__ == "__main__":
    
    if len(sys.argv) < 2:
        print("Need to supply input hdf5 file")
        sys.exit(1)

    vcl = None
    til = None
    with h5py.File(sys.argv[1], 'r') as fin:
        vcl = np.column_stack((fin["coordx"][:], fin["coordy"][:], fin["coordz"][:]))
        til = fin["connect1"][:] - 1

    print_cpp_vcl(vcl)
    print("")
    print_cpp_til(til)
    print("")
    print_cpp_centroids(vcl, til)
    print("")
    print_cpp_volumes(vcl, til)

