#ifndef GUNSHOT_H
#define GUNSHOT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../include/utils.hpp"
#include "../include/character.hpp"
#include "../include/terrain.hpp"

class Character;
class Gunshot
{
    // The ID of the Character that shot the bullet
    GLint shooterID;
    GLdouble gXInit;
    GLdouble gYInit;
    GLdouble gZInit;
    GLdouble gX;
    GLdouble gY;
    GLdouble gZ;
    GLfloat gDirectionXYAng;
    GLfloat gDirectionXZAng;
    GLdouble gVel;
    GLdouble gRadiusGunshot;
    GLint facingDirection;
    Color color;

private:
    void draw_sphere(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw_bullet(GLdouble x, GLdouble y, GLdouble z);

public:
    Gunshot(GLint shooterID, GLdouble x, GLdouble y, GLdouble z, GLdouble charSpeed, GLdouble charRadius, GLfloat directionXYAng, GLfloat directionXZAng, GLint facingDirection, Color crewmateUpperBody)
    {
        this->shooterID = shooterID;
        this->gXInit = x;
        this->gYInit = y;
        this->gZInit = y;
        this->gX = x;
        this->gY = y;
        this->gZ = z;
        this->gDirectionXYAng = directionXYAng;
        this->gDirectionXZAng = directionXZAng;
        // The Gunshot speed must be 2 times the character's speed
        this->gVel = charSpeed * 2;
        // We define the gunshot radius as one quarter of the character's radius
        this->gRadiusGunshot = charRadius / 4;
        this->facingDirection = facingDirection;
        this->color = crewmateUpperBody;
    };

    // Draw the gunshot at the current position
    void draw_gunshot();
    // Move gunshot position normalized to the game's frametime
    void move_gunshot(GLdouble frameTime);

    // Check if the Gunshot has collided with a Character
    bool is_inside_character(Character *character);
    // Check if the Gunshot has collided with a Terrain
    bool is_inside_terrain(Terrain *terrain);

    GLint get_shooter_id();

    GLfloat get_radius();
    Point get_center();
};

#endif /* GUNSHOT_H */
