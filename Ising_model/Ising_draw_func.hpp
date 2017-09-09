#ifndef CELL_AUTOMATA_ISING_SYSTEM_ISING_DRAW_FUNC
#define CELL_AUTOMATA_ISING_SYSTEM_ISING_DRAW_FUNC

#include <iostream>
#include <GL/glut.h>
#include "../openGLwrapper/make_canvas.hpp"
#include "../openGLwrapper/draw_figure.hpp"
#include "Ising_simulator.hpp"
#include "spin.hpp"
#include "Ising_simulator_traits.hpp"
#include "Ising_window_traits.hpp"
#include "Ising_global_variable.hpp"

template<typename window_traits>
void draw_pixel()
{
    const std::size_t row_n = Ising_field_ptr->row_num();
    const std::size_t column_n = Ising_field_ptr->column_num();
    constexpr float margin = window_traits::margin;
    constexpr float frame_size = 2 - 2.0 * margin;
    
    const double x_point_gap = frame_size / row_n;
    const double y_point_gap = frame_size / column_n;
    const float point_size = window_traits::window_side / system_side_num;

    const double initial_x_coord = -1 + margin + x_point_gap * 0.5;
    const double initial_y_coord = -1 + margin + y_point_gap * 0.5;
    
    double x_coord = initial_x_coord;
    double y_coord = initial_y_coord;
    for(std::size_t row = 0; row < row_n; ++row){
	for(std::size_t column = 0; column < column_n; ++column){
	    if(Ising_field_ptr->at(row, column).get() == 1)
		drawpoint(x_coord, y_coord, point_size);
	    x_coord += x_point_gap;
	}
	x_coord = initial_x_coord;
	y_coord += y_point_gap;
    }
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

template<typename window_traits>
void set_canvas(int& argc, char** argv)
{
    setWindow<window_traits>(argc, argv);
    setBackground();
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display<window_traits>);
    return;
}

void draw_canvas()
{
    ++step;
    std::cout << step * interval_calculation << " ";
    for(std::size_t roop = 0; roop < interval_calculation; ++roop)
	Ising_simulator_ptr->step();
    glutPostRedisplay();
    std::cout << std::endl;
    return;
}

void update_canvas(bool flag)
{
    if(flag)
	glutIdleFunc(draw_canvas);
    else
	glutIdleFunc(0);
    return;
}

void update_roop()
{
    glutMainLoop();
    return;
}


#endif /* CELL_AUTOMATA_ISING_SYSTEM_ISING_DRAW_FUNC */
