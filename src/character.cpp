#include "../include/character.hpp"

// Import game to check debug options
#include "../include/game.hpp"
extern Game *game;

bool Character::is_alive()
{
    return this->isAlive;
}

void Character::set_alive(bool alive)
{
    this->isAlive = alive;
}

void Character::set_last_time_fired(GLdouble lastTimeFired)
{
    this->lastTimeFired = lastTimeFired;
}
GLdouble Character::get_last_time_fired()
{
    return this->lastTimeFired;
}

void Character::set_reload_time(GLdouble reloadTime)
{
    this->reloadTime = reloadTime;
}
GLdouble Character::get_reload_time()
{
    return this->reloadTime;
}

void Character::move_arm_mouse_helper(GLfloat yMouse, GLfloat *oldY)
{
    // Initialize oldY with current mouse position if it hasn't been initialized yet
    if (oldY == 0)
    {
        *oldY = yMouse;
    }

    // Calculate the difference between the current mouse position and the last mouse position
    GLfloat deltaY = yMouse - *oldY;

    // Update arm's angle considering mouse sensitivity and Character's facing direction as well
    this->gThetaArm += deltaY * MOUSE_SENSITIVITY * -this->facingDirection;

    // Don't let the arm go past the max or min angles
    if (this->gThetaArm > this->gThetaArmMAX)
    {
        this->gThetaArm = this->gThetaArmMAX;
    }
    if (this->gThetaArm < this->gThetaArmMIN)
    {
        this->gThetaArm = this->gThetaArmMIN;
    }
    // Update the old mouse position
    *oldY = yMouse;
}

void Character::draw_head()
{
    glColor3f(this->visorColor.r, this->visorColor.g, this->visorColor.b);

    // if (this->facingDirection == Direction::RIGHT)
    // {
        glBegin(GL_POLYGON);
        // clang-format off
            glVertex2f(-this->trunkWidth / 2, 0);
            glVertex2f(this->trunkWidth / 1.75, 0);
            glVertex2f(this->trunkWidth / 1.75, this->height / 8);
            glVertex2f(-this->trunkWidth / 2, this->height / 8);
        // clang-format on
        glEnd();
    // }
    // else
    // {
    //     glBegin(GL_POLYGON);
    //     // clang-format off
    //         glVertex2f(-this->trunkWidth / 1.75, 0);
    //         glVertex2f(this->trunkWidth / 2, 0);
    //         glVertex2f(this->trunkWidth / 2, this->height / 8);
    //         glVertex2f(-this->trunkWidth / 1.75, this->height / 8);
    //     // clang-format on
    //     glEnd();
    // }
}

void Character::draw_body()
{
    glColor3f(this->colors.upperBody.r, this->colors.upperBody.g, this->colors.upperBody.b);

    GLfloat materialEmission[] = {0.00, 0.00, 0.00, 1.0};
    GLfloat materialColor[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {128};
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTranslatef(0, this->height / 8 * 2.5, 0);

    glScalef(1, this->height / this->trunkWidth / 1.5, 1);
    glutSolidCube(this->trunkWidth);

    // glBegin(GL_POLYGON);
    // // clang-format off
    //     glVertex2f(-this->trunkWidth / 2, 0);
    //     glVertex2f(this->trunkWidth / 2, 0);
    //     glVertex2f(this->trunkWidth / 2, this->height / 8 * 5);
    //     glVertex2f(-this->trunkWidth / 2, this->height / 8 * 5);
    // // clang-format on
    // glEnd();
}

// 4/8 / 2
void Character::draw_left_thigh()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b);

    // Draw thigh animation according to the facing direction
    if (this->facingDirection == Direction::RIGHT)
    {
        glRotatef(this->gThetaLeg, 0, 0, 1);
    }
    else
    {
        glRotatef(-this->gThetaLeg, 0, 0, 1);
    }

    // glRotatef(this->gThetaLeg, 0, 0, 1);

    glutSolidCube(this->trunkWidth / 3);
}

// 4/8 / 2
void Character::draw_left_leg()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b);

    // Draw left animation according to the facing direction
    if (this->facingDirection == Direction::LEFT)
    {
        glRotatef(-this->gThetaLeg, 0, 0, 1);
        glRotatef(15, 0, 0, 1);
    }
    else
    {
        glRotatef(this->gThetaLeg, 0, 0, 1);
        glRotatef(-30, 0, 0, 1);
    }

    glutSolidCube(this->trunkWidth / 3);
}

// 4/8 / 2
void Character::draw_right_thigh()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b);

    // Draw thigh animation according to the facing direction
    if (this->facingDirection == Direction::RIGHT)
    {
        glRotatef(-this->gThetaLeg, 0, 0, 1);
    }
    else
    {
        glRotatef(this->gThetaLeg, 0, 0, 1);
    }

    // glRotatef(this->gThetaLeg, 0, 0, 1);

    glutSolidCube(this->trunkWidth / 3);
}

// 4/8 / 2
void Character::draw_right_leg()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b);

    // Draw leg animation according to the facing direction
    if (this->facingDirection == Direction::RIGHT)
    {
        glRotatef(-this->gThetaLeg, 0, 0, 1);
        glRotatef(-15, 0, 0, 1);
    }
    else
    {
        glRotatef(this->gThetaLeg, 0, 0, 1);
        glRotatef(30, 0, 0, 1);
    }

    glutSolidCube(this->trunkWidth / 3);
}

void Character::draw_arm()
{
    glColor3f(this->colors.lowerBody.r * 0.5, this->colors.lowerBody.g * 0.5, this->colors.lowerBody.b * 0.5);

    glTranslatef(this->center.x - (this->trunkWidth / 2 * 1.1)*sin(game->get_player()->get_theta_body()/180*M_PI), -this->center.y, -this->center.z + (this->trunkWidth / 2 * 1.5)*cos(game->get_player()->get_theta_body()/180*M_PI));

    // Rotate with gThetaArm
    glRotatef(this->gThetaArm, 0, 0, 1);
    // Flip with facingDirection according to the direction of the character
    glRotatef(-this->gThetaBody, 0, 1, 0);
    glRotatef(90, 0, 0, 1);

    glScalef(1, -this->height / 8 * 2.5, 1);
    glutSolidCube(this->trunkWidth / 3);

    // glBegin(GL_POLYGON);
    // // clang-format off
    //     glVertex2f(- this->trunkWidth / 8, 0);
    //     glVertex2f( this->trunkWidth / 8, 0);
    //     glVertex2f(this->trunkWidth / 8, -this->height / 8 * 2.5);
    //     glVertex2f(-this->trunkWidth / 8, -this->height / 8 * 2.5);
    // // clang-format on
    // glEnd();
}

// Draw a character
void Character::draw_character()
{
    glPushMatrix();

    // Move to the center of the character (remember that the coordinate starts from the top left corner)
    glTranslatef(this->center.x, -this->center.y, -this->center.z);
    glRotatef(-this->gThetaBody, 0, 1, 0);
    // Left leg
    glPushMatrix();
    glTranslatef(-this->trunkWidth / 2, -this->radius + this->height / 16, 0);
    this->draw_left_leg();
    glPopMatrix();

    // Right leg
    glPushMatrix();
    glTranslatef(this->trunkWidth / 3 / 2, -this->radius + this->height / 16, 0);
    this->draw_right_leg();
    glPopMatrix();

    // Left thigh
    glPushMatrix();
    glTranslatef(-this->trunkWidth / 2, -this->radius + this->height / 8 * 2, 0);
    this->draw_left_thigh();
    glPopMatrix();

    // Right thigh
    glPushMatrix();
    glTranslatef(this->trunkWidth / 3 / 2, -this->radius + this->height / 8 * 2, 0);
    this->draw_right_thigh();
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(0, -this->height / 8, 0);
    this->draw_body();
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(this->trunkWidth / 1.99, this->height / 3.5, 0);
    glRotatef(90, 0, 1, 0);
    this->draw_head();
    glPopMatrix();

    glPopMatrix();

    // Visual debug options
    if (game->get_debug_options().drawObjectCenter)
    {
        // Draw dot at the center of the Character
        glPushMatrix();
        glTranslatef(this->center.x, -this->center.y, -this->center.z);
        glPointSize(4);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glEnd();
        glPopMatrix();

        // Also draw dot at the height
        glPushMatrix();
        glTranslatef(this->center.x, -this->center.y - this->radius, -this->center.z);
        glTranslatef(0, this->height, 0);
        glPointSize(4);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glEnd();
        glPopMatrix();
    }

    // // Draw Character's borders/hitbox in 3D
    // if (game->get_debug_options().drawCharacterHitbox)
    // {
    //     glPushMatrix();
    //     glTranslatef(this->center.x, -this->center.y - this->radius, -this->center.z);
    //     glColor3f(1.0, 0.0, 0.0);
    //     glEnd();

    //     glPopMatrix();
    // }

    // Arm
    glPushMatrix();
    // glTranslatef(0, 0, this->trunkWidth / 2 * 1.1);
    this->draw_arm();
    glPopMatrix();
}

void Character::move_character(GLfloat dx, GLfloat dy, GLfloat frameTime)
{
    if (dx < 0)
    {
        this->facingDirection = Direction::LEFT;
    }
    else if (dx > 0)
    {
        this->facingDirection = Direction::RIGHT;
    }

    this->center.x += dx * frameTime * cos(this->gThetaBody / 180 * M_PI);
    this->center.y += dy * frameTime;
    this->center.z += dx * frameTime * -sin((this->gThetaBody / 180 * M_PI));

    // Only animate if the character is moving in the x direction and is not jumping
    if (!this->isJumping && dx != 0)
    {
        if (abs(gThetaLeg + abs(dx * frameTime * 3)) > this->gThetaLegLIMIT)
        {
            // If the leg rotation is at the limit, we need to flip the direction
            isWalkingObserve = !isWalkingObserve;
        }
        if (isWalkingObserve)
        {
            // Increase in observe
            gThetaLeg += abs(dx * frameTime * 3);
        }
        else
        {
            // Increase in reverse
            gThetaLeg -= abs(dx * frameTime * 3);
        }
    }
}

bool Character::is_inside_terrain(Terrain *terrain)
{
    Point terrainPos = terrain->get_center();

    if (this->center.y + this->radius >= terrainPos.y &&
        this->center.y - this->radius <= terrainPos.y + terrain->get_height())
    {
        if (this->center.x + this->trunkWidth / 2 >= terrainPos.x && this->center.x - this->trunkWidth / 2 <= terrainPos.x + terrain->get_width())
        {
            // Collided with black Terrain (not arena Terrain) from above (make Character able to jump)
            if (terrain->get_color().b != 1.0 && this->center.y <= terrainPos.y)
            {
                this->isFalling = false;
                this->canJump = true;

                this->terrainBelow = terrain;
            }

            // Collided with Terrain from below (stop jump)
            if (this->center.y >= terrainPos.y + terrain->get_height())
            {
                this->isFalling = true;
                this->isJumping = false;
                this->canJump = false;
            }

            return true;
        }
    }

    if (terrain->get_color().b == 1.0)
    {
        this->terrainBelow = NULL;
    }

    return false;
}

bool Character::is_inside_another_character(Character *character)
{
    // Check if characters are overlapping in the 3D space, considering a cilinder containing thei of their trunk widths.
    return (this->center.x + this->trunkWidth / 2 >= character->center.x - character->trunkWidth / 2 &&
            this->center.x - this->trunkWidth / 2 <= character->center.x + character->trunkWidth / 2 &&
            this->center.y + this->radius >= character->center.y - character->radius &&
            this->center.y - this->radius <= character->center.y + character->radius &&
            this->center.z + this->trunkWidth / 2 >= character->center.z - character->trunkWidth / 2 &&
            this->center.z - this->trunkWidth / 2 <= character->center.z + character->trunkWidth / 2);
}

GLfloat Character::get_jump_speed()
{
    return this->jumpSpeed;
}

GLfloat Character::get_jump_initial_y()
{
    return this->jumpInitialY;
}

void Character::set_jump_initial_y(GLfloat y)
{
    this->jumpInitialY = y;
}

void Character::set_is_falling(bool isFalling)
{
    this->isFalling = isFalling;
}
bool Character::get_is_falling()
{
    return this->isFalling;
}

void Character::set_is_jumping(bool isJumping)
{
    this->isJumping = isJumping;
}
bool Character::get_is_jumping()
{
    return this->isJumping;
}

void Character::set_can_jump(bool canJump)
{
    this->canJump = canJump;
}
bool Character::get_can_jump()
{
    return this->canJump;
}

void Character::set_jump_time(GLfloat jumpTime)
{
    this->jumpTime = jumpTime;
}
GLfloat Character::get_jump_time()
{
    return this->jumpTime;
}

void Character::set_facing_direction(GLint facingDirection)
{
    this->facingDirection = facingDirection;
}

GLint Character::get_facing_direction()
{
    return this->facingDirection;
}

void Character::set_terrain_below(Terrain *terrain)
{
    this->terrainBelow = terrain;
}

void Character::set_speed(GLdouble speed)
{
    this->speed = speed;
}
GLdouble Character::get_speed()
{
    return this->speed;
}

void Character::set_center(Point p)
{
    this->center = p;
}

void Character::set_theta_arm(GLfloat theta)
{
    this->gThetaArm = theta;
}

GLfloat Character::get_theta_arm()
{
    return this->gThetaArm;
}

void Character::change_theta_body(GLfloat dTheta, GLfloat frameTime)
{
    this->gThetaBody = (this->gThetaBody + dTheta * frameTime);
    if (this->gThetaBody > 360)
        this->gThetaBody -= 360;
    if (this->gThetaBody < 0)
        this->gThetaBody += 360;
}

GLfloat Character::get_theta_body()
{
    return this->gThetaBody;
}

void Character::set_radius(GLdouble r)
{
    this->radius = r;
}

void Character::set_height(GLdouble h)
{
    this->height = h;
}

void Character::set_id(GLint id)
{
    this->id = id;
}

GLint Character::get_id()
{
    return this->id;
}

Point Character::get_center()
{
    return this->center;
}

void Character::set_visor_color(Color visorColor)
{
    this->visorColor = visorColor;
}

Color Character::get_visor_color()
{
    return this->visorColor;
}

void Character::set_crewmate_colors(CrewmateColors c)
{
    this->colors = c;
}

CrewmateColors Character::get_crewmate_colors()
{
    return this->colors;
}

GLdouble Character::get_radius()
{
    return this->radius;
}

GLdouble Character::get_height()
{
    return this->height;
}

void Character::set_trunk_width(GLdouble t)
{
    this->trunkWidth = t;
}

GLdouble Character::get_trunk_width()
{
    return this->trunkWidth;
}

Terrain *Character::get_terrain_below()
{
    return this->terrainBelow;
}
