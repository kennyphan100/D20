//! @file
//! @brief Implementation file for TestMapGameBuilder - CppUnit test cases for the MapGameBuilder class.
//!

#include "TestMapGameBuilder.h"

//! @brief Sets up the test fixture.
//! Instantiates a MapGameBuilder object with a test map file and dimensions.
void TestMapGameBuilder::setUp() {
    builder = new MapGameBuilder("./Test/test_map.txt", 10);
}

//! @brief Tears down the test fixture.
//! Deletes the MapGameBuilder object.
void TestMapGameBuilder::tearDown() {
    delete builder;
}

//! @brief Test case to check map dimensions.
//! Checks if the generated map has the expected width and height.
void TestMapGameBuilder::testMapDimensions() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map != nullptr);
    CPPUNIT_ASSERT_EQUAL(10, map->getWidth());
    CPPUNIT_ASSERT_EQUAL(10, map->getHeight());
}

//! @brief Test case to check start and finish positions.
//! Checks if the generated map has the correct start and finish positions.
void TestMapGameBuilder::testStartAndFinishPositions() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map->getCell(4, 4) == Cell::START);
    CPPUNIT_ASSERT(map->getCell(8, 5) == Cell::FINISH);
}

//! @brief Test case to check walls and occupied cells.
//! Checks if the generated map has the correct walls and occupied cells.
void TestMapGameBuilder::testWallsAndOccupiedCells() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map->getCell(2, 2) == Cell::WALL);
    CPPUNIT_ASSERT(map->getCell(3, 2) == Cell::OCCUPIED);
}

//! @brief Registers the test suite.
CPPUNIT_TEST_SUITE_REGISTRATION(TestMapGameBuilder);
