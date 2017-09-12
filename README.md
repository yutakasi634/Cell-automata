Cell automata
====

Extebsible cell automata code collection written in c++11.
Some part use c++14 function, so perhaps some warnings may appear when you build.

## Ising_model
Simple extensible Ising model program.
This is demo movie which show 1000 * 1000 ising model simulation.

![ising_model](data/ising_model_1000_1000.gif)

### Requirement

This code use openGL and GLUT libraries.

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
If you want to implement Ising model, in Ising_model directry,
```
$ ./Ising_model
```
If you want to test some functions, in test dirctory, you implement test files like discribed above.
