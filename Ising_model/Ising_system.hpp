#ifndef CELL_AUTOMATA_ISING_SYSTEM
#define CELL_AUTOMATA_ISING_SYSTEM

#include "../utilpack/array_matrix.hpp"
#include "spin.hpp"

template<typename spin_T, std::size_t row_Num, std::size_t column_Num, typename simulator_T>
class Ising_system
{
    using random_engine_type	= simulator_T::random_engine_type;
    using numerical_type	= simulator_T::numerical_type;
    using array_matrix		= Utilpack::array_matrix<spin_T, row_Num, column_Num>;
    
  public:
    Ising_system(random_engine_type& ran_e):random_engine(ran_e){};

  private:
    array_matrix system;
    random_engine_type& random_engine;
};

#endif /* CELL_AUTOMATA_ISING_SYSTEM */
