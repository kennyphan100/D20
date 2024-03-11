#include "TestMapGameBuilder.h"

void TestMapGameBuilder::setUp() {
    builder = new MapGameBuilder("test_map.txt", 10);
}

void TestMapGameBuilder::tearDown() {
    delete builder;
}

void TestMapGameBuilder::testMapDimensions() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map != nullptr);
    CPPUNIT_ASSERT_EQUAL(10, map->getWidth());
    CPPUNIT_ASSERT_EQUAL(10, map->getHeight());
}

void TestMapGameBuilder::testStartAndFinishPositions() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map->getCell(4, 4) == Cell::START);
    CPPUNIT_ASSERT(map->getCell(8, 5) == Cell::FINISH);
}

void TestMapGameBuilder::testWallsAndOccupiedCells() {
    Map* map = builder->getMap();
    CPPUNIT_ASSERT(map->getCell(2, 2) == Cell::WALL);
    CPPUNIT_ASSERT(map->getCell(3, 2) == Cell::OCCUPIED);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestMapGameBuilder);
