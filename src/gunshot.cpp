#include "../include/gunshot.hpp"

// TODO: change to sphere
void Gunshot::draw_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R * 1.3, G * 1.3, B * 1.3);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        glVertex2f(radius * 1 * cos(deg_to_radians(i)), radius * 1 * sin(deg_to_radians(i)));
    }
    glEnd();
}

void Gunshot::draw_gunshot()
{
    draw_bullet(this->gX, this->gY, this->gZ);
}

void Gunshot::draw_bullet(GLdouble x, GLdouble y, GLdouble z)
{
    glPushMatrix();
    glTranslatef(x, -y, 0);
    draw_circ(this->gRadiusGunshot, this->color.r, this->color.g, this->color.b);
    glPopMatrix();
}

void Gunshot::move_gunshot(GLdouble frameTime)
{
    /* Move the Gunshot considering the direction and the speed.
     * The angle must be converted to radians for the trigonometric functions.
     * The frameTime is used to normalize the movement. */
    this->gX += this->gVel * sin(deg_to_radians(this->gDirectionAng)) * frameTime;
    this->gY += this->gVel * cos(deg_to_radians(this->gDirectionAng)) * frameTime;
    // this->gZ += this->gVel * ...(deg_to_radians(this->gDirectionAng)) * frameTime;
}

bool Gunshot::is_inside_character(Character *character)
{
    // TODO: Also use Z to check if the Gunshot is inside the Character

    // Check if the Gunshot is inside the Character considering that the character is drawn from the center to the edges (hence the divisions by 2)
    if (this->gX + this->gRadiusGunshot > character->get_center().x - character->get_trunk_width() / 2 &&
        this->gX - this->gRadiusGunshot < character->get_center().x + character->get_trunk_width() / 2 && this->gY + this->gRadiusGunshot > character->get_center().y - character->get_radius() &&
        this->gY - this->gRadiusGunshot < character->get_center().y + character->get_radius())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Gunshot::is_inside_terrain(Terrain *terrain)
{
    // TODO: Also use Z to check if the Gunshot is inside the Terrain

    Point terrainPos = terrain->get_center();

    // Check if the Gunshot is inside the Terrain considering that the terrain is drawn from the top left corner to the bottom right corner
    if (this->gY + this->gRadiusGunshot >= terrainPos.y &&
        this->gY - this->gRadiusGunshot <= terrainPos.y + terrain->get_height())
    {
        if (this->gX + this->gRadiusGunshot >= terrainPos.x && this->gX - this->gRadiusGunshot <= terrainPos.x + terrain->get_width())
        {
            return true;
        }
    }

    return false;
}

GLint Gunshot::get_shooter_id()
{
    return this->shooterID;
}

GLfloat Gunshot::get_radius()
{
    return this->gRadiusGunshot;
}

Point Gunshot::get_center()
{
    return {this->gX, this->gY, this->gZ};
}
