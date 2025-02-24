The Octree library
=====================

The octree library enables efficient computation of
the magnetic induction field using a tree summation technique
(see :numref:`front-cuboids` and :numref:`back-cuboids`).

.. _front-cuboids:

.. figure:: front.pdf
   :alt: font cuboids
   :width: 100%

   The front four sub-cuboids of a cuboid.

.. _back-cuboids:

.. figure:: back.pdf
   :alt: back cuboids
   :width: 100%

   The back four sub-cuboids of a cuboid.

A cuboid is defined by points :math:`\bm{r}^0` and
:math:`\bm{r}^{26}`, since these are the minimal and maximal coordinates of
an axis aligned cuboid, we set
:math:`\bm{r}^0 \equiv \vecrmin = \left< \rmin{x},  \rmin{y}, \rmin{z} \right>` and
:math:`\bm{r}^{26} \equiv \vecrmax = \left< \rmax{x}, \rmax{y}, \rmax{z} \right>`.
The point :math:`\bm{r}^{13} \equiv \vecrmid` is special because it
defines the centre of the cuboid and appears in every sub-cuboid after
subdivision; it is defined as

.. math::
    :label: cuboid-midpoint

    \vecrmid = \left< \rmid{x}, \rmid{y}, \rmid{z} \ \right>
             = \left< \frac{\rmin{x} + \rmax{x}}{2},
                      \frac{\rmin{y} + \rmax{y}}{2},
                      \frac{\rmin{z} + \rmax{z}}{2} \right>.

In :numref:`cuboidcoordinates` we list all the coordinates shown in
:numref:`front-cuboids` and :numref:`back-cuboids` using the same indexing
scheme with reference to :math:`\vecrmin`, :math:`\vecrmid`
and :math:`\vecrmax`.

.. table:: coordinates of an axis aligned cuboid along with sub-cuboids.
    :widths: auto
    :name: cuboidcoordinates

    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | Position            | Components                                          | Position            | Components                                          | Position            | Components                                          |
    +=====================+=====================================================+=====================+=====================================================+=====================+=====================================================+
    | :math:`\bm{r}^{0}`  | :math:`\left< \rmin{x}, \rmin{y}, \rmin{z} \right>` | :math:`\bm{r}^{9}`  | :math:`\left< \rmin{x}, \rmid{y}, \rmin{z} \right>` | :math:`\bm{r}^{18}` | :math:`\left< \rmin{x}, \rmax{y}, \rmin{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | :math:`\bm{r}^{1}`  | :math:`\left< \rmid{x}, \rmin{y}, \rmin{z} \right>` | :math:`\bm{r}^{10}` | :math:`\left< \rmid{x}, \rmid{y}, \rmin{z} \right>` | :math:`\bm{r}^{19}` | :math:`\left< \rmid{x}, \rmax{y}, \rmin{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | :math:`\bm{r}^{2}`  | :math:`\left< \rmax{x}, \rmin{y}, \rmin{z} \right>` | :math:`\bm{r}^{11}` | :math:`\left< \rmax{x}, \rmid{y}, \rmin{z} \right>` | :math:`\bm{r}^{20}` | :math:`\left< \rmax{x}, \rmax{y}, \rmin{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | :math:`\bm{r}^{3}`  | :math:`\left< \rmin{x}, \rmin{y}, \rmid{z} \right>` | :math:`\bm{r}^{12}` | :math:`\left< \rmin{x}, \rmid{y}, \rmid{z} \right>` | :math:`\bm{r}^{21}` | :math:`\left< \rmin{x}, \rmax{y}, \rmid{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | :math:`\bm{r}^{4}`  | :math:`\left< \rmid{x}, \rmin{y}, \rmid{z} \right>` | :math:`\bm{r}^{13}` | :math:`\left< \rmid{x}, \rmid{y}, \rmid{z} \right>` | :math:`\bm{r}^{22}` | :math:`\left< \rmid{x}, \rmax{y}, \rmid{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | :math:`\bm{r}^{5}`  | :math:`\left< \rmax{x}, \rmin{y}, \rmid{z} \right>` | :math:`\bm{r}^{14}` | :math:`\left< \rmax{x}, \rmid{y}, \rmid{z} \right>` | :math:`\bm{r}^{23}` | :math:`\left< \rmax{x}, \rmax{y}, \rmid{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | :math:`\bm{r}^{6}`  | :math:`\left< \rmin{x}, \rmin{y}, \rmax{z} \right>` | :math:`\bm{r}^{15}` | :math:`\left< \rmin{x}, \rmid{y}, \rmax{z} \right>` | :math:`\bm{r}^{24}` | :math:`\left< \rmin{x}, \rmax{y}, \rmax{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | :math:`\bm{r}^{7}`  | :math:`\left< \rmid{x}, \rmin{y}, \rmax{z} \right>` | :math:`\bm{r}^{16}` | :math:`\left< \rmid{x}, \rmid{y}, \rmax{z} \right>` | :math:`\bm{r}^{25}` | :math:`\left< \rmid{x}, \rmax{y}, \rmax{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+
    | :math:`\bm{r}^{8}`  | :math:`\left< \rmax{x}, \rmin{y}, \rmax{z} \right>` | :math:`\bm{r}^{17}` | :math:`\left< \rmax{x}, \rmid{y}, \rmax{z} \right>` | :math:`\bm{r}^{26}` | :math:`\left< \rmax{x}, \rmax{y}, \rmax{z} \right>` |
    +---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+---------------------+-----------------------------------------------------+

The eight octants of a cuboid, after subdivision, are labelled in
:numref:`front-cuboids` and :numref:`back-cuboids`; where 'left-right' is
relative to the :math:`x`-axis ('left' in a negative :math:`x` direction and
'right' in a positive :math:`x` direction), 'top-bottom' is relative to the
:math:`y`-axis ('bottom' in a negative :math:`y` direction and 'top' in a
positive `y` direction) and 'front-back' is relative to the :math:`z`-axis (
'back' in a negative :math:`z` direction and 'front' in a positive :math:`z`
direction). An arbitrary point :math:`\bm{r} = \left< r_x, r_y, r_z \right>`
acquires a labelling (and a label-code) according to the tests shown in
:numref:`labelling-tests` -- that is a point that is labelled left, bottom or
top is given a zero-code, whereas a point that is labelled right is given a
code of 1, top is given a code of 2 and front is given a code of 4.

.. table:: testing a point for octant membership, labels with a 'negative
           direction' are assigned a zero code, where as labels with a
           'positive direction' are assigned a positive integer.
    :widths: auto
    :name: labelling-tests

    +--------+------------+-----------------------------------------+
    | label  | label-code | test                                    |
    +========+============+=========================================+
    | Left   | 0          | :math:`\rmin{x} \leq r_x  <   \rmid{x}` |
    +--------+------------+-----------------------------------------+
    | Right  | 1          | :math:`\rmid{x} \leq r_x \leq \rmax{x}` |
    +--------+------------+-----------------------------------------+
    | Bottom | 0          | :math:`\rmin{y} \leq r_y  <   \rmid{y}` |
    +--------+------------+-----------------------------------------+
    | Top    | 2          | :math:`\rmid{y} \leq r_y \leq \rmax{y}` |
    +--------+------------+-----------------------------------------+
    | Back   | 0          | :math:`\rmin{z} \leq r_z  <   \rmid{z}` |
    +--------+------------+-----------------------------------------+
    | Front  | 4          | :math:`\rmid{z} \leq r_z \leq \rmax{z}` |
    +--------+------------+-----------------------------------------+

By taking the sum of the label-codes for each component of :math:`\bm{r}` we
produce a unique integer that determines which octant the point is in. These
octants, along with the sum-code are shown in :numref:`sum-codes`.

.. table:: final sum-codes denoting octant labels
    :widths: auto
    :name: sum-codes

    +----------+------------+------------+------------+--------------+
    | sum-code | front/back | top/bottom | right/left | label code   |
    +==========+============+============+============+==============+
    | 0        | back       | bottom     | left       | BBL          |
    +----------+------------+------------+------------+--------------+
    | 1        | back       | bottom     | right      | BBR          |
    +----------+------------+------------+------------+--------------+
    | 2        | back       | top        | left       | BTL          |
    +----------+------------+------------+------------+--------------+
    | 3        | back       | top        | right      | BTR          |
    +----------+------------+------------+------------+--------------+
    | 4        | front      | bottom     | left       | FBL          |
    +----------+------------+------------+------------+--------------+
    | 5        | front      | bottom     | right      | FBR          |
    +----------+------------+------------+------------+--------------+
    | 6        | front      | top        | left       | FTL          |
    +----------+------------+------------+------------+--------------+
    | 7        | front      | top        | right      | FTR          |
    +----------+------------+------------+------------+--------------+

Each sub-division is defined by its own :math:`\vecrmin` and :math:`\vecrmax`
vertices. Referring to :numref:`front-cuboids` and :numref:`back-cuboids` and
the label codes in :numref:`sum-codes` the position vertices for each sub-cuboid
are

.. table:: The minimum and maximum position vectors, :math:`\vecrmin` and :math:`\vecrmax`, of each sub-cuboid
    :widths: auto
    :name: vecmin-and-vecmax

    +------------+---------------------+---------------------+
    | label code | :math:`\vecrmin`    | :math:`\vecrmax`    |
    +============+=====================+=====================+
    | BBL        | :math:`\bm{r}_{0}`  | :math:`\bm{r}_{13}` |
    +------------+---------------------+---------------------+
    | BBR        | :math:`\bm{r}_{1}`  | :math:`\bm{r}_{14}` |
    +------------+---------------------+---------------------+
    | BTL        | :math:`\bm{r}_{9}`  | :math:`\bm{r}_{22}` |
    +------------+---------------------+---------------------+
    | BTR        | :math:`\bm{r}_{10}` | :math:`\bm{r}_{23}` |
    +------------+---------------------+---------------------+
    | FBL        | :math:`\bm{r}_{3}`  | :math:`\bm{r}_{16}` |
    +------------+---------------------+---------------------+
    | FBR        | :math:`\bm{r}_{4}`  | :math:`\bm{r}_{17}` |
    +------------+---------------------+---------------------+
    | FTL        | :math:`\bm{r}_{12}` | :math:`\bm{r}_{25}` |
    +------------+---------------------+---------------------+
    | FTR        | :math:`\bm{r}_{13}` | :math:`\bm{r}_{26}` |
    +------------+---------------------+---------------------+

.. doxygenfile:: octree.hpp

