#ifndef CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIELD
#define CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIELD

#include <string>
#include <GL/glut.h>

template<typename window_traits>
void setWindow(int& argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(window_traits::window_side,
		       window_traits::window_side);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(window_traits::window_name);
    return;
}

void setBackground()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    return;
}

#endif /* CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIELD */
