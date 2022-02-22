// Library for representing enemies

#ifndef ENEMY_H
#define ENEMY_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "character.hpp"

// Represents an enemy in the game. It is merely a Character object with another name.
class Enemy : public Character
{

public:
    using Character::Character;
};

#endif /* ENEMY_H */
