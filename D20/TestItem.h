//! @file
//! @brief Header file for the TestItem class - CppUnit test cases for the Item class.
//!

#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Item.h"

/**
 * @class TestItem
 * @brief Test class for Item, utilizing the CppUnit framework.
 *
 * This class is designed to implement test cases for testing the functionality of the Item class. It aims to verify the correctness
 * of the items' enhancement, adding item, and removing item from an item container functionality.
 */
class TestItem : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestItem);
    CPPUNIT_TEST(testShieldEnhancement);
    CPPUNIT_TEST(testArmorEnhancement);
    CPPUNIT_TEST(testHelmetEnhancement);
    CPPUNIT_TEST(testRingEnhancement);
    CPPUNIT_TEST(testWeaponEnhancement);
    CPPUNIT_TEST(testBootsEnhancement);
    CPPUNIT_TEST(testAddItemInContainer);
    CPPUNIT_TEST(testRemoveItemFromContainer);
    CPPUNIT_TEST_SUITE_END();

public:
    //! @brief Set up function for the test cases.
    void setUp(void);
    //! @brief Tear down function for the test cases.
    void tearDown(void);

protected:
    //! @brief Test case for checking Shield enhancement.
    void testShieldEnhancement();
    //! @brief Test case for checking Armor enhancement.
    void testArmorEnhancement();
    //! @brief Test case for checking Helmet enhancement.
    void testHelmetEnhancement();
    //! @brief Test case for checking Ring enhancement.
    void testRingEnhancement();
    //! @brief Test case for checking Weapon enhancement.
    void testWeaponEnhancement();
    //! @brief Test case for checking Boots enhancement.
    void testBootsEnhancement();
    //! @brief Test case for adding an item into the container.
    void testAddItemInContainer();
    //! @brief Test case for removing an item from the container.
    void testRemoveItemFromContainer();
private:
    Item* HelmetObject; //!< Pointer to a Helmet object.
    Item* ArmorObject; //!< Pointer to an Armor object.
    Item* ShieldObject; //!< Pointer to a Shield object.
    Item* RingObject; //!< Pointer to a Ring object.
    Item* BeltObject; //!< Pointer to a Belt object.
    Item* BootsObject; //!< Pointer to a Boots object.
    Item* WeaponObject; //!< Pointer to a Weapon object.
    ItemContainer* ContainerObject; //!< Pointer to an ItemContainer object.
};

//! @brief Register the test suite.
CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);