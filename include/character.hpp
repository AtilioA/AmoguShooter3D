#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "utils.hpp"
#include "terrain.hpp"

// Enum representing the different directions a Character can face
enum Direction : GLint
{
    LEFT = -1,
    RIGHT = 1
};

class Character // abstract class
{
protected:
    /* Position */
    GLint id;
    Point center;
    GLdouble speed;
    Terrain *terrainBelow;

    /* Geometry */
    GLdouble radius;
    GLdouble height;
    GLdouble trunkWidth;

    /* Style */
    Color visorColor;
    CrewmateColors colors;

    /* Combat */
    bool isAlive;
    GLdouble lastTimeFired;
    GLdouble reloadTime;

    /* Walking */
    GLint facingDirection;
    bool isWalking;
    bool isWalkingObserve;

    /* Jumping */
    // Three booleans is certainly redundancy, but it's easier to think through
    bool canJump;
    bool isJumping;
    bool isFalling;
    GLfloat jumpTime;
    GLfloat jumpSpeed;
    GLfloat jumpInitialY;
    GLfloat gThetaBody;

    /* Angle of each joint */
    GLfloat gThetaThigh;
    GLfloat gThetaLeg;
    GLfloat gThetaLegLIMIT;
    GLfloat gThetaArm;
    GLfloat gThetaArmMAX;
    GLfloat gThetaArmMIN;

public:
    Character(Point center, GLfloat radius, CrewmateColors colors, GLint id)
    {
        this->set_id(id);
        this->set_center(center);
        this->set_radius(radius);
        this->visorColor = DEFAULT_VISOR_COLOR;
        this->set_crewmate_colors(colors);
        this->set_height(radius * 2);
        this->trunkWidth = radius;
        this->speed = (radius / 200);
        this->set_terrain_below(NULL);

        this->gThetaArm = 0;
        this->gThetaArmMIN = -45;
        this->gThetaArmMAX = 45;
        this->gThetaLeg = 0;
        this->gThetaThigh = 0;
        this->gThetaLegLIMIT = 15;
        this->gThetaBody = 0;

        // Each Character starts facing right and walking in obverse direction
        this->facingDirection = Direction::RIGHT;
        this->isWalkingObserve = true;

        this->isAlive = true;
        this->lastTimeFired = 0;
        // Each Character gets a random reload time between 0.1 and 1.1 seconds
        this->reloadTime = (rand() % 1001) + 100; // milliseconds

        this->canJump = true;
        this->isJumping = false;
        this->isFalling = false;
        this->jumpTime = 0;
        this->jumpSpeed = (this->height / 3) * this->speed; // 3x player height in 1 second
        this->jumpInitialY = center.y;
    };
    virtual ~Character(){};

    /* Jumping interface */
    void jump(GLfloat clock);
    GLfloat get_jump_speed();

    void set_is_falling(bool isFalling);
    bool get_is_falling();

    void set_is_jumping(bool isJumping);
    bool get_is_jumping();

    void set_can_jump(bool canJump);
    bool get_can_jump();

    void set_jump_time(GLfloat jumpTime);
    GLfloat get_jump_time();

    void set_jump_initial_y(GLfloat y);
    GLfloat get_jump_initial_y();

    /* Combat interface */
    bool is_alive();

    void set_alive(bool alive);
    GLdouble get_last_time_fired();

    GLdouble get_reload_time();
    void set_last_time_fired(GLdouble lastTimeFired);

    void set_reload_time(GLdouble reloadTime);
    void set_id(GLint id);

    GLint get_id();

    /* Colors interface */
    void set_visor_color(Color visorColor);
    Color get_visor_color();

    void set_crewmate_colors(CrewmateColors c);
    CrewmateColors get_crewmate_colors();

    /* Position/Geometry interface */
    void set_center(Point p);
    Point get_center();

    void set_radius(GLdouble r);
    GLdouble get_radius();

    void set_height(GLdouble h);
    GLdouble get_height();

    void set_trunk_width(GLdouble t);
    GLdouble get_trunk_width();

    void set_speed(GLdouble speed);
    GLdouble get_speed();

    /* Collision interface */
    bool is_inside_another_character(Character *character);
    bool is_inside_terrain(Terrain *terrain);
    void set_terrain_below(Terrain *terrain);
    Terrain *get_terrain_below();

    /* Animation interface */
    void move_character(GLfloat dx, GLfloat dy, GLfloat frameTime);
    void set_facing_direction(GLint facingDirection);
    GLint get_facing_direction();

    /* Drawing interface */
    void draw_character();
    void draw_left_thigh();
    void draw_left_leg();
    void draw_right_thigh();
    void draw_right_leg();
    void draw_body();
    void draw_arm();
    void draw_head();
    void determine_animation_direction();

    /* Joint rotation interface */
    void move_arm_mouse_helper(GLfloat yMouse, GLfloat *oldY);
    void rotate_arm(GLfloat inc);
    void rotate_thigh(GLfloat inc);
    void rotate_leg(GLfloat inc);
    void set_theta_arm(GLfloat theta);
    GLfloat get_theta_arm();
    void change_theta_body(GLfloat dTheta, GLfloat frameTime);
    GLfloat get_theta_body();
};

#endif /* CHARACTER_H */
