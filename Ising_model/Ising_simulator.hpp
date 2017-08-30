#ifndef CELL_AUTOMATA_ISING_SIMULATOR
#define CELL_AUTOMATA_ISING_SIMULATOR

#include <utility>
#include "Ising_system.hpp"
#include "spin.hpp"
#include "spin_params.hpp"
#include "vector"

template<template<typename>class spin_T,
	 std::size_t row_Num, std::size_t column_Num, typename simulator_T>
class Ising_simulator
{
    using spin_type		= spin_T<simulator_T>;
    using spin_params_type	= Spin_params<spin_type>;
    using system_type		= Ising_system<spin_type, row_Num, column_Num>;
    using numerical_type	= typename simulator_T::numerical_type;
    using random_engine_type	= typename simulator_T::random_engine_type;
    using array_matrix		=
	typename Utilpack::array_matrix<spin_type, row_Num, column_Num>;
    
  public:
    template<typename ...Params>
    Ising_simulator(int seed, Params&&... params):
	spin_params{std::forward<Params>(params) ...},random_engine(seed)
    {
//	ising_system.initialize(spin_params, random_engine);
//	ising_system.reset_states();
    }

    void step()
    {
	ising_system.step();
	return;
    }
    
    void reset()
    {
	ising_system.reset_states();
	return;
    }

    const array_matrix& spins_state() const
    {
	return ising_system.spins_state();
    }
    
  private:
    spin_params_type spin_params;
    random_engine_type random_engine;
    system_type ising_system;
};


#endif /* CELL_AUTOMATA_ISING_SYSTEM */
