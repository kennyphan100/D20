//! @file
//! @brief File containing the Test Class declaration for MapGameBuilder

#ifndef TESTMAPGAMEBUILDER_H
#define TESTMAPGAMEBUILDER_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "MapGameBuilder.h"

/**
 * @class TestMapGameBuilder
 * @brief Test suite for the MapGameBuilder class.
 *
 * This set of unit tests is designed to validate the functionalities of the MapGameBuilder class,
 * including map dimensions, start and finish positions, as well as walls and occupied cells configuration.
 */
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
