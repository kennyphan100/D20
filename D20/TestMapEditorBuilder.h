//! @file
//! @brief File containing the Test Class declaration for MapEditorBuilder

#ifndef TESTMAPEDITORBUILDER_H
#define TESTMAPEDITORBUILDER_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "MapEditorBuilder.h"

/**
 * @class TestMapEditorBuilder
 * @brief Test suite for the MapEditorBuilder class.
 *
 * This set of unit tests is designed to validate the functionalities of the MapEditorBuilder class,
 * including map dimensions, start and finish positions, as well as walls and occupied cells configuration.
 */
class TestMapEditorBuilder : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestMapEditorBuilder);
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
    MapEditorBuilder* builder;
};

#endif // TESTMAPEDITORBUILDER_H
