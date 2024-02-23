#include "TestDice.h"

// setUp() method that is executed before all the test cases
void TestDice::setUp(void)
{
	DiceObject = new Dice();
}

// tearDown() method that is executed after all the test cases
// typically does memory deallocation
void TestDice::tearDown(void)
{
	delete DiceObject;
}

// Test Case: Invalid format
void TestDice::testRollDiceInvalidFormat(void)
{
	CPPUNIT_ASSERT_EQUAL(-1, DiceObject->rollDice("3d+5"));
}

// Test Case: Invalid dice type
void TestDice::testRollDiceInvalidDiceType(void)
{
	CPPUNIT_ASSERT_NO_THROW(-1, DiceObject->rollDice("3d2+5"));
}

// Test Case: Valid dice
void TestDice::testRollDiceValid(void)
{
	CPPUNIT_ASSERT_NO_THROW(DiceObject->rollDice("3d6+5"));
}


