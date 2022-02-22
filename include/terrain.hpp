// Library for the Terrain class

#ifndef TERRAIN_H
#define TERRAIN_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "utils.hpp"

class Terrain
{
private:
    Point center;
    Color color;
    GLfloat width;
    GLfloat height;

public:
    Terrain(Point center, GLfloat width, GLfloat height, Color color)
    {
        this->center = center;
        this->width = width;
        this->height = height;
        this->color = color;
    }

    // Draw Terrain object
    void draw_terrain();

    void set_vertex(Point p);
    Point get_center();
    Color get_color();
    GLfloat get_width();
    GLfloat get_height();

    void set_color(Color c);
};

#endif /* TERRAIN_H */
