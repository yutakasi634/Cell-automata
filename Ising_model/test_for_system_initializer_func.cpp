#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "../utilpack/array_matrix.hpp"
#include "system_initializer_func.hpp"
#include "Ising_simulator_traits.hpp"
#include "spin.hpp"

using simulator_traits			= Default_simulator_traits;
using spin_type			        = Neuman_flip_spin<simulator_traits>;
using system_type			= Utilpack::array_matrix<spin_type, 3, 3>;
using random_engine_type		= spin_type::random_engine_type;
using random_engine_pointer_type	= random_engine_type*;
using numerical_type			= spin_type::numerical_type;
using spin_params_type			= Spin_params<spin_type>;

numerical_type tempreture(1), magnetic_flux_density(1), spin_interaction(1);
spin_params_type spin_params(tempreture, magnetic_flux_density, spin_interaction);
random_engine_type random_engine(53);
random_engine_pointer_type random_engine_ptr = &random_engine;
system_type test_system;

BOOST_AUTO_TEST_CASE(set_spin_for_Neuman_flip_spin)
{
    set_spin<spin_type, 3, 3>(test_system, spin_params, random_engine_ptr);
}

BOOST_AUTO_TEST_CASE(set_row_partner_for_Neuman_flip_spin)
{
    set_spin<spin_type, 3, 3>(test_system, spin_params, random_engine_ptr);
    for(std::size_t row = 0; row < 3; ++row)
	set_row_spin_partner<3, 3, spin_type::simulator_traits>(test_system, row);
}

BOOST_AUTO_TEST_CASE(set_spin_partner_for_Neuman_flip_spin)
{
    set_spin<spin_type, 3, 3>(test_system, spin_params, random_engine_ptr);
    set_spin_partner<spin_type, 3, 3>(test_system);
}


BOOST_AUTO_TEST_CASE(system_initialize_for_Neuman_flip_spin)
{
    system_initialize<spin_type, 3, 3>(test_system, spin_params, random_engine_ptr);

    std::array<spin_type::const_base_pointer, 4>
	correct_partner{ &test_system.at(0,1), &test_system.at(1,2),
	    &test_system.at(2,1), &test_system.at(1,0)};
    std::array<spin_type::const_base_pointer, 4>
	test_partner = test_system.at(1,1).get_partners();
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
	test_partner.begin(), test_partner.end(),
	correct_partner.begin(), correct_partner.end());

    
    correct_partner = { &test_system.at(2,0), &test_system.at(0,1),
	    &test_system.at(1,0), &test_system.at(0,2)};
    test_partner = test_system.at(0,0).get_partners();

    BOOST_CHECK_EQUAL_COLLECTIONS(
	test_partner.begin(), test_partner.end(),
	correct_partner.begin(), correct_partner.end());

    
    correct_partner = { &test_system.at(1,2), &test_system.at(2,0),
	    &test_system.at(0,2), &test_system.at(2,1)};
    test_partner = test_system.at(2,2).get_partners();
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
	test_partner.begin(), test_partner.end(),
	correct_partner.begin(), correct_partner.end());

}

