#ifndef CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIELD
#define CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIELD

#include <string>
#include <GL/glut.h>

template<typename window_traits>
void setWindow(int& argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(window_traits::window_x_size,
		       window_traits::window_y_size);
    glutCreateWindow(window_traits::window_name);
    return;
}

void setBackground()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);	
    glClearColor(1.0, 1.0, 1.0, 1.0);
    return;
}

#endif /* CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIELD */
