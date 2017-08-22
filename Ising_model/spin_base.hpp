#ifndef CELL-AUTOMATA-ISING-SPIN-BASE
#define CELL-AUTOMATA-ISING-SPIN-BASE

template<typename value_T>
class spin_base
{
    using state_type		= value_T;
  public:
    spin_base(state_type s):state(s){}

    state_type get() const
    { return state; }
    void set(state_type s)
    { state = s; return; }
    virtual void step() = 0;
    
  private:
    state_type state;
}

#endif /* CELL-AUTOMATA-ISING-SPIN */
