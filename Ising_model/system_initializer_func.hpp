#ifndef CELL_AUTOMATA_ISING_CONFIGURATOR
#define CELL_AUTOMATA_ISING_CONFIGURATOR

#include "../utilpack/array_matrix.hpp"
#include "spin_params.hpp"
#include "spin.hpp"


//set_row_spin_partner have to be overloded for each spin type.

//overload for Neuman_flip_spin
template<std::size_t R, std::size_t C, typename simulator_T>
void set_row_spin_partner(
    Utilpack::
    array_matrix<Neuman_flip_spin<simulator_T>, R, C>& system,
    const std::size_t row)
{
    std::size_t previous_row, next_row;
    if(row == 0){
	previous_row = system.row_num() - 1; next_row = 1;}
    else if(row == system.row_num() - 1){
	previous_row = row - 1; next_row = 0;}
    else{
	previous_row = row - 1; next_row = row + 1;}

    system.at(row, 0).set_partners(
	{&system.at(previous_row, 0), &system.at(row, 1), &system.at(next_row, 0),
		&system.at(row, system.column_num() - 1)});
    for(std::size_t column = 1; column < system.column_num() - 1; ++column)
	system.at(row, column).set_partners(
	    {&system.at(previous_row, column), &system.at(row, column + 1),
		    &system.at(next_row, column), &system.at(row, column -  1)});
    system.at(row, system.column_num() - 1).set_partners(
	{&system.at(previous_row, system.column_num() - 1),
		&system.at(row, 0),
		&system.at(next_row, system.column_num() -1),
		&system.at(row, system.column_num() - 2)});
    
    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~set_spin_partner()~~~~~~~~~~~~~~~~~~~~~~~~END

template<typename spin_T, std::size_t R, std::size_t C>
void set_spin_partner(Utilpack::array_matrix<spin_T, R, C>& system)
{
    for(std::size_t row = 0; row < system.row_num(); ++row)
	set_row_spin_partner<
	    R, C, typename spin_T::simulator_traits>(system, row);
    return;
}

template<typename spin_T, std::size_t R, std::size_t C>
void set_spin(Utilpack::array_matrix<spin_T, R, C>& system,
	      const Spin_params<spin_T>& params,
	      const typename spin_T::random_engine_pointer_type random_engine_ptr)
{
    for(spin_T& spin : system)
	spin = spin_T(params, random_engine_ptr);
    return;
}

template<typename spin_T, std::size_t R, std::size_t C>
void system_initialize(
    Utilpack::array_matrix<spin_T, R, C>& system,
    const Spin_params<spin_T>& params,
    const typename spin_T::random_engine_pointer_type random_engine_ptr)
{
    set_spin<spin_T, R, C>(system, params, random_engine_ptr);
    set_spin_partner<spin_T, R, C>(system);
    return;
}

#endif /* CELL_AUTOMATA_ISING_CONFIGURATOR */
