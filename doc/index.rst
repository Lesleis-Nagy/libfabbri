.. libfabbri documentation master file, created by
   sphinx-quickstart on Sat Jul 30 09:23:08 2022.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to libfabbri's documentation!
=====================================
This library implements analytical calculations for **B** -- the
magnetic field, **W** -- the magnetic scalar potential, and
**V** -- the magnetic vector potential for uniformly and linearly
magnetised tetrahedra based on Massimo Fabbri's 2008 and 2009 papers
:cite:p:`fabbri:2008, fabbri:2009`. The library used for
multiprecision calculations is `MPFR C++ <http://www.holoborodko.com/pavel/mpfr/>`_ :cite:p:`holoborodko:2010` which makes
use of `MPFR <https://www.mpfr.org/>`_ :cite:p:`fousse-et-al:2007`. For unit testing we use the `Catch2 <https://github.com/catchorg/Catch2>`_
library :cite:p:`catch2:2017`.

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   classes
   bibliography

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
