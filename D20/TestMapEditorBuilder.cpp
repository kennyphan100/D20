//! @file
//! @brief Implementation file for TestMapEditorBuilder - CppUnit test cases for the MapEditorBuilder class.
//!

#include "TestMapEditorBuilder.h"

//! @brief Sets up the test fixture.
//! Instantiates a MapEditorBuilder object with a test map file.
void TestMapEditorBuilder::setUp() {
    builder = new MapEditorBuilder("test_map.txt");
}

//! @brief Tears down the test fixture.
//! Deletes the MapEditorBuilder object.
void TestMapEditorBuilder::tearDown() {
    delete builder;
}

//! @brief Test case to check map dimensions.
//! Checks if the generated map has the expected width and height
void TestMapEditorBuilder::testMapDimensions() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map != nullptr);
    CPPUNIT_ASSERT_EQUAL(10, map->getWidth());
    CPPUNIT_ASSERT_EQUAL(10, map->getHeight());
}

//! @brief Test case to check start and finish positions.
//! Checks if the generated map has the correct start and finish positions.
void TestMapEditorBuilder::testStartAndFinishPositions() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map->getCell(4, 4) == Cell::START);
    CPPUNIT_ASSERT(map->getCell(8, 5) == Cell::FINISH);
}

//! @brief Test case to check walls and occupied cells.
//! Checks if the generated map has the correct walls and occupied cells.
void TestMapEditorBuilder::testWallsAndOccupiedCells() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map->getCell(2, 2) == Cell::WALL);
    CPPUNIT_ASSERT(map->getCell(3, 2) == Cell::OCCUPIED);
}

//! @brief Registers the test suite.
CPPUNIT_TEST_SUITE_REGISTRATION(TestMapEditorBuilder);
