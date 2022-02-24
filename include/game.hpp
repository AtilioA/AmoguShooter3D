#ifndef GAME_H_
#define GAME_H_

#include <bits/stdc++.h>
#include "gunshot.hpp"
#include "utils.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "terrain.hpp"

using namespace std;

// Used to tweak mouse sensitivity on move_arm_mouse_helper()
#define MOUSE_SENSITIVITY 1 / 3

typedef struct tDebug
{
    bool highlightTerrain;
    bool pacificEnemies;
    bool drawObjectCenter;
    bool drawCharacterHitbox;
    bool globalCamera;
} Debug;

class Game
{
private:
    Player *player;
    vector<Enemy *> enemies;
    vector<Gunshot *> charactersGunshots;
    vector<Terrain *> terrains;
    Terrain *arena;
    GLint nCharacters;
    string arenaSVGFilename;
    Dimensions arenaDimensions;
    bool debugMode;
    Debug debugOptions;

public:
    Game()
    {
        this->player = NULL;
        this->enemies = vector<Enemy *>();
        this->terrains = vector<Terrain *>();
        this->arena = NULL;
        this->nCharacters = 0;
        this->arenaSVGFilename = "";
        this->arenaDimensions = {0, 0};
        this->debugMode = false;
        this->debugOptions = {false, false, false, false, false};
    };

    /* Game status interface */
    bool has_game_reached_end_state();
    bool has_player_reached_arena_end();
    bool has_player_won();
    void reset_game();

    /* Character interface */
    void make_a_character_shoot(Character *character);
    void make_a_character_jump(Character *character, GLfloat frameTime);
    void move_a_character(Character *character, GLdouble dx, GLdouble dy, GLfloat frameTime);
    void remove_character(Character *character);

    /* Gunshot interface */
    vector<Gunshot *> get_characters_gunshots();
    void move_gunshots(GLfloat frameTime);
    void move_a_gunshot(Gunshot *gunshot, GLfloat frameTime);
    void remove_gunshot(Gunshot *gunshot);

    /* Player interface */
    void add_player(Player *player);
    Player *get_player();
    void draw_player();
    GLint get_n_characters();

    /* Enemy interface */
    void add_enemy(Enemy *enemy);
    std::vector<Enemy *> get_enemies();
    void draw_enemies();

    /* Character collision interface */
    void handle_collision(Character *character, GLdouble dx, GLdouble dy, GLfloat frameTime);
    bool check_collision(Character *character);
    void apply_gravity(GLfloat frameTime);
    bool is_character_inside_any_other_character(Character *character);
    bool is_character_outside_arena(Character *character);
    bool is_character_inside_any_terrain(Character *character);
    bool will_enemy_fall(Enemy *enemy, GLdouble dx, GLfloat frameTime);
    GLdouble get_random_z_inside_arena_given_radius(GLfloat radius);
    /* Gunshot collision interface */
    void handle_collision_gunshot(Gunshot *gunshot);
    bool check_collision_gunshot_non_character(Gunshot *gunshot);
    bool is_gunshot_outside_arena(Gunshot *gunshot);
    bool is_gunshot_inside_any_terrain(Gunshot *gunshot);
    Character *check_collision_gunshot_any_character(Gunshot *gunshot);

    /* Random enemy behavior interface */
    // Make enemy shoot at player if player is in range
    void enemy_shoot_at_player(Enemy *enemy, GLfloat frameTime);
    void enemies_shoot_at_player(GLfloat frameTime);
    // Move enemy to the left or right randomly
    void move_enemy_randomly(Enemy *enemy, GLfloat frameTime);
    void move_enemies_randomly(GLfloat frameTime);

    /* Terrain interface */
    void add_terrain(Terrain *terrain);
    std::vector<Terrain *> get_terrains();
    void draw_terrains();

    /* Arena interface */
    void set_arena(Terrain *arena);
    Terrain *get_arena();
    void set_arena_svg_filename(string arenaSVGFilename);
    string get_arena_svg_filename();
    void set_arena_dimensions(Dimensions arenaDimensions);
    Dimensions get_arena_dimensions();

    /* Memory management interface */
    void free();
    void free_terrains();
    void free_enemies();

    /* Debug interface */
    bool get_debug_mode();
    void set_debug_mode(bool debugMode);
    void set_debug_options(bool debug);
    Debug get_debug_options();
    void set_global_camera(bool globalCamera);
};

#endif /* GAME_H_ */
