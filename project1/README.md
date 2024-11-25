# Computation of the MP2 energy

This program reads the `.h5` file and computes the MP2 energy.

## Theory

The MP2 energy is given by the formula:

```math
E_{\text{MP2}} = E_{\text{HF}} + 
 \sum_{(i,j)\in\text{occupied}}\sum_{(a,b)\in\text{virtual}}\langle ij|ab\rangle\frac{2\langle ij|ab\rangle-\langle ij|ba\rangle}{\varepsilon_i+\varepsilon_j-\varepsilon_a-\varepsilon_b}
```

where the $E_{\text{HF}}$ is the Hartree-Fock energy calculated by the following formula:

```math
E_{\text{HF}} = E_{NN} + 2\sum_{i=1}^{N_{\text{occ}}}\langle i|\hat{h}|i\rangle + \sum_{i=1}^{N_{\text{occ}}}\sum_{j=1}^{N_{\text{occ}}} \left(2\langle ij|ij\rangle - \langle ij|ji\rangle\right)
```

## Dependencies

The program depends on the `HDF5` library and `TREXIO` library. 

### HDF5

On Ubuntu, the `HDF5` library can be installed using the following command:

```bash
$ sudo apt-get install libhdf5-dev
```

### TREXIO

The `TREXIO` library can be installed using the following command:

```bash
$ wget https://github.com/TREX-CoE/trexio/releases/download/v2.5.0/trexio-2.5.0.tar.gz
$ tar -zxvf trexio-2.5.0.tar.gz
$ cd trexio-2.5.0
$ ./configure
$ make
$ sudo make install
```
Note that when configuring the `TREXIO` library, you may need to specify the path to the `HDF5` library if it is not installed in the default location. See more information [here](https://github.com/TREX-CoE/trexio).

## Installation and usage

To install the program, run the following commands:

```bash
$ git clone git@github.com:vfornemo/ACT-homeworks.git
$ cd project1
$ ./compile.sh
```

The program can be run using the following command:

```bash
./main.o [path/to/input.h5]
```

The program will read the `input.h5` file and write the MP2 energy to the standard output.

## Example

```bash
$ ./main.o ./data/h2o.h5
```

The output will be:

```bash
Reading file: ./data/h2o.h5
Nucleus repulsion energy: 9.194966
Number of up electrons: 5
Number of MOs: 24
Number of 2e integrals: 13458
h_core_sum: -123.151186
eri_sum: 37.929422
Electronic energy: -85.221764
HF energy: -76.026799
MP2 energy: -76.230759
```
