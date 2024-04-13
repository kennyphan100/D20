#pragma once
enum class ObjectType {
    None,
    Wall,
    Chest,
    Door,
    Character,
    Aggressor,
    Friendly,
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

const int INVENTORY_OFFSET_X = 900;
const int INVENTORY_OFFSET_Y = 150;
const int INVENTORY_GRID_WIDTH = 5;
const int INVENTORY_GRID_HEIGHT = 5;
const int INVENTORY_CELL_SIZE = 50;

const float UNEQUIP_BUTTON_OFFSET_X = 900; // Same X offset as the inventory
const float UNEQUIP_BUTTON_OFFSET_Y = INVENTORY_OFFSET_Y + (INVENTORY_GRID_HEIGHT * INVENTORY_CELL_SIZE) + 20; // Place it below the inventory
const float UNEQUIP_BUTTON_WIDTH = 170;
const float UNEQUIP_BUTTON_HEIGHT = 30;

const int OBJECT_MENU_WIDTH = 100; // Width of the object menu
const int OBJECT_MENU_OFFSET = 130; // Offset from the right edge of the window
const int OBJECT_MENU_Y = 100; // Offset from the right edge of the window