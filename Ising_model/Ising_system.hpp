#ifndef CELL_AUTOMATA_ISING_SYSTEM
#define CELL_AUTOMATA_ISING_SYSTEM

#include "../utilpack/array_matrix.hpp"
#include "spin.hpp"
#include "spin_params.hpp" 
#include "system_initializer_func.hpp"

template<typename spin_T, std::size_t row_Num, std::size_t column_Num>
class Ising_system
{
    using spin_type			= spin_T;
    using spin_params_type              = Spin_params<spin_type>;
    using simulator_traits              = typename spin_type::simulator_traits;
    using random_engine_type		= typename simulator_traits::random_engine_type;
    using numerical_type		= typename simulator_traits::numerical_type;
    using array_matrix			=
	Utilpack::array_matrix<spin_type, row_Num, column_Num>;
    
  public:
    Ising_system(spin_params_type& s_params,
		 random_engine_type& ran_e):
	spin_params(s_params), random_engine(ran_e)
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
	    (system, spin_params, &random_engine);
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
	system.at(dist_size(random_engine)).step();
	return;
    }

    array_matrix& spins_state() const
    {
	return system;
    }
    
  private:
    array_matrix system;
    Spin_params<spin_type>& spin_params;
    random_engine_type& random_engine;
    std::uniform_int_distribution<std::size_t> dist_size;
};

#endif /* CELL_AUTOMATA_ISING_SYSTEM */
