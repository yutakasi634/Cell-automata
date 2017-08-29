#ifndef CELL_AUTOMATA_ISING_SPIN_PARAMS
#define CELL_AUTOMATA_ISING_SPIN_PARAMS

template<typename spin_T, typename simulator_T>
struct Spin_params;

template<typename simulator_T>
class Neuman_flip_spin;

template<typename simulator_T>
struct Spin_params<Neuman_flip_spin<simulator_T>, simulator_T>
{
    using numerical_type = typename simulator_T::numerical_type;

    Spin_params(numerical_type t, numerical_type m, numerical_type s):
	tempreture(t), magnetic_flux_density(m), spin_interaction(s){};
    
    numerical_type tempreture, magnetic_flux_density, spin_interaction;
};

#endif /* CELL_AUTOMATA_ISING_SPIN_PARAMS */
