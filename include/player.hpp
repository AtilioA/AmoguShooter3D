// Library for representing the player

#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "character.hpp"

// Represents the player. It is merely a Character object with another name.
class Player : public Character
{

public:
    using Character::Character;
};

#endif /* PLAYER_H */
