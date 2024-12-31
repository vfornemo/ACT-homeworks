\# A Molecular Dynamics Code

Molecular Dynamics: Input Reading and Distance Calculation
==========================================================

Input Handling
--------------

The first part of the program focuses on reading the input data required
for the molecular dynamics simulation. The input file `inp.txt` contains
the number of atoms and their respective Cartesian coordinates and
masses. With these, the following steps are implemented:

-   **Read Number of Atoms:** The function `read_Natoms()` reads the
    total number of atoms specified in the first line of the input file.

-   **Memory Allocation:** Using the function `malloc_2d()`, memory is
    allocated dynamically for a two-dimensional array to store atomic
    coordinates ($x, y, z$) and another one for interatomic distances.

-   **Input:** The `read_molecule()` function reads the atomic
    coordinates and masses from the file and stores them in
    pre-allocated arrays.

Distance Calculation
--------------------

The `compute_distances()` function calculates the pairwise distances
between all atoms using the Euclidean formula:

$$d_{ij} = \sqrt{(x_{i} - x_{j})^2 + (y_{i} - y_{j})^2 + (z_{i} - z_{j})^2}$$

This is performed in a nested loop for all atom pairs, where the
distance from an atom to itself is set to 0. The resulting distances are
stored in a dynamically allocated two-dimensional array for further use
in the simulation.

Key Functions
-------------

`malloc_2d():`

   Allocates memory for a 2D array, ensuring efficient storage and
    access.

`read_Natoms():`

   Reads the total number of atoms from the input file.

`read_molecule():`

   Reads atomic coordinates and masses into allocated arrays.

`compute_distances():`

   Calculates and stores interatomic distances based on Cartesian
    coordinates.

Validation and Testing
----------------------

The implementation also includes error handling, such as:

-   Checking for file-opening errors.

-   Validating the successful allocation of memory.

-   Handling unexpected input file formats or missing data.

The output is verified by printing the coordinates, masses, and
calculated distances to the console for cross-checking.
