//! @file
//! @brief File containing the Test Class declaration for Dice
//!

#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Map.h"

/**
 * @class TestMap
 * @brief Test suite for the Map class.
 *
 * This set of unit tests is designed to validate both basic and complex functionalities of the Map class,
 * including cell manipulation and path verification capabilities.
 */
class TestMap : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestMap);
    CPPUNIT_TEST(testSetCellInBounds);
    CPPUNIT_TEST(testSetCellOutOfBounds);
    CPPUNIT_TEST(testIsEmptyCellReturnsTrue);
    CPPUNIT_TEST(testIsEmptyCellReturnsFalse);
    CPPUNIT_TEST(testVerifyMapExistingPath);
    CPPUNIT_TEST(testVerifyMapNonExistingPath);
    CPPUNIT_TEST_SUITE_END();

public:
    /**
     * @brief Sets up test cases before each test method.
     * Initializes map objects with and without predefined paths.
     */
    void setUp(void);

    /**
     * @brief Cleans up after each test method.
     * Deallocates memory used by map objects.
     */
    void tearDown(void);

protected:
    /**
     * @brief Tests whether cells within bounds can be correctly set and retrieved.
     */
    void testSetCellInBounds(void);

    /**
     * @brief Tests if setting a cell outside the map boundaries is handled correctly.
     * Expects to catch an exception or receive an error flag indicating out-of-bounds.
     */
    void testSetCellOutOfBounds(void);

    /**
      * @brief Tests the isEmptyCell function to return true for an unoccupied cell.
      * Validates whether empty cells are correctly identified within the map.
      */
    void testIsEmptyCellReturnsTrue(void);

    /**
     * @brief Tests the isEmptyCell function to return false for a non-empty cell.
     * Ensures that walls or occupied cells are properly recognized as non-empty.
     */
    void testIsEmptyCellReturnsFalse(void);

    /**
     * @brief Tests verifyMap to confirm it correctly identifies a valid path from start to end.
     * A map with a clear path should result in verifyMap returning true.
     */
    void testVerifyMapExistingPath(void);

    /**
     * @brief Tests verifyMap to ensure it accurately detects when no valid path exists.
     * A map without a clear path from start to end, verifyMap should return false.
     */
    void testVerifyMapNonExistingPath(void);
private:
    Map* MapObjectWithExistingPath; ///< Pointer to a Map instance configured with a guaranteed path from start to finish.
    Map* MapObjectWithoutExistingPath; ///< Pointer to a Map instance where no path exists from start to finish.
};

//! @brief Register the test suite.
CPPUNIT_TEST_SUITE_REGISTRATION(TestMap);