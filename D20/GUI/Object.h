#pragma once
enum class ObjectType {
    None,
    Wall,
    Chest,
    Door,
    Character,
    Aggressor
};

struct Object {
    int x, y;
    ObjectType type;
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
//const int GRID_WIDTH = 10;
//const int GRID_HEIGHT = 10;
const int CELL_SIZE = 40; // Adjust cell size as desired
const int GRID_OFFSET_X = 400; // Adjust horizontal offset
const int GRID_OFFSET_Y = 100; // Adjust vertical offset
const int OBJECT_MENU_WIDTH = 100; // Width of the object menu
const int OBJECT_MENU_OFFSET = 130; // Offset from the right edge of the window
const int OBJECT_MENU_Y = 100; // Offset from the right edge of the window