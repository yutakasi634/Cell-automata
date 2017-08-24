#ifndef CELL_AUTOMATA_ISING_SPIN_BASE
#define CELL_AUTOMATA_ISING_SPIN_BASE

#include <array>

template<typename value_T, std::size_t partner_Num>
class Spin_base
{    
  public:
    using state_type		= value_T;
    using base_pointer		= Spin_base*;
    using const_base_pointer    = const Spin_base*;
    using partners_list_type	= std::array<const_base_pointer, partner_Num>;
    
    Spin_base(){}
    Spin_base(state_type s):state(s){}

    virtual void step() = 0;
    virtual void set_partners(const partners_list_type&) = 0;
    virtual void reset_state() = 0;
    
    state_type get() const
    { return state; }
    void set(state_type s)
    { state = s; return; }
    
  protected:
    state_type state;
    partners_list_type partners;
};

#endif /* CELL_AUTOMATA_ISING_SPIN */
