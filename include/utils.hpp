// Library for utilitary functions and structs

#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <string>
#include <bits/stdc++.h>

#include <GL/glut.h>

#define M_PI 3.14159265358979323846

// Default visor color
#define DEFAULT_VISOR_COLOR Color({1.0, 1.0, 1.0})

// Stores the size of a 2D window
typedef struct tDimensions
{
    GLdouble width;
    GLdouble height;
} Dimensions;

// Stores the coordinates of a point
typedef struct tPoint
{
    GLdouble x;
    GLdouble y;
} Point;

// Stores the RGB values of a color
typedef struct tColor
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
} Color;

// Stores the color for a Character (crewmate): upper body and lower body.
typedef struct tCrewmateColors
{
    tColor upperBody;
    tColor lowerBody;
} CrewmateColors;

// Picks the player color, which is RED in this case
CrewmateColors get_player_colors();

// Picks an color from the enemy colors at random, defaults to black color.
CrewmateColors get_random_enemy_colors();

// Determine the smallest dimension of a Dimensions instance
GLfloat smallest_dimension(Dimensions dimensions);

GLfloat rad_to_degrees(GLfloat rad);
GLfloat deg_to_radians(GLfloat deg);

#endif /* UTILS_H */
