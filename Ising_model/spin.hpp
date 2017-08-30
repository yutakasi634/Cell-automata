#ifndef CELL_AUTOMATA_ISING_SPIN
#define CELL_AUTOMATA_ISING_SPIN

#include <array>
#include <random>
#include <stdexcept>
#include <cmath>
#include "spin_base.hpp"
#include "spin_params.hpp"

template<typename simulator_T>
class Neuman_flip_spin : public Spin_base<int, 4>
{    
  public:

    using simulator_traits		= simulator_T;
    using numerical_type		= typename simulator_traits::numerical_type;
    using spin_params_type              = Spin_params<Neuman_flip_spin<simulator_T> >;
    using spin_params_pointer           = spin_params_type*;
    using random_engine_type		= typename simulator_traits::random_engine_type;
    using random_engine_pointer_type	= random_engine_type*;

    Neuman_flip_spin():
	spin_params_ptr(nullptr),random_engine_ptr(nullptr){};
    
    Neuman_flip_spin(
	const spin_params_pointer params_ptr,
	const random_engine_pointer_type rand_en_ptr):
	Spin_base<int, 4>(0),
	spin_params_ptr(params_ptr),
	random_engine_ptr(rand_en_ptr)
    {
	generate_distribution();
    }
    
    Neuman_flip_spin(
	const int s,
	const spin_params_pointer params_ptr,
	const random_engine_pointer_type random_engine_ptr):
	Spin_base<int, 4>(s),
	spin_params_ptr(params_ptr),
	random_engine_ptr(random_engine_ptr)
    {	
	check_state();
	generate_distribution();
    }

    void check_state() const
    {
	if(state != 1 && state != -1)
	    throw std::invalid_argument("Neuman flip spin state have to be 1 or -1.");
	return;
    }

    void generate_distribution()
    {
	typename
	    std::uniform_real_distribution<numerical_type>::param_type param_r(0.0, 1.0);
	dist_r01.param(param_r);

	typename
	    std::uniform_int_distribution<>::param_type param_i(0, 1);
	dist_i01.param(param_i);
	return;
    }
    
    virtual void set_partners(const partners_list_type& partners_list) override
    {
	partners = partners_list;
	return;
    }

    const partners_list_type& get_partners() const
    {
	return partners;
    }
    
    virtual void step() override
    {
	numerical_type tempreture = (*spin_params_ptr).tempreture;
	numerical_type energy_diff = after_flip_energy() - current_energy();
	if(energy_diff <= 0)
	    flip();
	else
	{
	    numerical_type flip_prob = std::exp(-tempreture * energy_diff);
	    if(dist_r01(*random_engine_ptr) <= flip_prob)
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
	numerical_type spin_interaction = (*spin_params_ptr).spin_interaction;
	numerical_type magnetic_flux_density = (*spin_params_ptr).magnetic_flux_density;
	numerical_type energy(0);
	for(auto& elem_p : partners)
	    energy += elem_p->get();
	energy = (-spin_interaction * energy - magnetic_flux_density) * state;
	return energy;
    }
    
    numerical_type after_flip_energy() const
    {
	return -current_energy();
    }

    virtual void reset_state() override
    {
	state = dist_i01(*random_engine_ptr);
	state = 2 * state - 1;
    }

    
    
  private:
    
    spin_params_pointer spin_params_ptr;
    random_engine_pointer_type random_engine_ptr;
    std::uniform_real_distribution<numerical_type> dist_r01;
    std::uniform_int_distribution<> dist_i01;
};

#endif /* CELL_AUTOMATA_ISING_SPIN */
