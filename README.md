# Introduction
`libfabbri` is a set of `C++` routines to calculate the scalar potential, 
magnetic induction field and the magnetic vector potential for uniformly 
magetised tetrahedra. The original papers by Massimo Fabbri [1,2] outline
the theory behind this code for uniformly magnetised [1] and linearly
magnetised [2] general polyhedra.

# Compilation

Some useful flags for CMake

* `-DMULTIPRECISION=ON`, switches multiprecision functionality on by linking against MPFR libraries (this also makes use of Pavel Holoborodko's MPFR C++ library),
* `-DBUILD_TESTS=ON`, if this is on, then unit tests will be built,
* `-DBUILD_UTILITIES=ON`, if this is on, then libfabbri utilities will be built.

# Bibliography
[1] Fabbri, M. Magnetic Flux Density and Vector3D Potential of Uniform Polyhedral Sources. Ieee T Magn 44, 32–36 (2008).

[2] Fabbri, M. Magnetic flux density and vector potential of linear polyhedral sources. Compel - Int J Comput Math Electr Electron Eng 28, 1688–1700 (2009).
 
