#ifndef CELL_AUTOMATA_ISING_CONFIGURATOR
#define CELL_AUTOMATA_ISING_CONFIGURATOR

#include "../utilpack/array_matrix.hpp"
#include "spin.hpp"

template<typename spin_T, std::size_t row_Num, std::size_t column_Num, typename simulator_T>
class System_initializer;

template<std::size_t row_Num, std::size_t column_Num, typename simulator_T>
class System_initializer<Neuman_flip_spin>
{
    using array_matrix		= Utilpack::array_matrix<spin_T*, row_Num, column_Num>;
    using numerical_type	= simulator_T::numerical_T;
    
    void initialize(array_matrix&, numerical_type, numerical_type, numerical_type);
    void set_spin(array_matrix&, numerical_type, numerical_type, numerical_type);
    void set_spin_partner(array_matrix&);
    void set_row_spin_partner(array_matrix&);
    
};

template<std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void System_initializer<Neuman_flip_spin>::initialize(
    typename System_initializer::array_matrix& system,
    typename System_initializer::numerical_type tempreture,
    typename System_initializer::numerical_type magnetic_flux_density,
    typename System_initializer::numerical_type spin_interaction)
{
    set_spin(system, tempreture, magnetic_flux_density, spin_interaction);
    set_spin_partner(system);
    return;
}

template<std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void System_initializer<Neuman_flip_spin>::set_spin(
    typename System_initializer<Neuman_flip_spin>::array_matrix& system,
    typename System_initializer<Neuman_flip_spin>::numerical_type tempreture,
    typename System_initializer<Neuman_flip_spin>::numerical_type magnetic_flux_density,
    typename System_initializer<Neuman_flip_spin>::numerical_type spin_interaction)
{
    for(spin_T* spin_pointer : system)
	spin_pointer = new Neuman_flip_spin();
    return;
}

template<std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void System_initializer<Neuman_flip_spin>::set_spin_partner(
    typename System_initializer<Neuman_flip_spin>::array_matrix& system)
{
    set_row_spin_partner(system, 0, row_Num, 1);
    for(std::size_t row; row < row_Num - 1; ++row)
	set_row_spin_partner(system, row, row - 1, row + 1);
    set_row_spin_partner(system, row_Num, row_Num - 1, 0);
    return;
}

template<std::size_t row_Num, std::size_t column_Num, typename simulator_T>
void System_initializer<Neuman_flip_spin>::set_row_spin_partner(
    array_matrix& system, std::size_t row, std::size_t previous_row,
    std::size_t next_row)
{
    system.at(row, 0).set_partners(
	{&system.at(previous_row, 0), &system.at(row, 1), &system.at(next_row, 0),
		&system.at(row, column_Num)});
    for(std::size_t column = 1; column < column_Num - 1; ++column)
	system.at(row, column).set_partners(
	    {&system.at(previous_row, column), &system.at(row, column + 1),
		    &system.at(next_row, column), &system.at(row, column -  1)});
    system.at(row, column_Num).set_partners(
	{&system.at(previous_row, column_Num),&system.at(row, 0),
		&system.at(next_row, column_Num), &system(row, column_Num - 1)});
    return;
}

#endif /* CELL_AUTOMATA_ISING_CONFIGURATOR */
