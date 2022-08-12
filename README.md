# Introduction
`libfabbri` is a set of `C++` routines to calculate the scalar potential, 
magnetic induction field and the magnetic vector potential for uniformly 
magetised tetrahedra. The original papers by Massimo Fabbri [1,2] outline
the theory behind this code for uniformly magnetised [1] and linearly
magnetised [2] general polyhedra.

# Compilation

Some useful flags for CMake

* `-DMULTIPRECISION=ON`, switches multiprecision functionality on by linking against MPFR libraries (this also makes use of Pavel Holoborodko's MPFR C++ library),
* `-DBUILD_TESTS=ON`, if this is on then unit tests will be built,
* `-DTEST_DEBUG_MESSAGES=ON`, if this is on then unit tests will produce some output while executing,
* `-DBUILD_UTILS=ON`, if this is on, then libfabbri utilities will be built **WARNING** this requires ncurses of user interaction and HDF5 for output.

# Prerequisites

Prerequisite libraries are
* MPFR - for multiprecision computations,
* HDF5 - if using `-DBUILD_UTILS=ON` since the utilities use this library for I/O,
* CURSES/NCURSES - if using `-DBUILD_UTILS=ON` since utilities use this library for user interaction.

If you wish to compile the documentation you will need to install 

* Doxygen
* Python
* Sphinx
* breathe
* sphinxcontrib-bibtex

# Bibliography
[1] Fabbri, M. Magnetic Flux Density and Vector3D Potential of Uniform Polyhedral Sources. Ieee T Magn 44, 32–36 (2008).

[2] Fabbri, M. Magnetic flux density and vector potential of linear polyhedral sources. Compel - Int J Comput Math Electr Electron Eng 28, 1688–1700 (2009).
 
