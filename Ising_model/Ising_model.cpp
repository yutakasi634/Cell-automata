#include <iostream>
#include "Ising_simulator.hpp"
#include "spin.hpp"
#include "Ising_simulator_traits.hpp"

using numerical_type = Default_simulator_traits::numerical_type;
constexpr std::size_t system_row_num(1000);
constexpr std::size_t system_column_num(1000);
constexpr std::size_t total_step(10000);
constexpr int random_seed(53);
constexpr numerical_type tempreture(1);
constexpr numerical_type magnetic_flux_density(1);
constexpr numerical_type spin_interaction(1);

int main(){

    Ising_simulator<
	Neuman_flip_spin, system_row_num, system_column_num, Default_simulator_traits>
	simulator(random_seed, tempreture, magnetic_flux_density, spin_interaction);

    // for(std::size_t step = 0; step < total_step; ++step){
    // 	std::cout << step << std::endl;
    // 	simulator.step();
    // }
    return 0;
}
