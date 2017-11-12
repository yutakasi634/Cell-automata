[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

Cell automata
====

Extensible cell automata code collection written in c++11.
Some part uses c++14 function, so perhaps some warnings may appear when you build.

## Ising_model
Simple extensible Ising model program.
This is demo movie which shows 1000 * 1000 ising model simulation.

![ising_model](data/ising_model_1000_1000.gif)

### Requirement

This code uses openGL and GLUT libraries.

### Build

```
$ git clone https://github.com/yutakasi634/Cell-automata.git
$ cd Ising_model
$ mkdir build
$ cd build
$ cmake ..
$ make
```
### Usage
If you want to implement Ising model, in Ising_model directory,
```
$ ./Ising_model
```
If you want to test some functions, in the test directory, you implement test files as described above.
