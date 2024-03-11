#include "TestMapEditorBuilder.h"

void TestMapEditorBuilder::setUp() {
    builder = new MapEditorBuilder("test_map.txt");
}

void TestMapEditorBuilder::tearDown() {
    delete builder;
}

void TestMapEditorBuilder::testMapDimensions() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map != nullptr);
    CPPUNIT_ASSERT_EQUAL(10, map->getWidth());
    CPPUNIT_ASSERT_EQUAL(10, map->getHeight());
}

void TestMapEditorBuilder::testStartAndFinishPositions() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map->getCell(4, 4) == Cell::START);
    CPPUNIT_ASSERT(map->getCell(8, 5) == Cell::FINISH);
}

void TestMapEditorBuilder::testWallsAndOccupiedCells() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map->getCell(2, 2) == Cell::WALL);
    CPPUNIT_ASSERT(map->getCell(3, 2) == Cell::OCCUPIED);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestMapEditorBuilder);
