#include "../include/game.hpp"
#include "../include/svg_reader.hpp"

using namespace std;

GLdouble Game::get_random_z_inside_arena_given_radius(GLfloat radius)
{
    GLfloat arenaLength = this->arena->get_length();
    Point arenaPos = this->arena->get_center();

    GLdouble initialZ = arenaPos.z + radius;
    GLdouble finalZ = arenaPos.z + arenaLength - radius;

    // Generate a random z position between the initial and final z position
    GLdouble randomZ = initialZ + (finalZ - initialZ) * (rand() / (RAND_MAX + 1.0));

    return randomZ;
}

void Game::make_a_character_shoot(Character *character)
{
    // Check if Character can shoot (based on their reload time and the time since the last shot)
    if (glutGet(GLUT_ELAPSED_TIME) - character->get_last_time_fired() >= character->get_reload_time())
    {
        Gunshot *newGunshot = new Gunshot(character->get_id(), character->get_center().x, character->get_center().y, character->get_center().z - character->get_trunk_width() / 2 * 1.1, character->get_speed(), character->get_radius(), character->get_theta_arm() + (90 * character->get_facing_direction()), character->get_theta_body(), character->get_facing_direction(), character->get_crewmate_colors().upperBody);

        this->charactersGunshots.push_back(newGunshot);

        // Update the last time the Character fired a Gunshot
        character->set_last_time_fired(glutGet(GLUT_ELAPSED_TIME));
    }
}

void Game::make_a_character_jump(Character *character, GLfloat frameTime)
{
    // cout << "is_jumping: " << character->get_is_jumping() << endl;
    // cout << "initial y: " << character->get_jump_initial_y() - character->get_height() * 3 << endl;
    // cout << "y: " << character->get_center().y << endl;

    // Player can't jump if they're already jumping (AKA double-jumping, etc)
    character->set_can_jump(false);

    // If the player is jumping, move them up, but only if they're not at the top of the jump (3x their height)
    if (character->get_is_jumping() && (character->get_jump_initial_y() - character->get_height() * MAX_JUMP_HEIGHT) < character->get_center().y)
    {
        character->set_is_jumping(true);
        character->set_is_falling(false);
        character->set_terrain_below(NULL);

        // cout << -character->get_jump_speed() << endl;
        // cout << frameTime << endl;
        this->move_a_character(character, 0, -character->get_jump_speed(), frameTime);
    }
    else
    {
        character->set_can_jump(false);
        character->set_is_jumping(false);
        character->set_is_falling(true);
    }
}

bool Game::has_player_reached_arena_end()
{
    return this->player->get_center().x + (this->player->get_trunk_width() * 1.2) / 2 >= this->arena->get_center().x + this->arena->get_width();
}

bool Game::has_player_won()
{
    // Player has won if they have reached the end of the arena
    if (this->has_game_reached_end_state())
    {
        if (!this->player->is_alive())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    return false;
}

bool Game::has_game_reached_end_state()
{
    // End state is defined as:
    // The player being alive at the end of the arena or
    if (this->player->is_alive() && this->has_player_reached_arena_end())
    {
        return true;
    }
    // the player being dead at any point.
    else if (!this->player->is_alive())
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<Gunshot *> Game::get_characters_gunshots()
{
    return this->charactersGunshots;
}

void Game::move_gunshots(GLfloat frameTime)
{
    for (auto &gunshot : this->charactersGunshots)
    {
        this->move_a_gunshot(gunshot, frameTime);
    }
}

void Game::move_a_gunshot(Gunshot *gunshot, GLfloat frameTime)
{
    if (gunshot != NULL)
    {
        gunshot->move_gunshot(frameTime);
        this->handle_collision_gunshot(gunshot);
    }
}

void Game::remove_character(Character *character)
{
    if (character == this->player)
    {
        this->player = nullptr;
    }
    else
    {
        // If it's an Enemy, remove it from the enemies vector
        for (size_t i = 0; i < this->enemies.size(); i++)
        {
            if (this->enemies[i] == character)
            {
                this->enemies.erase(this->enemies.begin() + i);
                break;
            }
        }
    }
}

void Game::handle_collision_gunshot(Gunshot *gunshot)
{
    if (this->check_collision_gunshot_non_character(gunshot))
    {
        this->remove_gunshot(gunshot);
    }
    else
    {
        Character *hitCharacter = this->check_collision_gunshot_any_character(gunshot);
        if (hitCharacter != NULL && hitCharacter->get_id() != gunshot->get_shooter_id())
        {
            // Gunshot collided with a character and should be removed
            this->remove_gunshot(gunshot);
            cout << "Hit character " << hitCharacter->get_id() << endl;

            // Set character as dead and remove from game
            hitCharacter->set_alive(false);
            if (hitCharacter == this->player)
            {
                cout << "Player has been hit by a gunshot" << endl;
                return;
            }

            // Only remove the character here if it is not the player
            remove_character(hitCharacter);
        }
    }
}

Character *Game::check_collision_gunshot_any_character(Gunshot *gunshot)
{
    if (gunshot->is_inside_character(this->player))
    {
        return this->player;
    }
    else
    {
        for (Enemy *enemy : this->enemies)
        {
            if (gunshot->is_inside_character(enemy))
            {
                return enemy;
            }
        }
    }

    return NULL;
}

bool Game::check_collision_gunshot_non_character(Gunshot *gunshot)
{
    if (this->is_gunshot_outside_arena(gunshot) || this->is_gunshot_inside_any_terrain(gunshot))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Game::is_gunshot_outside_arena(Gunshot *gunshot)
{
    Terrain *arenaTerrain = this->arena;
    Point arenaPos = this->arena->get_center();

    if (gunshot->get_center().y - gunshot->get_radius() < arenaPos.y ||
        gunshot->get_center().y + gunshot->get_radius() > arenaPos.y + arenaTerrain->get_height())
    {
        return true;
    }

    if (gunshot->get_center().x - gunshot->get_radius() / 2 < arenaPos.x || gunshot->get_center().x + gunshot->get_radius() / 2 > arenaPos.x + arenaTerrain->get_width())
    {
        return true;
    }

    if (gunshot->get_center().z - gunshot->get_radius() / 2 < arenaPos.z || gunshot->get_center().z + gunshot->get_radius() / 2 > arenaPos.z + arenaTerrain->get_length())
    {
        return true;
    }

    return false;
}

bool Game::is_gunshot_inside_any_terrain(Gunshot *gunshot)
{
    for (Terrain *terrain : this->terrains)
    {
        if (gunshot->is_inside_terrain(terrain))
        {
            return true;
        }
    }

    return false;
}

void Game::remove_gunshot(Gunshot *gunshot)
{
    for (size_t i = 0; i < this->charactersGunshots.size(); i++)
    {
        if (this->charactersGunshots[i] == gunshot)
        {
            this->charactersGunshots.erase(this->charactersGunshots.begin() + i);
            break;
        }
    }
}

void Game::move_a_character(Character *character, GLdouble dx, GLdouble dy, GLfloat frameTime)
{
    character->move_character(dx, dy, frameTime);
    this->handle_collision(character, dx, dy, frameTime);
}

bool Game::check_collision(Character *character)
{
    if (this->is_character_outside_arena(character) || this->is_character_inside_any_terrain(character))
    {
        return true;
    }
    else
    {
        return is_character_inside_any_other_character(character);
    }
}

void Game::handle_collision(Character *character, GLdouble dx, GLdouble dy, GLfloat frameTime)
{
    if (this->check_collision(character))
    {
        character->move_character(-dx, -dy, frameTime);
    }
}

void Game::apply_gravity(GLfloat frameTime)
{
    GLdouble gravityVelocity = this->player->get_radius() * 0.33 * this->player->get_speed();

    // Apply gravity to player
    this->move_a_character(this->player, 0, gravityVelocity, frameTime);

    // Apply gravity to enemies
    Enemy *currentEnemy = NULL;
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        currentEnemy = this->enemies[i];
        this->move_a_character(currentEnemy, 0, gravityVelocity, frameTime);
    }
}

bool Game::will_enemy_fall(Enemy *enemy, GLdouble dx, GLfloat frameTime)
{
    Terrain *terrainBelowEnemy = enemy->get_terrain_below();

    // If enemy has no terrain below, it can't fall
    if (terrainBelowEnemy == NULL)
    {
        return false;
    }
    else
    {
        // Check if Enemy will be outside Terrain's x coordinates (i.e. will fall)
        GLfloat newX = enemy->get_center().x + (dx * frameTime);
        if ((newX + enemy->get_trunk_width() / 4) <= terrainBelowEnemy->get_center().x ||
            (newX - enemy->get_trunk_width() / 4) >= terrainBelowEnemy->get_center().x + terrainBelowEnemy->get_width())
        {
            return true;
        }
    }

    return false;
}

void Game::move_enemy_randomly(Enemy *enemy, GLfloat frameTime)
{
    int integerFrameTime = (int)frameTime;

    int randomNumber = rand() % integerFrameTime;

    switch (randomNumber)
    {
    case 1:
        if (!will_enemy_fall(enemy, -enemy->get_speed(), frameTime))
        {
            move_a_character(enemy, -enemy->get_speed(), 0, frameTime);
        }
        // else
        // {
        // cout << enemy->get_id() << ": "
        //  << "would fall" << endl;
        // }
        break;
    case 2:
        if (!will_enemy_fall(enemy, enemy->get_speed(), frameTime))
        {
            move_a_character(enemy, enemy->get_speed(), 0, frameTime);
        }
        // else
        // {
        // cout << enemy->get_id() << ": "
        //  << "would fall" << endl;
        // }
        break;
    default:
        break;
    }
}

void Game::enemy_shoot_at_player(Enemy *enemy, GLfloat frameTime)
{
    GLdouble enemyXViewDistance = this->get_arena()->get_height() * 0.4;
    GLdouble enemyYViewDistance = enemy->get_height() * 3;

    if (enemy->get_center().x - enemyXViewDistance < this->player->get_center().x &&
        enemy->get_center().x + enemyXViewDistance > this->player->get_center().x)
    {
        // cout << "Player is in view of enemy ID " << enemy->get_id() << endl;

        // Set enemy facing direction to player direction
        if (enemy->get_center().x < this->player->get_center().x)
        {
            enemy->set_facing_direction(Direction::RIGHT);
        }
        else
        {
            enemy->set_facing_direction(Direction::LEFT);
        }

        // cout << "Player y: " << this->player->get_center().y << "enemyYViewDistance: " << enemyYViewDistance << endl;
        // cout << "Enemy y: " << enemy->get_center().y << endl;

        if (this->player->get_center().y + enemyYViewDistance >= enemy->get_center().y && this->player->get_center().y - enemyYViewDistance <= enemy->get_center().y)
        {
            // cout << "Player is close to enemy ID " << enemy->get_id() << endl;
            enemy->set_visor_color(get_player_colors().upperBody);

            // Shoot at player at random intervals
            GLfloat randomNumber = rand() % (int)frameTime;
            if (randomNumber < frameTime * 0.005)
            {
                cout << "Enemy " << enemy->get_id() << " is shooting at player" << endl;
                this->make_a_character_shoot(enemy);
            }
        }
        else
        {
            enemy->set_visor_color(DEFAULT_VISOR_COLOR);
        }
    }
    else
    {
        enemy->set_visor_color(DEFAULT_VISOR_COLOR);
    }
}

void Game::enemies_shoot_at_player(GLfloat frameTime)
{
    if (!this->debugOptions.pacificEnemies)
    {
        for (size_t i = 0; i < this->enemies.size(); i++)
        {
            this->enemy_shoot_at_player(this->enemies[i], frameTime);
        }
    }
}

void Game::move_enemies_randomly(GLfloat frameTime)
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        this->move_enemy_randomly(this->enemies[i], frameTime);
    }
}

void Game::free_terrains()
{
    for (auto &terrain : this->terrains)
    {
        delete terrain;
    }
}

void Game::free_enemies()
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        if (this->enemies[i] != NULL)
        {
            delete this->enemies[i];
        }
    }
}

// WIP
void Game::free()
{
    delete this->player;

    this->charactersGunshots.clear();
    this->enemies.clear();
    this->terrains.clear();

    delete this->arena;
}

void Game::reset_game()
{
    this->free();

    parse_svg_file(this->arenaSVGFilename, this);
}

bool Game::is_character_outside_arena(Character *character)
{
    Terrain *arenaTerrain = this->arena;
    Point arenaPos = this->arena->get_center();

    // Check if player is outside the arena vertically
    if (character->get_center().y - character->get_radius() < arenaPos.y ||
        character->get_center().y + character->get_radius() * 0.98 > arenaPos.y + arenaTerrain->get_height())
    {
        if (character->get_center().y >= arenaPos.y)
        {
            // Player collided with bottom of the arena and should be able to jump again
            character->set_is_falling(false);
            character->set_is_jumping(false);
            character->set_can_jump(true);
        }

        if (character->get_center().y - character->get_height() <= arenaPos.y)
        {
            // Player collided with the top of the arena and should stop jumping
            character->set_is_falling(true);
            character->set_is_jumping(false);
            character->set_can_jump(false);
        }
        return true;
    }

    // Player collided with bottom of the arena and should mark it as the terrain 'below'
    if (character->get_center().y + character->get_radius() > arenaPos.y + arenaTerrain->get_height())
    {
        character->set_terrain_below(this->get_arena());
    }

    // Check if player is outside the arena horizontally
    if (character->get_center().x - character->get_trunk_width() / 2 < arenaPos.x || character->get_center().x + character->get_trunk_width() / 2 > arenaPos.x + arenaTerrain->get_width())
    {
        return true;
    }

    if (character->get_center().z - character->get_trunk_width() / 2 < arenaPos.z || character->get_center().z + character->get_trunk_width() / 2 > arenaPos.z + arenaTerrain->get_length())
    {
        return true;
    }

    return false;
}

bool Game::is_camera_outside_arena(GLdouble x, GLdouble y, GLdouble z)
{
    Terrain *arenaTerrain = this->arena;
    Point arenaPos = this->arena->get_center();

    // Check if camera is outside the arena vertically
    if (-y < arenaPos.y || -y > arenaPos.y + arenaTerrain->get_height())
    {
        return true;
    }

    // Check if camera is outside the arena horizontally
    if (x < arenaPos.x || x > arenaPos.x + arenaTerrain->get_width())
    {
        return true;
    }

    if (-z < arenaPos.z || -z > arenaPos.z + arenaTerrain->get_length())
    {
        return true;
    }

    return false;
}

bool Game::is_character_inside_any_other_character(Character *character)
{
    GLint charID = character->get_id();

    // Check collision for player
    if (charID != this->player->get_id() && character->is_inside_another_character(this->player))
    {
        return true;
    }

    // Check collision for enemies
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        if (charID != this->enemies[i]->get_id() && character->is_inside_another_character(this->enemies[i]))
        {
            return true;
        }
    }

    return false;
}

bool Game::is_character_inside_any_terrain(Character *character)
{
    for (size_t i = 0; i < this->terrains.size(); i++)
    {
        Terrain *terrain = this->terrains[i];
        if (character->is_inside_terrain(terrain))
        {
            // If this debug option is enabled, highlight the terrain that the character collided with
            if (this->debugOptions.highlightTerrain)
            {
                terrain->set_color(character->get_crewmate_colors().upperBody);
            }

            return true;
        }
    }

    return false;
}

// Enemy interface
void Game::add_enemy(Enemy *enemy)
{
    this->enemies.push_back(enemy);
    this->nCharacters++;
}

vector<Enemy *> Game::get_enemies()
{
    return this->enemies;
}

void Game::draw_enemies()
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        (this->enemies[i])->draw_character();
    }
}

// Terrain interface
void Game::add_terrain(Terrain *terrain)
{
    this->terrains.push_back(terrain);
}

vector<Terrain *> Game::get_terrains()
{
    return this->terrains;
}

void Game::draw_terrains()
{
    for (size_t i = 0; i < this->terrains.size(); i++)
    {
        (this->terrains[i])->draw_terrain();
    }
}

Player *Game::get_player()
{
    return this->player;
}

void Game::add_player(Player *player)
{
    this->player = player;
    this->nCharacters++;
}

void Game::draw_player()
{
    this->player->draw_character();
}

void Game::set_arena(Terrain *arena)
{
    this->arena = arena;
}

Terrain *Game::get_arena()
{
    return this->arena;
}

GLint Game::get_n_characters()
{
    return this->nCharacters;
}

void Game::set_arena_svg_filename(string arenaSVGFilename)
{
    this->arenaSVGFilename = arenaSVGFilename;
}

string Game::get_arena_svg_filename()
{
    return this->arenaSVGFilename;
}

void Game::set_arena_dimensions(Dimensions arenaDimensions)
{
    this->arenaDimensions = arenaDimensions;
}

Dimensions Game::get_arena_dimensions()
{
    return this->arenaDimensions;
}

bool Game::get_debug_mode()
{
    return this->debugMode;
}

void Game::set_debug_mode(bool debugMode)
{
    this->debugMode = debugMode;
    set_debug_options(debugMode);
}

void Game::set_debug_options(bool debug)
{
    if (this->debugMode)
    {
        this->debugOptions.highlightTerrain = debug;
        this->debugOptions.pacificEnemies = debug;
        this->debugOptions.drawObjectCenter = debug;
        this->debugOptions.drawCharacterHitbox = debug;
        this->debugOptions.globalCamera = debug;
    }
}

Debug Game::get_debug_options()
{
    return this->debugOptions;
}

void Game::set_global_camera(bool globalCamera)
{
    if (this->debugMode)
    {
        this->debugOptions.globalCamera = globalCamera;
    }
}
