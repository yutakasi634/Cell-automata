#ifndef CELL_AUTOMATA_ISING_CONFIGURATOR
#define CELL_AUTOMATA_ISING_CONFIGURATOR

#include "../utilpack/array_matrix.hpp"
#include "spin_params.hpp"
#include "spin.hpp"

template<typename spin_T, std::size_t row_Num, std::size_t column_Num>
void system_initialize(
    Utilpack::array_matrix<spin_T*, row_Num, column_Num>& system,
    spin_params<spin_T>& params
    typename spin_T::random_engine_type& random_engine);
{
    set_spin<spin_T, row_Num, column_Num>(system, params, random_engine);
    set_spin_partner<spin_T, row_Num, column_Num>(system);
    return;
}

template<typename spin_T, std::size_t row_Num, std::size_t column_Num>
void set_spin(Utilpack::array_matrix<spin_T*, row_Num, column_Num>& system,
	      spin_params<spin_T>& params,
	      typename spin_T::random_engine_type& random_engine);
{
    for(spin_T* spin_pointer : system)
	spin_pointer = new spin_T(params, random_engine);
    return;
}


template<typename spin_T, std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void set_spin_partner(Utilpack::array_matrix<spin_T*, row_Num, column_Num>& system)
{
    for(std::size_t row = 0; row < row_Num; ++row)
	set_row_spin_partner<row_Num, column_Num, simulator_T>(system, row);
    return;
}

//set_row_spin_partner have to be overloded for each spin type.

//overload for Neuman_flip_spin
template<std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void set_row_spin_partner(
    Utilpack::
    array_matrix<Neuman_flip_spin<simulator_T>*, row_Num, column_Num>& system,
    std::size_t row)
{
    std::size_t previous_row, next_row;
    if(row == 0)
	previous_row = row_Num; next_row = 1;
    else if(row == row_Num)
	previous_row = row_Num - 1; next_row = 0;
    else
	previous_row = row - 1; next_row = row + 1;

    system.at(row, 0)->set_partners(
	{&system.at(previous_row, 0), &system.at(row, 1), &system.at(next_row, 0),
		&system.at(row, column_Num)});
    for(std::size_t column = 1; column < column_Num - 1; ++column)
	system.at(row, column)->set_partners(
	    {&system.at(previous_row, column), &system.at(row, column + 1),
		    &system.at(next_row, column), &system.at(row, column -  1)});
    system.at(row, column_Num)->set_partners(
	{&system.at(previous_row, column_Num),&system.at(row, 0),
		&system.at(next_row, column_Num), &system(row, column_Num - 1)});
    
    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~set_spin_partner()~~~~~~~~~~~~~~~~~~~~~~~~END

#endif /* CELL_AUTOMATA_ISING_CONFIGURATOR */
