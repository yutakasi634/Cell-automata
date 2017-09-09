#include <iostream>
#include <GL/glut.h>
#include "Ising_simulator.hpp"
#include "spin.hpp"
#include "Ising_simulator_traits.hpp"
#include "Ising_window_traits.hpp"
#include "Ising_draw_func.hpp"
#include "Ising_model_parameters.hpp"
#include "Ising_global_val.hpp"

int main(int argc, char *argv[]){
    Ising_simulator_ptr = new simulator_type
    	(random_seed, tempreture, magnetic_flux_density, spin_interaction);
    
    Ising_field_ptr = &(Ising_simulator_ptr->spins_state());
    
    set_canvas<Ising_window_traits>(argc ,argv);    
    update_canvas(true);
    update_roop();

    delete Ising_simulator_ptr;
    
    return 0;
}


