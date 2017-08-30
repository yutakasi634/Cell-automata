#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "../utilpack/array_matrix.hpp"
#include "Ising_simulator_traits.hpp"
#include "Ising_system.hpp"

using simulator_traits		= Default_simulator_traits;
using spin_type			= Neuman_flip_spin<simulator_traits>;

using Ising_system_type		= Ising_system<spin_type, 3, 3>;
using numerical_type		= typename Default_simulator_traits::numerical_type;
using random_engine_type	= typename Default_simulator_traits::random_engine_type;
using spin_params_type		= Spin_params<spin_type>;

numerical_type tempreture(1), magnetic_flux_density(1), spin_interaction(1);
spin_params_type spin_params(tempreture, magnetic_flux_density, spin_interaction);
random_engine_type random_engine(53);

BOOST_AUTO_TEST_CASE(constructor_check_for_neuman_case)
{
    Ising_system_type test_system(spin_params, random_engine);
}

BOOST_AUTO_TEST_CASE(initialize_for_neuman_case)
{
    Ising_system_type test_system{};
    test_system.initialize(spin_params, random_engine);
}

BOOST_AUTO_TEST_CASE(reset_state_for_neuman_case)
{
    Ising_system_type test_system(spin_params, random_engine);
    test_system.reset_states();
}

BOOST_AUTO_TEST_CASE(step_for_neuman_case)
{
    Ising_system_type test_system(spin_params, random_engine);
    test_system.step();
}
