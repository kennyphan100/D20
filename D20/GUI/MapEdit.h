#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"

using namespace std;

//enum class ObjectType {
//    None,
//    Wall,
//    Chest,
//    Door
//};
//
//struct Object {
//    int x, y;
//    ObjectType type;
//};
//
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//const int GRID_WIDTH = 10;
//const int GRID_HEIGHT = 10;
//const int CELL_SIZE = 40; // Adjust cell size as desired
//const int GRID_OFFSET_X = 400; // Adjust horizontal offset
//const int GRID_OFFSET_Y = 100; // Adjust vertical offset
//const int OBJECT_MENU_WIDTH = 100; // Width of the object menu
//const int OBJECT_MENU_OFFSET = 130; // Offset from the right edge of the window
//const int OBJECT_MENU_Y = 100; // Offset from the right edge of the window

class MapEdit {
public:
    enum ActiveInputField { CREATE, NAME, WIDTH, HEIGHT };
    MapEdit(sf::RenderWindow& window);

    void handleMapEditClick(int mouseX, int mouseY);
    void handleRemoveObject(int mouseX, int mouseY);
    void drawMapEdit();
    void drawGrid(sf::RenderWindow& window);
    void drawSelectedMapGrid(string selectedMap);
    void drawObjectMenu(sf::RenderWindow& window, ObjectType selectedObjectType);
    void loadMapFiles(const string& directoryPath);
    bool isClickOnMapList(int mouseX, int mouseY);

    vector<vector<ObjectType>> createMap(const vector<Object>& objects);

    bool isPrintableAscii(sf::Uint32 unicode);
    ActiveInputField getActiveField() const;

    sf::Text titleLabel;
    sf::RectangleShape editMapButton;
    sf::Text editMapButtonText;
    sf::Text mapLabel;
    sf::Text alertText;

    sf::Vector2f mapListStartPosition{ 50, 130 }; // Starting position of the map list
    float mapListItemSpacing = 30.0f;
    vector<string> mapFiles;
    vector<bool> mapSelections;

    std::vector<Object> objects;

    ObjectType selectedObjectType = ObjectType::None;
    sf::Texture wallTexture;
    sf::Texture chestTexture;
    sf::Texture doorTexture;

    int GRID_WIDTH = 10;
    int GRID_HEIGHT = 10;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    sf::Text backButton;

    string selectedMap;
    bool showSuccessfulAlert;
    bool showFailureAlert;
    ActiveInputField activeField;
};

