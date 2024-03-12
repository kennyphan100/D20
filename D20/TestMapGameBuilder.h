#ifndef TESTMAPGAMEBUILDER_H
#define TESTMAPGAMEBUILDER_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "MapGameBuilder.h"

class TestMapGameBuilder : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestMapGameBuilder);
    CPPUNIT_TEST(testMapDimensions);
    CPPUNIT_TEST(testStartAndFinishPositions);
    CPPUNIT_TEST(testWallsAndOccupiedCells);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;
    void tearDown() override;

    void testMapDimensions();
    void testStartAndFinishPositions();
    void testWallsAndOccupiedCells();

private:
    MapGameBuilder* builder;
};

#endif // TESTMAPGAMEBUILDER_H
