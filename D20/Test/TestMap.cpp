//! @file 
//! @brief File containing the implementation of the Test Methods for Map
//!

#include "TestMap.h"

// setUp() method that is executed before all the test cases
void TestMap::setUp(void)
{
	MapObjectWithExistingPath = new Map(10, 10, "test");
	MapObjectWithoutExistingPath = new Map(10, 10, "test");

	for (int x = 0; x < 10; x++) {
		MapObjectWithoutExistingPath->setCell(x, 5, Cell::WALL);
	}
}

// tearDown() method that is executed after all the test cases
// typically does memory deallocation
void TestMap::tearDown(void)
{
	delete MapObjectWithExistingPath;
	delete MapObjectWithoutExistingPath;
}

// Test Case: Cell coordinates are in bounds.
void TestMap::testSetCellInBounds(void)
{
	CPPUNIT_ASSERT_NO_THROW(MapObjectWithExistingPath->setCell(1, 1, Cell::WALL));
}

// Test Case: Cell coordinates are out of bounds.
void TestMap::testSetCellOutOfBounds(void)
{
	CPPUNIT_ASSERT_THROW(MapObjectWithExistingPath->setCell(10, 10, Cell::WALL), out_of_range);
}

// Test Case: Cell coordinate is empty
void TestMap::testIsEmptyCellReturnsTrue(void)
{
	CPPUNIT_ASSERT(MapObjectWithExistingPath->isEmptyCell(0, 5));
}

// Test Case: Cell coordinate is not empty
void TestMap::testIsEmptyCellReturnsFalse(void)
{
	CPPUNIT_ASSERT(false == MapObjectWithoutExistingPath->isEmptyCell(0, 5));
}

// Test Case: Existing path
void TestMap::testVerifyMapExistingPath(void)
{
	CPPUNIT_ASSERT(MapObjectWithExistingPath->verifyMap());
}

// Test Case: Non-existing path
void TestMap::testVerifyMapNonExistingPath(void)
{
	CPPUNIT_ASSERT(false == MapObjectWithoutExistingPath->verifyMap());
}

