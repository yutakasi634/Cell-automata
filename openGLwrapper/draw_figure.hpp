#ifndef CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIGURE
#define CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIGURE

#include <GL/glut.h>

void drawpoint(float x_coordinate, float y_coordinate,
	       float size = 1.0,
	       float rgbr = 0, float rgbg = 0, float rgbb = 0)
{
    glColor3f(rgbr, rgbg, rgbb);
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2f(x_coordinate, y_coordinate);
    glEnd();
    return;
}

void drawquads(double x_coordinate, double y_coordinate,
	       double x_side, double y_side,
	       float rgbr = 0, float rgbg = 0, float rgbb = 0)
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

#endif /*  CELL_AUTOMATA_OPENGLWRAPPER_DRAWFIGURE */
