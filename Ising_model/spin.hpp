#ifndef CELL_AUTOMATA_ISING_SPIN
#define CELL_AUTOMATA_ISING_SPIN

#include <array>
#include <random>
#include <stdexcept>
#include <cmath>
#include "spin_base.hpp"

template<typename numerical_T, typename random_engine_T>
class Neuman_flip_spin : public Spin_base<int, 4>
{
    using numerical_type	= numerical_T;
    using random_engine_type	= random_engine_T;
    
  public:
    Neuman_flip_spin(state_type s, numerical_type& temp, numerical_type& perm,
		     numerical_type& spin_inter, random_engine_type& ran):
	Spin_base<int, 4>(s), tempreture(temp), magnetic_flux_density(perm),
	spin_interaction(spin_inter), random_engine(ran)
    {
	if(s != 1 && s != -1)
	    throw std::invalid_argument("Neuman flip spin state have to be 1 or -1.");
	
	typename
	    std::uniform_real_distribution<numerical_type>::param_type param_r(0.0, 1.0);
	dist_r01.param(param_r);

	typename
	    std::uniform_int_distribution<>::param_type param_i(0, 1);
	dist_i01.param(param_i);
    }

    virtual void set_partners(const partners_list_type& partners_list) override
    {
	partners = partners_list;
	return;
    }
    
    virtual void step() override
    {
	numerical_type energy_diff = after_flip_energy() - current_energy();
	if(energy_diff <= 0)
	    flip();
	else
	{
	    numerical_type flip_prob = std::exp(-tempreture * energy_diff);
	    if(dist_r01(random_engine) <= flip_prob)
		flip();
	}
	return;
    };

    void flip()
    {
	state *= -1;
	return;
    }
    
    numerical_type current_energy() const
    {
	numerical_type energy(0);
	for(auto elem_p : partners)
	    energy += elem_p->get();
	energy = (-spin_interaction * energy - magnetic_flux_density) * state;
	return energy;
    }
    
    numerical_type after_flip_energy() const
    {
	return -current_energy();
    }

    void initialize()
    {
	state = 2 * dist_i01(random_engine) - 1;
    }
    
  private:
    const numerical_type& tempreture, magnetic_flux_density, spin_interaction;
    random_engine_type& random_engine;
    std::uniform_real_distribution<numerical_type> dist_r01;
    std::uniform_int_distribution<> dist_i01;
};

#endif /* CELL_AUTOMATA_ISING_SPIN */
