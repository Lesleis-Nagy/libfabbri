Magnetic functions
==================

These functions implement the integrals found in Massimo Fabbri's 2008 and 2009
papers :cite:p:`fabbri:2008, fabbri:2009`. For tetrahedra, the triangle
face-windings are assumed to follow the convention outlined in
:numref:`triangle_windings`. For cubes the face winding is assumed to follow
the convention in :numref:`square_windings`.

.. _triangle_windings:

.. figure:: triangle_windings.pdf
    :alt: triangle windings
    :width: 60%

    Triangle winding conventions used for magnetic field / potential
    calculations.

.. _square_windings:

.. figure:: square_windings.pdf
    :alt: square windings
    :width: 60%

    Square winding conventions used for magnetic field / potential calculations.

.. doxygenfile:: fabbri.hpp
