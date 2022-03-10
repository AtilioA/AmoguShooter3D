#include "../include/terrain.hpp"

// Import game to check debug options
#include "../include/game.hpp"
extern Game *game;

void Terrain::draw_terrain()
{
    glColor3f(this->color.r, this->color.g, this->color.b);

    glPushMatrix();

    glTranslatef(this->center.x, -this->center.y, 0);

    // Draw each face from the top left corner to the bottom right corner using GL_QUADS. Use the Terrain width, height, and length to determine the dimensions of each of the six faces.
    glBegin(GL_QUADS);

    // FRONT FACE
    glVertex3f(0, 0, 0);
    glVertex3f(this->width, 0, 0);
    glVertex3f(this->width, -this->height, 0);
    glVertex3f(0, -this->height, 0);

    // BACK FACE
    glVertex3f(0, 0, -this->length);
    glVertex3f(0, -this->height, -this->length);
    glVertex3f(this->width, 0, -this->length);
    glVertex3f(this->width, -this->height, -this->length);

    // TOP FACE
    glVertex3f(0, 0, 0);
    glVertex3f(this->width, 0, 0);
    glVertex3f(this->width, 0, -this->length);
    glVertex3f(0, 0, -this->length);

    // BOTTOM FACE
    glVertex3f(0, 0, -this->length);
    glVertex3f(this->width, 0, -this->length);
    glVertex3f(this->width, -this->height, -this->length);
    glVertex3f(0, -this->height, -this->length);

    // LEFT FACE
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -this->length);
    glVertex3f(0, -this->height, -this->length);
    glVertex3f(0, -this->height, 0);

    // RIGHT FACE
    glVertex3f(this->width, 0, 0);
    glVertex3f(this->width, 0, -this->length);
    glVertex3f(this->width, -this->height, -this->length);
    glVertex3f(this->width, -this->height, 0);

    glEnd();
    glPopMatrix();

    if (game->get_debug_options().drawObjectCenter)
    {
        // Draw borders/hitboxes for GL_QUADS faces in red
        glColor3f(1.0f, 0.0f, 0.0f);

        glPushMatrix();

        glTranslatef(this->center.x, -this->center.y, 0);

        // FRONT FACE
        glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, 0);
        glVertex3f(this->width, 0, 0);
        glVertex3f(this->width, -this->height, 0);
        glVertex3f(0, -this->height, 0);
        glEnd();

        // BACK FACE
        glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, -this->length);
        glVertex3f(this->width, 0, -this->length);
        glVertex3f(this->width, -this->height, -this->length);
        glVertex3f(0, -this->height, -this->length);
        glEnd();

        // LEFT FACE
        glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, -this->length);
        glVertex3f(0, -this->height, -this->length);
        glVertex3f(0, -this->height, 0);
        glEnd();

        // TOP FACE
        glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, 0);
        glVertex3f(this->width, 0, 0);
        glVertex3f(this->width, 0, -this->length);
        glVertex3f(0, 0, -this->length);
        glEnd();

        // BOTTOM FACE
        glBegin(GL_LINE_LOOP);
        glVertex3f(this->width, 0, 0);
        glVertex3f(this->width, 0, -this->length);
        glVertex3f(this->width, -this->height, -this->length);
        glVertex3f(this->width, -this->height, 0);
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

GLfloat Terrain::get_length()
{
    return this->length;
}

void Terrain::set_color(Color c)
{
    this->color = c;
}
