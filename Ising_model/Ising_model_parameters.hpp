#ifndef CELL_AUTOMATA_ISING_SYSTEM_ISING_PARAMETER
#define CELL_AUTOMATA_ISING_SYSTEM_ISING_PARAMETER

using numerical_type = Default_simulator_traits::numerical_type;

constexpr std::size_t    system_side_num = 1000;
constexpr std::size_t    interval_calculation(system_side_num * 100);
constexpr int            random_seed(53);
constexpr numerical_type tempreture(1);
constexpr numerical_type magnetic_flux_density(0.0);
constexpr numerical_type spin_interaction(1.0);

using simulator_type =
    Ising_simulator<Neuman_flip_spin, system_side_num,
		    system_side_num, Default_simulator_traits>;

#endif /* CELL_AUTOMATA_ISING_SYSTEM_ISING_PARAMETER */
