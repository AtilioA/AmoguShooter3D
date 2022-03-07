#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

#include "include/game.hpp"
#include "include/svg_reader.hpp"
#include "include/utils.hpp"

using namespace std;

// Key status
int keyStatus[256];

// Char array for endgame messages
static char str[999];

// Identificadores de textura
GLuint textureEarth;
GLuint textureSun;
GLuint texturePlane;

// Cotroles de giro
double angleDay = 0;
double angleYear = 0;

// Camera controls
double camDist = 50;
double camXYAngle = 0;
double camXZAngle = 0;
int toggleCam = 0;
int camAngle = 60;
int lastX = 0;
int lastY = 0;
int buttonDown = 0;

/* Window dimensions */
// "será exibida em uma janela de 500x500 pixel do sistema operacional"
const GLint Width = 500;
const GLint Height = 500;
// Default viewing dimensions (glOrtho/"Camera")
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

// Whether to use frametime normalization or not
static bool shouldPreserveFramerateSpeed = true;

// Auxiliary variable to calculate mouse movement (and rotate player's arm)
GLfloat oldY = 0;

Game *game = new Game();

void RenderString(float x, float y)
{
    // Render the string in white color
    glColor3f(1.0f, 1.0f, 1.0f);

    // Handpicked font margin adjusted to the window size (for game over message)
    GLfloat stringMargin = game->get_player()->get_radius() * 6;

    // Change string according to game outcome
    if (game->has_player_won())
    {
        stringMargin = game->get_player()->get_radius() * 6.25;
        sprintf(str, "  VITORIA! Aperte R para reiniciar");
        cout << "VITÓRIA" << endl;
    }
    else
    {
        sprintf(str, "GAME OVER! Aperte R para reiniciar");
        cout << "GAME OVER" << endl;
    }

    // Raster position for the text, determined by the player's position
    glRasterPos2f(game->get_player()->get_center().x - stringMargin, -game->get_arena()->get_center().y - game->get_arena()->get_height() / 2);

    // Navigate through the string and display each character
    char *text;
    text = str;
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *text);
        text++;
    }
}

void change_camera(int angle, int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(angle,
                   (GLfloat)w / (GLfloat)h, 1, 150.0);

    glMatrixMode(GL_MODELVIEW);
}

void render_scene()
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // gluLookAt(0, 2, 5, 0, 0, 0, 0, 1, 0);

    GLfloat lightParams[] = {0.0, 3.0, 10.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightParams);

    // Only draw the game components if the game is not over
    if (game->has_game_reached_end_state())
    {
        cout << "Game has reached end state!" << endl;
        RenderString(0, 0);
    }
    else
    {
        // cout << "\nDrawing game elements:" << endl;
        // cout << "Drawing arena... ";
        game->get_arena()->draw_terrain();
        // cout << "Drawing terrains... ";
        game->draw_terrains();
        // cout << "Drawing player... ";
        game->draw_player();
        // cout << "Drawing enemies..." << endl;
        game->draw_enemies();
        // cout << "Drawing gunshots..." << endl;
        for (auto &gunshot : game->get_characters_gunshots())
        {
            gunshot->draw_gunshot();
        }
        // cout << "Finished drawing game elements." << endl;
    }

    // Flush OpenGL buffers so that the rendered image is visible.
    glutSwapBuffers();
    // Mark the current window as needing to be redisplayed.
    glutPostRedisplay();
}

// Function called whenever a key is pressed; all shortcuts are handled by the switch statement
void key_press(unsigned char key, int x, int y)
{
    static bool textureEnabled = true;
    static bool lightingEnabled = true;
    static bool smoothEnabled = true;

    switch (key)
    {
    // Enable 'global camera' (buggy but only exists for debugging purposes)
    case '1':
        if (game->get_debug_mode())
        {
            game->set_global_camera(!game->get_debug_options().globalCamera);
        }
        break;
    // Walk left
    case 'a':
    case 'A':
        keyStatus[(int)('a')] = 1; // Using keyStatus trick
        break;
    // Walk right
    case 'd':
    case 'D':
        keyStatus[(int)('d')] = 1; // Using keyStatus trick
        break;
    // Reset game (only works if the game is over or if the debug mode is enabled)
    case 'r':
    case 'R':
        keyStatus[(int)('r')] = 1; // Using keyStatus trick
        if (game->get_debug_mode())
        {
            cout << "Resetting game (debug mode)..." << endl;
            game->reset_game();
        }
        break;
    // Toggle debug mode
    case '2':
        if (game->get_debug_mode())
        {
            game->get_debug_options().drawCharacterHitbox ? game->set_debug_options(false) : game->set_debug_options(true);
        }
        break;
    case '3':
        toggleCam = 0;
        break;
    case '4':
        toggleCam = 1;
        break;
    case 't':
        if (textureEnabled)
        {
            glDisable(GL_TEXTURE_2D);
        }
        else
        {
            glEnable(GL_TEXTURE_2D);
        }
        textureEnabled = !textureEnabled;
        break;
    case 'l':
        if (lightingEnabled)
        {
            glDisable(GL_LIGHTING);
        }
        else
        {
            glEnable(GL_LIGHTING);
        }
        lightingEnabled = !lightingEnabled;
        break;
    case 's':
        if (smoothEnabled)
        {
            glShadeModel(GL_FLAT);
        }
        else
        {
            glShadeModel(GL_SMOOTH);
        }
        smoothEnabled = !smoothEnabled;
        break;
    case '+':
    {
        int inc = camAngle >= 180 ? 0 : 1;
        camAngle += inc;
        change_camera(camAngle,
                      glutGet(GLUT_WINDOW_WIDTH),
                      glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
    case '-':
    {
        int inc = camAngle <= 5 ? 0 : 1;
        camAngle -= inc;
        change_camera(camAngle, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
    break;
    case ' ':
        keyStatus[(int)(' ')] = 1;
        break;

    // Quit game
    case 27: // Escape key
        exit(0);
    }

    // Redraw the scene (maybe unnecessary)
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    change_camera(camAngle, w, h);
}

// Handle key release
void key_up(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    // Redraw the scene (maybe unnecessary)
    glutPostRedisplay();
}

// Make all keys 'up'
void ResetKeyStatus()
{
    int i = 0;

    // Initialize keyStatus
    for (i = 0; i < 256; i++)
    {
        keyStatus[i] = 0;
    }
}

// Function used to handle mouse presses
void mouse_click(int button, int state, int mousex, int mousey)
{
    // Player shoot on left click
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        game->make_a_character_shoot(game->get_player());
    }

    // Redraw the scene (maybe unnecessary)
    glutPostRedisplay();
}

void init(Game *game)
{
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);

    // Initialize all keys to 'up'
    ResetKeyStatus();

    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark gray, no opacity(alpha).

    cout << "\nArena width: " << game->get_arena_dimensions().width << ", height: " << game->get_arena_dimensions().height << endl;
    GLfloat smallestArenaDimension = smallest_dimension(game->get_arena_dimensions());
    cout << "Smallest arena dimension: " << smallestArenaDimension << endl;

    // Use ViewingHeight and ViewingWidth to create the default camera
    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glLoadIdentity();
    // glOrtho(-(ViewingWidth / 2),  // X coordinate of left edge
    //         (ViewingWidth / 2),   // X coordinate of right edge
    //         -(ViewingHeight / 2), // Y coordinate of bottom edge
    //         (ViewingHeight / 2),  // Y coordinate of top edge
    //         -100,                 // Z coordinate of the “near” plane
    //         100);                 // Z coordinate of the “far” plane

    glMatrixMode(GL_MODELVIEW); // Select the projection matrix
    glLoadIdentity();
}

void idle(void)
{
    // Calculate frametime/'deltatime'
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, frameTime;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    frameTime = currentTime - previousTime;
    previousTime = currentTime;

    // If we don't have to normalize with frameTime use 1 as multiplier (won't change anything)
    if (!shouldPreserveFramerateSpeed)
    {
        frameTime = 1;
    }

    Player *player = game->get_player();

    // Use local camera (follows the player)
    // The camera shouldn't move in y direction, only in x
    if (!game->get_debug_options().globalCamera)
    {
        // glMatrixMode(GL_PROJECTION); // Select the projection matrix
        // glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 2, 5, player->get_center().x, player->get_center().y, player->get_center().z, 0, 1, 0);
        // glOrtho(-game->get_arena()->get_height() / 2 + player->get_center().x,          // X coordinate of left edge
        //         game->get_arena()->get_height() / 2 + player->get_center().x,           // X coordinate of right edge
        //         (-game->get_arena()->get_center().y - game->get_arena()->get_height()), // Y coordinate of bottom edge
        //         -game->get_arena()->get_center().y,                                     // Y coordinate of top edge
        //         -1,                                                                     // Z coordinate of the “near” plane
        //         1);                                                                     // Z coordinate of the “far” plane
        // glMatrixMode(GL_MODELVIEW); // Select the projection matrix
    }
    // else // if global camera is enabled
    // {
    //     glMatrixMode(GL_PROJECTION); // Select the projection matrix
    //     glLoadIdentity();
    //     glOrtho(-(ViewingWidth / 2),  // X coordinate of left edge
    //             (ViewingWidth / 2),   // X coordinate of right edge
    //             -(ViewingHeight / 2), // Y coordinate of bottom edge
    //             (ViewingHeight / 2),  // Y coordinate of top edge
    //             -100,                 // Z coordinate of the “near” plane
    //             100);                 // Z coordinate of the “far” plane

    //     glMatrixMode(GL_MODELVIEW); // Select the projection matrix
    //     glLoadIdentity();
    // }

    // If player has reached the end of the level or has died, stop the game
    if (game->has_game_reached_end_state())
    {
        cout << "Game ended!" << endl;

        if (!player->is_alive())
        {
            cout << "Player is dead!" << endl;
        }
        else
        {
            cout << "Player won!" << endl;
        }

        // Allow the player to restart the game
        if (keyStatus['r'] == 1 || keyStatus['R'] == 1)
        {
            game->reset_game();
        }
    }
    else
    {
        // Never use unitialized frametime
        if (frameTime > 0)
        {
            // Update enemies positions by moving them randomly
            game->move_enemies_randomly(frameTime);

            // Make enemies shoot at player if they are in range
            game->enemies_shoot_at_player(frameTime);
        }

        GLdouble inc = player->get_speed();
        GLdouble dx = 0, dy = 0;

        // cout << "Can jump: " << player->get_can_jump() << endl;
        // cout << "Is jumping: " << player->get_is_jumping() << endl;
        // cout << "Is falling: " << player->get_is_falling() << endl;

        /* Make Player jump */
        if (keyStatus[(int)(' ')] == 1)
        {
            // Jump initialization
            if (player->get_can_jump() && !player->get_is_jumping())
            {
                // cout << "Setting initial y:" << player->get_center().y << endl;
                player->set_jump_initial_y(player->get_center().y);

                player->set_is_jumping(true);
                player->set_can_jump(false);
            }

            // Player continue jumping when holding spacebar
            if (player->get_is_jumping() && !player->get_is_falling())
            {
                game->make_a_character_jump(player, frameTime);
            }
        }
        else // Not pressing spacebar
        {
            player->set_is_jumping(false);
            player->set_is_falling(true);
        }

        /* Make Player move */
        if (keyStatus['d'] == 1 || keyStatus['D'] == 1)
        {
            dx += inc;
            game->move_a_character(player, dx, dy, frameTime);
        }
        if (keyStatus['a'] == 1 || keyStatus['A'] == 1)
        {
            dx -= inc;
            game->move_a_character(player, dx, dy, frameTime);
        }

        // Apply gravity to all characters
        game->apply_gravity(frameTime);

        // Move all gunshots
        game->move_gunshots(frameTime);
    }

    // Redraw the scene (maybe unnecessary)
    glutPostRedisplay();
}

// This function is called whenever the mouse is moved within the window
void aim_with_mouse(int x, int y)
{
    // Rotate player's arm based on mouse movement
    game->get_player()->move_arm_mouse_helper(y, &oldY);
}

int main(int argc, char *argv[])
{
    // Program needs at least one argument (svg filepath) apart from the executable name
    if (argc < 2)
    {
        printf("Usage: %s <svg file>\n", argv[0]);
        exit(1);
    }
    string arena_filename = argv[1];

    // Check if third argv argument is -d (for debug), set debug flag
    bool debug = false;
    if (argc >= 3 && strcmp(argv[2], "-d") == 0)
    {
        debug = true;
    }
    game->set_debug_mode(debug);

    // Generate seed for random enemy activity
    srand(time(NULL));

    cout << "Parsing SVG file..." << endl;
    parseSVGFile(arena_filename, game);
    cout << "Finished parsing SVG file." << endl;

    // Initialize openGL with Double buffer and RGB color without transparency
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create the window
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(75, 75);
    glutCreateWindow("Trabalho 2D");

    /* Define callbacks */
    glutDisplayFunc(render_scene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key_press);
    glutKeyboardUpFunc(key_up);
    // Mouse events handlers
    glutMouseFunc(mouse_click);
    glutPassiveMotionFunc(aim_with_mouse);
    // Main rendering loop
    glutIdleFunc(idle);

    init(game);

    glutMainLoop();

    return 0;
}
