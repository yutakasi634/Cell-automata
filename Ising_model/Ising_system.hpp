#ifndef CELL_AUTOMATA_ISING_SYSTEM
#define CELL_AUTOMATA_ISING_SYSTEM

#include "../utilpack/array_matrix.hpp"
#include "spin.hpp"
#include "spin_params.hpp" 
#include "system_initializer_func.hpp"

template<template<typename> class spin_T,
	 std::size_t row_Num, std::size_t column_Num, typename simulator_T>
class Ising_system
{
    using random_engine_type		= typename simulator_T::random_engine_type;
    using random_engine_pointer_type	= random_engine_type*;
    using numerical_type		= typename simulator_T::numerical_type;
    using spin_type			= spin_T<simulator_T>;
    using array_matrix			=
	Utilpack::array_matrix<spin_type, row_Num, column_Num>;
    
  public:
    Ising_system(Spin_params<spin_type>& s_params,
		 random_engine_type& ran_e):
	spin_params(s_params), random_engine_pointer(&ran_e)
    {
	typename
	    std::uniform_int_distribution<std::size_t>::param_type
	    param(0, system.size() - 1);
	dist_size.param(param);
	
	initialize();
    }

    void initialize()
    {
	system_initialize<spin_type, row_Num, column_Num>
	    (system, spin_params, random_engine_pointer);
	return;
    }
    
    void reset_states()
    {
	for(spin_type& spin : system)
	    spin.reset_state();
	return;
    }
    
    void step()
    {
	system.at(dist_size(*random_engine_pointer)).step();
	return;
    }
    
  private:
    array_matrix system;
    Spin_params<spin_type> spin_params;
    random_engine_pointer_type random_engine_pointer;
    std::uniform_int_distribution<std::size_t> dist_size;
};

#endif /* CELL_AUTOMATA_ISING_SYSTEM */
