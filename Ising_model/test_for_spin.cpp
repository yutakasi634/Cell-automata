#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <iostream>
#include <array>
#include <cmath>
#include "Ising_simulator_traits.hpp"
#include "spin.hpp"
#include "spin_params.hpp"

using simulator_traits          = Default_simulator_traits;
using Neuman_f_spin		= Neuman_flip_spin<simulator_traits>;
using numerical_type		= Neuman_f_spin::numerical_type;
using random_engine_type	= Neuman_f_spin::random_engine_type;
using base_pointer		= Neuman_f_spin::base_pointer;
using const_base_pointer	= Neuman_f_spin::const_base_pointer;
using spin_params_type          = spin_params<Neuman_f_spin, simulator_traits>;

numerical_type tolerance = 1e-5;//tolerance for BOOST_CHECK_CLOSE_FRACTION.

random_engine_type random_generator(53);
numerical_type tempreture(1), magnetic_flux_density(1), spin_interaction(1);
spin_params_type params(tempreture, magnetic_flux_density, spin_interaction);

const Neuman_f_spin up_spin(1, params, random_generator), 
    down_spin(-1, params, random_generator);
const_base_pointer up_spin_p = &up_spin, down_spin_p = &down_spin;



BOOST_AUTO_TEST_CASE(Neuman_flip_spin_constructor)
{
    
    BOOST_CHECK_THROW(
	Neuman_f_spin error_spin(
	    2, params, random_generator), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(Neuman_flip_spin_current_energy)
{
    Neuman_f_spin test_spin(1, params, random_generator);
    
    std::array<const_base_pointer, 4> neighbours =
	{up_spin_p, up_spin_p, up_spin_p, down_spin_p};    
    test_spin.set_partners(neighbours);
    BOOST_CHECK_CLOSE_FRACTION(-3, test_spin.current_energy(), tolerance);
}

BOOST_AUTO_TEST_CASE(Neuman_flip_spin_after_flip_energy)
{
    Neuman_f_spin test_spin(1, params, random_generator);
    
    std::array<const_base_pointer, 4> neighbours =
	{up_spin_p, up_spin_p, up_spin_p, down_spin_p};    
    test_spin.set_partners(neighbours);
    BOOST_CHECK_CLOSE_FRACTION(3, test_spin.after_flip_energy(), tolerance);
}

BOOST_AUTO_TEST_CASE(Neuman_flip_spin_step)
{
    Neuman_f_spin test_spin(1, params, random_generator);
    
    std::array<const_base_pointer, 4> neighbours =
	{up_spin_p, up_spin_p, down_spin_p, down_spin_p};    
    test_spin.set_partners(neighbours);

    std::size_t total_step = 10000;
    numerical_type mean_state = test_spin.get();
    for(std::size_t step = 0; step < total_step; ++step)
    {
	test_spin.step();
	mean_state += test_spin.get(); 
    }
    mean_state /= total_step;

    numerical_type theoretical_value = std::tanh(1);
    
    //tolerance is 5 * SD range.
    numerical_type depend_step_tolerance = 5.0 / (std::sqrt(12 * total_step));

    BOOST_CHECK_SMALL( mean_state - theoretical_value, depend_step_tolerance);
}

BOOST_AUTO_TEST_CASE(Neuman_flip_spin_reset_state)
{
    Neuman_f_spin test_spin(1, params, random_generator);
    
    std::size_t total_step = 10000;
    numerical_type mean_state = test_spin.get();
    for(std::size_t step = 0; step < total_step; ++step)
    {
	test_spin.reset_state();
	mean_state += test_spin.get(); 
    }
    mean_state /= total_step;

    numerical_type theoretical_value = 0.;
    
    //tolerance is 5 * SD range.
    numerical_type depend_step_tolerance = 5.0 / (std::sqrt(12 * total_step));

    BOOST_CHECK_SMALL( mean_state - theoretical_value, depend_step_tolerance);
}
