import os, sys, re

import numpy as np

class Mesh:
    def __init__(self, dimensions, nvert, ntri, indexing, vcl, til, sub):
        self.dimensions = dimensions
        self.nvert = nvert
        self.ntri = ntri
        self.indexing = indexing
        self.vcl = vcl
        self.til = til
        self.sub = sub


def read_mesh(file_name, write_line=False):
    r"""
    Reads the simple file text format.
    """

    re_header = re.compile(
        r"^\s*([0-9]+)\s*([0-9]+)\s*([0-9]+)\s*((ZERO)|(ONE))\s*$"
    )

    re_vertex = re.compile(
        r"^\s*([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?)"  \
            r"\s*([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?)" \
            r"\s*([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?)\s*$"
    )

    re_tetrahedron = re.compile(
        r"^\s*([0-9]+)\s*([0-9]+)\s*([0-9]+)\s*([0-9]+)\s*([0-9]+)\s*$"
    )

    dimensions = None
    nvert = None
    ntri = None
    indexing = None

    vcl = []
    til = []
    sub = []

    with open(file_name, "r") as fin:
        line_counter = 1

        for line in fin:

            if write_line:
                print(f"{line_counter:04d}: {line.strip()}")

            if line_counter > 1 \
                    and (dimensions is None
                         or nvert is None
                         or ntri is None
                         or indexing is None):
                print("Error: no header found on first line")
                sys.exit(1)

            if line_counter == 1:
                match_header = re_header.match(line)
                if match_header:
                    dimensions = int(match_header.group(1))
                    nvert = int(match_header.group(2))
                    ntri = int(match_header.group(3))
                    indexing = match_header.group(4)
                else:
                    print("Error: no header found on first line")
                    sys.exit(1)
            elif 2 <= line_counter and line_counter <= nvert+1:
                match_vertex = re_vertex.match(line)
                if match_vertex:
                    vcl.append((
                        float(match_vertex.group(1)),
                        float(match_vertex.group(3)),
                        float(match_vertex.group(5))
                    ))
                else:
                    print(f"Error: no vertex found on lines: 2-{nvert+1}")
                    sys.exit(1)
            elif nvert+2 <= line_counter and line_counter <= nvert+ntri+1:
                match_tetrahedron = re_tetrahedron.match(line)
                if match_tetrahedron:
                    til.append((
                        int(match_tetrahedron.group(1)),
                        int(match_tetrahedron.group(2)),
                        int(match_tetrahedron.group(3)),
                        int(match_tetrahedron.group(4))
                    ))
                    sub.append(int(match_tetrahedron.group(5)))
                else:
                    print(f"Error: no tetrahedron found on lines:" \
                            f"{nvert+2}-{nvert+ntri+1}")
                    sys.exit(1)

            line_counter = line_counter + 1

    if len(vcl) != nvert:
        print("Vertex array count is incorrect")
        sys.exit(1)

    if len(til) != ntri:
        print("Tetrahedron array count is incorrect")
        sys.exit(1)

    return Mesh(dimensions, nvert, ntri, indexing, vcl, til, sub)


if __name__ == "__main__":

    data = read_mesh("small_cube.txt")

    print(
        f"dims: {data.dimensions}, "
        f"nvert: {data.nvert}, "
        f"ntri: {data.ntri}, "
        f"indexing: {data.indexing}")

    print(f"Vertices")
    for v in data.vcl:
        print(f"{v[0]:20.15f} {v[1]:20.15f} {v[2]:20.15f}")
    print("")

    print(f"Elements")
    for n in data.til:
        print(f"{n[0]:5d} {n[1]:5d} {n[2]:5d} {n[3]:5d}")
    print("")

    print(f"Centroids")
    counter = 0
    for t in data.til:
        v0 = data.vcl[t[0] - 1]
        v1 = data.vcl[t[1] - 1]
        v2 = data.vcl[t[2] - 1]
        v3 = data.vcl[t[3] - 1]

        r_c = ((v0[0] + v1[0] + v2[0] + v3[0]) / 4.0,
               (v0[1] + v1[1] + v2[1] + v3[1]) / 4.0,
               (v0[2] + v1[2] + v2[2] + v3[2]) / 4.0)

        print(f"{counter:4d} {r_c[0]:10.5f}, {r_c[1]:10.5f}, {r_c[2]:10.5f}")

        counter = counter + 1
    print("")

    print("Volumes")
    for counter, t in enumerate(data.til):
        v0 = np.array(data.vcl[t[0] - 1])
        v1 = np.array(data.vcl[t[1] - 1])
        v2 = np.array(data.vcl[t[2] - 1])
        v3 = np.array(data.vcl[t[3] - 1])

        a = v1 - v0
        b = v2 - v0
        c = v3 - v0

        volume = abs(np.dot(a, np.cross(b, c))) / 6.0

        print(f"{counter:4d} {volume:20.15f}")
