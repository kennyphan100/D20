#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Map.h"

class TestMap : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestMap);
    CPPUNIT_TEST(testSetCellInBounds);
    CPPUNIT_TEST(testSetCellOutOfBounds);
    CPPUNIT_TEST(testVerifyMapExistingPath);
    CPPUNIT_TEST(testVerifyMapNonExistingPath);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testSetCellInBounds(void);
    void testSetCellOutOfBounds(void);
    void testVerifyMapExistingPath(void);
    void testVerifyMapNonExistingPath(void);
private:
    Map* MapObjectWithExistingPath;
    Map* MapObjectWithoutExistingPath;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestMap);