#include <iostream>
#include "Ising_simulator.hpp"
#include "spin.hpp"
#include "Ising_simulator_traits.hpp"

using numerical_type = Default_simulator_traits::numerical_type;
constexpr std::size_t system_row_num, system_column_num, total_step;
constexpr int random_seed;
constexpr numerical_type tempreture, magnetic_flux_density, spin_interaction;

row_Num			= 1000;
column_Num		= 1000;
total_step		= 10000;
random_seed		= 53;
tempreture		= 1;
magnetic_flux_density	= 1;
spin_interaction	= 1;

int main(){

    Ising_simulator<
	Neuman_flip_spin, system_row_num, system_column_num, Default_simulator_traits>
	simulator(random_seed);
    simulator.set_neuman_spin_system(
	tempreture, magnetic_flux_density, spin_interaction);

    for(std::size_t step = 0; step < total_step; ++step){
	simulator.step();
	    }
    
    
    return 0;

}
