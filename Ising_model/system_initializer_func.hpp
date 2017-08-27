#ifndef CELL_AUTOMATA_ISING_CONFIGURATOR
#define CELL_AUTOMATA_ISING_CONFIGURATOR

#include "../utilpack/array_matrix.hpp"
#include "spin.hpp"

template<typename spin_T, std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void system_initialize(
    Utilpack::array_matrix_T<spin_T, row_Num, column_Num, simulator_T>&);

template<std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void system_initialize(
    Utilpack::array_matrix<Neuman_flip_spin*, row_Num, column_Num>& system)
{
    using numerical_type = simulator_T::numerical_T;
    set_spin<Neuman_flip_spin*, row_Num, column_Num, simulator_T>
	(system, tempreture, magnetic_flux_density, spin_interaction);
    set_spin_partner<row_Num, column_Num>(system);
    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~set_spin()~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template<typename spin_T, std::size_t row_Num, std::size_t, typename simulator_T>
void set_spin(Utilpack::array_matrix<spin_T, row_Num, column_Num>&,
	      simulator_T::numerical_T , simulator_T::numerical_T , simulator_T::numerical_T );


template<std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void set_spin(Utilpack::array_matrix<Neuman_flip_spin, row_Num, column_Num> system,
	      simulator_T::numerical_T tempreture,
	      simulator_T::numerical_T magnetic_flux_density,
	      simulator_T::numerical_T spin_interaction)
{
    for(spin_T spin_pointer : system)
	spin_pointer = Neuman_flip_spin(
	    tempreture, magnetic_flux_density, spin_interaction);
    return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~set_spin()~~~~~~~~~~~~~~~~~~~~~~~~~~~~END
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~set_spin_partner()~~~~~~~~~~~~~~~~~~~~~~~~~~~


template<typename spin_T, std::size_t row_Num, std::size_t column_Num>
void set_spin_partner(Utilpack::array_matrix<spin_T, row_Num, column_Num>& system)
{
    set_row_spin_partner<spin_T, >(system, 0, row_Num, 1);
    for(std::size_t row; row < row_Num - 1; ++row)
	set_row_spin_partner(system, row, row - 1, row + 1);
    set_row_spin_partner(system, row_Num, row_Num - 1, 0);
    return;
}

template<typename spin_T, std::size_t row_Num, std::size_t column_Num>
void set_row_spin_partner(Utilpack::array_matrix<spin_T, row_Num, column_Num>& system,
			  std::size_t row)
{
    std::size_t previous_row, next_row;
    if(row == 0)
	previous_row = row_Num; next_row = 1;
    else if(row == row_Num)
	previous_row = row_Num - 1; next_row = 0;
    else
	previous_row = row - 1; next_row = row + 1;

    systemat(row, 0)->set_partners(
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
