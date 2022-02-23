#include "../include/tinyxml2.hpp"
#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/enemy.hpp"
#include "../include/terrain.hpp"
#include "../include/utils.hpp"

using namespace tinyxml2;
using namespace std;

void parseCircle(XMLElement *circ, Game *game)
{
    GLfloat cx, cy, r;
    CrewmateColors colors;

    // Get all tag attributes for the circle
    circ->QueryFloatAttribute("cx", &cx);
    circ->QueryFloatAttribute("cy", &cy);
    circ->QueryFloatAttribute("r", &r);
    string circFill = circ->Attribute("fill");

    GLdouble cz = game->get_random_z_inside_arena_given_radius(r);

    Point center = {cx, cy, cz};

    cout << "cx: " << cx << " cy: " << cy << " random z: " << cz << " r: " << r << " circFill: " << circFill << endl;

    // Enemy circle
    if (circFill == "red")
    {
        cout << "-- ENEMY --" << endl;
        colors = get_random_enemy_colors();
        Enemy *enemy = new Enemy(center, r, colors, game->get_n_characters());
        game->add_enemy(enemy);
    }
    // Player circle
    else if (circFill == "green")
    {
        cout << "-- PLAYER --" << endl;
        colors = get_player_colors();
        Player *player = new Player(center, r, colors, game->get_n_characters());
        game->add_player(player);
    }
}

void parseRect(XMLElement *rect, Game *game)
{
    GLfloat x, y, width, height;
    Color color;

    // Get all tag attributes for the rectangle
    rect->QueryFloatAttribute("x", &x);
    rect->QueryFloatAttribute("y", &y);
    rect->QueryFloatAttribute("width", &width);
    rect->QueryFloatAttribute("height", &height);
    string rectFill = rect->Attribute("fill");

    Point center = {x, y};

    cout << "x: " << x << " y: " << y << " width: " << width << " height: " << height << " rectFill: " << rectFill << endl;

    // STUB: this hack fixes the case when the height isn't defined yet or is 0
    GLfloat length = game->get_arena_dimensions().height / 2;
    if (length == 0)
    {
        // We might be able to assume that the blue rectangle is always the first rectangle
        length = height / 2;
    }

    // Terrain rectangle
    if (rectFill == "black")
    {
        cout << "-- TERRAIN --" << endl;
        color = {0.0, 0.0, 0.0};
        Terrain *terrain = new Terrain(center, width, height, length, color);
        terrain->draw_terrain();
        game->add_terrain(terrain);
    }
    // Background rectangle
    else if (rectFill == "blue")
    {
        cout << "-- BACKGROUND --" << endl;
        color = {0.0, 0.0, 0.75};

        Terrain *background = new Terrain(center, width, height, length, color);
        Dimensions dimensions = {width, height};
        // Disclaimer: arena_background and arena_dimensions are a bit redundant
        game->set_arena_background(background);
        game->set_arena_dimensions(dimensions);
    }

    // cout << "length: " << length << endl;
}

void parseSVGFile(string filepath, Game *game)
{
    XMLDocument *gameSVGfile = new XMLDocument();

    game->set_arena_svg_filename(filepath);

    cout << "Parsing '" << game->get_arena_svg_filename() << "'." << endl;

    gameSVGfile->LoadFile(filepath.c_str());

    // If the file cannot be opened, exit the program with failure status
    if (gameSVGfile->ErrorID() != 0)
    {
        cout << "Couldn't open file '" << filepath << "'." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parse svg header
        XMLElement *svgHeader = gameSVGfile->FirstChildElement("svg");
        // Parse svg body (contains all the circles and rectangles, i.e. the game elements)
        XMLElement *svgBody = svgHeader->FirstChildElement();

        // While there are more elements to parse
        while (svgBody != NULL)
        {
            // Get type of tag
            string tagType = svgBody->Value();

            // Parse elements according to their type
            if (tagType == "rect")
            {
                parseRect(svgBody, game);
            }
            else
            {
                parseCircle(svgBody, game);
            }

            // Get next element to parse in the svg body
            svgBody = svgBody->NextSiblingElement();
        }
    }
}
