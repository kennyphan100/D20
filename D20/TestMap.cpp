#include "TestMap.h"


// setUp() method that is executed before all the test cases
void TestMap::setUp(void)
{
	MapObjectWithExistingPath = new Map(10, 10);
	MapObjectWithoutExistingPath = new Map(10, 10);

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
	CPPUNIT_ASSERT_THROW(MapObjectWithExistingPath->setCell(10, 10, Cell::WALL), std::out_of_range);
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

