#ifndef CELL_AUTOMATA_OPENGLWRAPPER_DRAWQUADS
#define CELL_AUTOMATA_OPENGLWRAPPER_DRAWQUADS

#include <GL/glut.h>

void drawquads(double x_coordinate, double y_coordinate,
	       double x_side, double y_side,
	       double rgbr = 0, double rgbg = 0, double rgbb = 0)
{
    double half_x_side = x_side * 0.5;
    double half_y_side = y_side * 0.5;
    
    glColor3f(rgbr, rgbg, rgbb);
    glBegin(GL_QUADS);
    glVertex2f(x_coordinate - half_x_side, y_coordinate - half_y_side);
    glVertex2f(x_coordinate - half_x_side, y_coordinate + half_y_side);
    glVertex2f(x_coordinate + half_x_side, y_coordinate + half_y_side);
    glVertex2f(x_coordinate + half_x_side, y_coordinate - half_y_side);
    glEnd();
    return;
}

#endif /*  CELL_AUTOMATA_OPENGLWRAPPER_DRAWQUADS */
