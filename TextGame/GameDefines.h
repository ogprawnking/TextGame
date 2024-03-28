#pragma once

// Room tile characters
const char* const INDENT = "\t";
const char* const EMPTY_TILE = "[ \xb0 ]";
const char* const ENEMY_TILE = "[ \x94 ]";
const char* const TREASURE_TILE = "[ $ ]";
const char* const FOOD_TILE = "[ \xcf ]";
const char* const ENTRANCE_TILE = "[ \x9d ]";
const char* const EXIT_TILE = "[ \xFE ]";
const char* const PLAYER_TILE = "[ \x81 ]";
// numbers for room recognition
const int EMPTY = 0;
const int ENTRANCE = 4;
const int EXIT = 5;
 //ENEMY to TREAUSRE_DEF shouldn't be needed
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int TREASURE_HP = 6;
const int TREASURE_ATT = 7;
const int TREASURE_DEF = 8;
 //numbers are prioritised by lowest number being priority etc.
 //player can be drawn no matter what in a room.
const int PRIORITY_PLAYER = 0;
const int PRIORITY_ENEMY = 1;
const int PRIORITY_POWERUP = 2;
const int PRIORITY_FOOD = 3;
const int PRIORITY_DEFAULT = 5;


const int MAX_RANDOM_TYPE = FOOD + 1;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;
// numbers for user input to move (instead of wasd)
const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;
const int LOOK = 9;
const int FIGHT = 10;
const int PICKUP = 11;
const int QUIT = 12;

static const char itemNames[15][30] = {
 "ouraknight,", "ligma,", "suffering,", "incontinence,",
 "katax,", "homunculus-loxodontus,", "indecision,", "ugly,", "independence,",
 "incurability,", "coeliac,", "severe-anxiety,", "determination,", "swiftness,",
 "type1diabetes,"
};