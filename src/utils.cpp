#include "../include/utils.hpp"

using namespace std;

// Available colors for Player objects
vector<string> PLAYER_COLORS = {"RED"};

// Available colors for Enemy objects
vector<string> ENEMY_COLORS = {
    "PURPLE",
    "GREEN",
    "YELLOW",
    "ORANGE",
    "BROWN",
    "LIME",
    "BLUE",
    "CYAN",
    "MAGENTA",
    "WHITE",
    "BLACK",
};

/*  CREWMATE COLORS:
    rgb(194,20,15)   rgb(120,10,57)
    rgb(81,238,59)   rgb(22,167,66)
    rgb(104,47,186)  rgb(63,70,78)
    rgb(238,82,186)  rgb(170,44,172)
    rgb(242,242,84)  rgb(197,136,37)
    rgb(240,125,16)  rgb(179,60,21)
    rgb(14,127,42)   rgb(12,75,44)
    rgb(112,72,31)   rgb(95,36,19)
    rgb(57,254,218)  rgb(35,169,190)
    rgb(18,46,208)   rgb(9,22,142)
    rgb(214,224,240) rgb(130,149,192)
    rgb(63,70,78)    rgb(31,31,38)
*/

// Maps strings to their respective RGB values within CrewmateColors struct, which stores instances of struct Color
map<string, CrewmateColors> colorMap = {
    {"RED", CrewmateColors({tColor({194.0 / 255.0, 20.0 / 255.0, 15.0 / 255.0}), tColor({120.0 / 255.0, 10.0 / 255.0, 57.0 / 255.0})})},
    {"GREEN", CrewmateColors({tColor({81.0 / 255.0, 238.0 / 255.0, 59.0 / 255.0}), tColor({22.0 / 255.0, 167.0 / 255.0, 66.0 / 255.0})})},
    {"PURPLE", CrewmateColors({tColor({104.0 / 255.0, 47.0 / 255.0, 186.0 / 255.0}), tColor({63.0 / 255.0, 70.0 / 255.0, 78.0 / 255.0})})},
    {"MAGENTA", CrewmateColors({tColor({238.0 / 255.0, 82.0 / 255.0, 186.0 / 255.0}), tColor({170.0 / 255.0, 44.0 / 255.0, 172.0 / 255.0})})},
    {"YELLOW", CrewmateColors({tColor({242.0 / 255.0, 242.0 / 255.0, 84.0 / 255.0}), tColor({197.0 / 255.0, 136.0 / 255.0, 37.0 / 255.0})})},
    {"ORANGE", CrewmateColors({tColor({240.0 / 255.0, 125.0 / 255.0, 16.0 / 255.0}), tColor({179.0 / 255.0, 60.0 / 255.0, 21.0 / 255.0})})},
    {"GREEN", CrewmateColors({tColor({14.0 / 255.0, 127.0 / 255.0, 42.0 / 255.0}), tColor({12.0 / 255.0, 75.0 / 255.0, 44.0 / 255.0})})},
    {"BROWN", CrewmateColors({tColor({112.0 / 255.0, 72.0 / 255.0, 31.0 / 255.0}), tColor({95.0 / 255.0, 36.0 / 255.0, 19.0 / 255.0})})},
    {"CYAN", CrewmateColors({tColor({57.0 / 255.0, 254.0 / 255.0, 218.0 / 255.0}), tColor({35.0 / 255.0, 169.0 / 255.0, 190.0 / 255.0})})},
    {"BLUE", CrewmateColors({tColor({18.0 / 255.0, 46.0 / 255.0, 208.0 / 255.0}), tColor({9.0 / 255.0, 22.0 / 255.0, 142.0 / 255.0})})},
    {"WHITE", CrewmateColors({tColor({214.0 / 255.0, 224.0 / 255.0, 240.0 / 255.0}), tColor({130.0 / 255.0, 149.0 / 255.0, 192.0 / 255.0})})},
    {"BLACK", CrewmateColors({tColor({63.0 / 255.0, 70.0 / 255.0, 78.0 / 255.0}), tColor({31.0 / 255, 31.0 / 255, 38.0 / 255})})}};

CrewmateColors get_random_enemy_colors()
{
    // Get random index from 0 to size of ENEMY_COLORS and use it to access the corresponding color
    int randomIndex = rand() % ENEMY_COLORS.size();
    string *randomColor = &ENEMY_COLORS[randomIndex];

    if (colorMap.find(*randomColor) != colorMap.end())
    {
        return colorMap[*randomColor];
    }
    else
    {
        return colorMap["BLACK"];
    }
}

CrewmateColors get_player_colors()
{
    // Hardcoded to return RED
    if (colorMap.find("RED") != colorMap.end())
    {
        return colorMap["RED"];
    }
    else
    {
        return get_random_enemy_colors();
    }
}

GLfloat smallest_dimension(Dimensions dimensions)
{
    if (dimensions.width < dimensions.height)
    {
        return dimensions.width;
    }
    else
    {
        return dimensions.height;
    }
}

GLfloat deg_to_radians(GLfloat deg)
{
    return deg * M_PI / 180.0;
}

GLfloat rad_to_degrees(GLfloat rad)
{
    return rad * 180.0 / M_PI;
}
