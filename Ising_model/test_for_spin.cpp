#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "spin.hpp"
#include <iostream>
#include <array>
#include <cmath>

using numerical_type		= Default_traits::numerical_type;
using random_engine_type	= Default_traits::random_number_generator_type;
using Spin			= Neuman_flip_spin<Default_traits>;
using base_pointer		= Spin::base_pointer;
using const_base_pointer	= Spin::const_base_pointer;

float tolerance = 1e-5;//tolerance for BOOST_CHECK_CLOSE_FRACTION.

random_engine_type random_generator(53);
numerical_type tempreture(1), magnetic_flux_density(1), spin_interaction(1);
const Spin up_spin(1, tempreture, magnetic_flux_density,spin_interaction,
		   random_generator), 
    down_spin(-1, tempreture, magnetic_flux_density, spin_interaction,
	      random_generator);
const_base_pointer up_spin_p = &up_spin, down_spin_p = &down_spin;



BOOST_AUTO_TEST_CASE(Neuman_flip_spin_constructor)
{
    
    BOOST_CHECK_THROW(Spin error_spin(2, tempreture, magnetic_flux_density,
				      spin_interaction, random_generator),
		      std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(Neuman_flip_spin_current_energy)
{
    Spin test_spin(1, tempreture, magnetic_flux_density, spin_interaction,
		   random_generator);
    
    std::array<const_base_pointer, 4> neighbours =
	{up_spin_p, up_spin_p, up_spin_p, down_spin_p};    
    test_spin.set_partners(neighbours);
    BOOST_CHECK_CLOSE_FRACTION(-3, test_spin.current_energy(), tolerance);
}

BOOST_AUTO_TEST_CASE(Neuman_flip_spin_after_flip_energy)
{
    Spin test_spin(1, tempreture, magnetic_flux_density, spin_interaction,
		   random_generator);
    
    std::array<const_base_pointer, 4> neighbours =
	{up_spin_p, up_spin_p, up_spin_p, down_spin_p};    
    test_spin.set_partners(neighbours);
    BOOST_CHECK_CLOSE_FRACTION(3, test_spin.after_flip_energy(), tolerance);
}

BOOST_AUTO_TEST_CASE(Neuman_flip_spin_step)
{
    Spin test_spin(1, tempreture, magnetic_flux_density, spin_interaction,
		   random_generator);
    
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
    
    //tolerance is 5 * SD range. Probability is 99.9999%.
    numerical_type depend_step_tolerance = 5.0 / (std::sqrt(12 * total_step));

    BOOST_CHECK_SMALL( mean_state - theoretical_value, depend_step_tolerance);
}


