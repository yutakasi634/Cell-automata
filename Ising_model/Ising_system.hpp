#ifndef CELL_AUTOMATA_ISING_SYSTEM
#define CELL_AUTOMATA_ISING_SYSTEM

#include "../utilpack/array_matrix.hpp"
#include "spin.hpp"
#include "system_initializer_func.hpp"

template<typename spin_T, std::size_t row_Num, std::size_t column_Num, typename simulator_T>
class Ising_system
{
    using random_engine_type	= simulator_T::random_engine_type;
    using numerical_type	= simulator_T::numerical_type;
    using array_matrix		=
	Utilpack::array_matrix<spin_T*, row_Num, column_Num>;
    
  public:
    Ising_system(random_engine_type& ran_e):random_engine(ran_e)
    {
	typename
	uniform_real_distribution<std::size_t>::param_type
	    param(0, array_matrix.size() - 1);
	dist_size.param(param);
	
	initialize();
    }

    void initialize()
    {
	system_initialize<spin_T, row_Num, column_Num, simulator_T>
	    (system, tempreture, magnetic_flux_density, spin_interaction);
	return;
    }
    
    void reset_states()
    {
	for(spin_T spin : system)
	    spin.reset_state();
	return;
    }
    
    void step()
    {
	array_matrix.at(dist_size(random_engine)).step();
	return;
    }
    
  private:
    array_matrix system;
    numerical_type tempreture, magnetic_flux_density, spin_interaction;
    random_engine_type& random_engine;
    std::uniform_int_distribution<std::size_t> dist_size;
};

#endif /* CELL_AUTOMATA_ISING_SYSTEM */
