#include <iostream>
#include <GL/glut.h>
#include "Ising_simulator.hpp"
#include "spin.hpp"
#include "Ising_simulator_traits.hpp"
#include "Ising_window_traits.hpp"
#include "../openGLwrapper/make_canvas.hpp"
#include "../openGLwrapper/drawquads.hpp"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~parameter set~~~~~~~~~~~~~~~~~~~~~~~~~~~

using numerical_type = Default_simulator_traits::numerical_type;

constexpr std::size_t system_row_num(250);
constexpr std::size_t system_column_num(250);
constexpr std::size_t display_interval(100);
constexpr std::size_t interval_calculation(10000);
constexpr int random_seed(53);
constexpr numerical_type tempreture(1);
constexpr numerical_type magnetic_flux_density(0.0);
constexpr numerical_type spin_interaction(0.5);

using simulator_type = Ising_simulator<
    Neuman_flip_spin, system_row_num, system_column_num, Default_simulator_traits>;

//~~~~~~~~~~~~~~~~~~~~~~~~global func declaration~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template<typename window_traits>
void set_canvas(int& argc, char** argv);

template<typename window_traits>
void draw_pixel();

template<typename window_traits>
void display();

void update_canvas(int);
//~~~~~~~~~~~~~~~~~~~~~~~~global variable declaration~~~~~~~~~~~~~~~~~~~~~~~~~~~

const simulator_type::array_matrix* Ising_field_ptr(nullptr);
simulator_type* Ising_simulator_ptr(nullptr); 
std::size_t step(0);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main(int argc, char *argv[]){
    Ising_simulator_ptr = new simulator_type
    	(random_seed, tempreture, magnetic_flux_density, spin_interaction);
    
    Ising_field_ptr = &(Ising_simulator_ptr->spins_state());
    
    set_canvas<Ising_window_traits>(argc ,argv);
    glutTimerFunc(display_interval, update_canvas, 0);
    glutMainLoop();
    
    delete Ising_simulator_ptr;
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~global func definition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template<typename window_traits>
void set_canvas(int& argc, char** argv)
{
    setWindow<window_traits>(argc, argv);
    setBackground();
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display<window_traits>);
    return;
}

template<typename window_traits>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_pixel<window_traits>();
    glutSwapBuffers();
    return;
}

void update_canvas(int value)
{
    ++step;
    std::cout << step * interval_calculation << std::endl;
    for(std::size_t roop = 0; roop < interval_calculation; ++roop)
	Ising_simulator_ptr->step();
    glutPostRedisplay();
    glutTimerFunc(display_interval, update_canvas, 0);
    return;
}

template<typename window_traits>
void draw_pixel()
{
    const std::size_t row_n = Ising_field_ptr->row_num();
    const std::size_t column_n = Ising_field_ptr->column_num();
    constexpr float margin = window_traits::margin;
    constexpr float frame_size = 2 - 2.0 * margin;
    const double x_pixel_size = frame_size / row_n;
    const double y_pixel_size = frame_size / column_n;

    const double initial_x_coord = -1 + margin + x_pixel_size * 0.5;
    const double initial_y_coord = -1 + margin + y_pixel_size * 0.5;

    double x_coord = initial_x_coord;
    double y_coord = initial_y_coord;
    for(std::size_t row = 0; row < row_n; ++row){
	for(std::size_t column = 0; column < column_n; ++column){
	    if(Ising_field_ptr->at(row, column).get() == 1)
		drawquads(x_coord, y_coord, x_pixel_size, y_pixel_size);
	    x_coord += x_pixel_size;
	}
	x_coord = initial_x_coord;
	y_coord += y_pixel_size;
    }
    return;
}

