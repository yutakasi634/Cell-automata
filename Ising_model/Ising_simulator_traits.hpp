#ifndef CELL_AUTOMATA_ISING_SIMULATOR_TRAITS
#define CELL_AUTOMATA_ISING_SIMULATOR_TRAITS

#include <random>

struct Default_simulator_traits
{
    using numerical_type	= float;
    using random_engine_type	= std::mt19937;
};

#endif /* CELL_AUTOMATA_ISING_SIMULATOR_TRAITS */
