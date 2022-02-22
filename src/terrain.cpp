#include "../include/terrain.hpp"

// Import game to check debug options
#include "../include/game.hpp"
extern Game *game;

void Terrain::draw_terrain()
{
    glColor3f(this->color.r, this->color.g, this->color.b);

    glPushMatrix();

    glTranslatef(this->center.x, -this->center.y, 0);

    // Draw terrain from the top left corner to the bottom right corner
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(this->width, 0);
    glVertex2f(this->width, -this->height);
    glVertex2f(0, -this->height);
    glEnd();
    glPopMatrix();

    if (game->get_debug_options().drawObjectCenter)
    {
        // Draw dot at the center of the terrain
        glPushMatrix();
        glTranslatef(this->center.x, -this->center.y, 0);
        glPointSize(3);

        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glEnd();
        glPopMatrix();

        // Draw borders/hitboxes in red
        glPushMatrix();
        glTranslatef(this->center.x, -this->center.y, 0);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0, 0);
        glVertex2f(this->width, 0);
        glVertex2f(this->width, -this->height);
        glVertex2f(0, -this->height);
        glEnd();
        glPopMatrix();
    }
}

Point Terrain::get_center()
{
    return this->center;
}

Color Terrain::get_color()
{
    return this->color;
}

GLfloat Terrain::get_width()
{
    return this->width;
}

GLfloat Terrain::get_height()
{
    return this->height;
}

void Terrain::set_color(Color c)
{
    this->color = c;
}
