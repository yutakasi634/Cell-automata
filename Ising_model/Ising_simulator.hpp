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
    using system_type		= Ising_system<spin_type>;
    using numerical_type	= simulator_T::random_engine_type;
    using random_engine_type	= simulator_T::random_engine_type;
    using array_matrix		= system_type::array_matrix;
    
  public:
    Ising_simulator(int seed):random_engine(seed){};

    void set_neuman_spin_system(
	numerical_type tempreture ,numerical_type magnetic_flux_density,
	numerical_type spin_interaction)
    {
	spin_params =
	    Spin_params<spin_type>(tempreture, magnetic_flux_density, spin_interaction);
	return;
    }
    
    void set_ising_system()
    {
	ising_system =
	    Ising_system<spin_type, row_Num, column_Num>(spin_params, random_engine);
	return;
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

    array_matrix& spins_state() const
    {
	return ising_system.spins_state();
    }
    
  private:
    spin_params_type spin_params;
    system_type ising_system;
    random_engine_type random_engine;
};
    

#endif /* CELL_AUTOMATA_ISING_SYSTEM */
