#include "../include/gunshot.hpp"

// Draw a sphere with given radius and RGB values
void Gunshot::draw_sphere(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R * 1.3, G * 1.3, B * 1.3);
    // TODO: Investigate params GLint slices, GLint stacks for glutSolidSphere
    glutSolidSphere(radius, 20, 20);
    glEnd();
}

void Gunshot::draw_gunshot()
{
    draw_bullet(this->gX, this->gY, this->gZ);
}

void Gunshot::draw_bullet(GLdouble x, GLdouble y, GLdouble z)
{
    glPushMatrix();

    glTranslatef(x, -y, -z);
    draw_sphere(this->gRadiusGunshot, this->color.r, this->color.g, this->color.b);

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
    // Check if the Gunshot is inside the Character in a 3D space considering that the character is drawn from the center to the edges.
    GLdouble xDistGunshot = abs(this->gX - character->get_center().x);
    GLdouble yDistGunshot = abs(this->gY - character->get_center().y);
    GLdouble zDistGunshot = abs(this->gZ - character->get_center().z);

    return ((xDistGunshot <= character->get_radius()) && (yDistGunshot <= character->get_radius()) && (zDistGunshot <= character->get_radius()));
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
