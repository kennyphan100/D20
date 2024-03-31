//! @file
//! @brief Implementation file for TestItem - CppUnit test cases for the Item class.
//!

#include "TestItem.h"

//! @brief Set up function for the test cases that is executed before each test case.
void TestItem::setUp(void)
{
    HelmetObject = new Helmet("Helmet");
    ArmorObject = new Armor("Armor");
    ShieldObject = new Shield("Shield");
    RingObject = new Ring("Ring");
    BeltObject = new Belt("Belt");
    BootsObject = new Boots("Boots");
    WeaponObject = new Weapon("Weapon");

    ContainerObject = new Backpack("MyBackpack");
}

//! @brief Tear down function for the test cases that is executed after each test case. Typically used for deallocation.
void TestItem::tearDown(void)
{
    delete HelmetObject;
    delete ArmorObject;
    delete ShieldObject;
    delete RingObject;
    delete BeltObject;
    delete BootsObject;
    delete WeaponObject;
    delete ContainerObject;
}

//! @brief Test case for checking Shield enhancement.
void TestItem::testShieldEnhancement() {
    Shield shield("Shield");
    auto enhancement = shield.getEnhancement();
    CPPUNIT_ASSERT(enhancement.first == EnhancementType::ArmorClass);
    CPPUNIT_ASSERT(enhancement.second >= 1 && enhancement.second <= 5);
}

//! @brief Test case for checking Armor enhancement.
void TestItem::testArmorEnhancement() {
    Armor armor("Armor");
    auto enhancement = armor.getEnhancement();
    CPPUNIT_ASSERT(enhancement.first == EnhancementType::ArmorClass);
    CPPUNIT_ASSERT(enhancement.second >= 1 && enhancement.second <= 5);
}

//! @brief Test case for checking Helmet enhancement.
void TestItem::testHelmetEnhancement() {
    Helmet helmet("Helmet");
    auto enhancement = helmet.getEnhancement();
    CPPUNIT_ASSERT((enhancement.first == EnhancementType::Wisdom) || (enhancement.first == EnhancementType::Intelligence) || (enhancement.first == EnhancementType::ArmorClass));
    CPPUNIT_ASSERT(enhancement.second >= 1 && enhancement.second <= 5);
}

//! @brief Test case for checking Ring enhancement.
void TestItem::testRingEnhancement() {
    Ring ring("Ring");
    auto enhancement = ring.getEnhancement();
    CPPUNIT_ASSERT((enhancement.first == EnhancementType::Strength) || (enhancement.first == EnhancementType::Constitution) || (enhancement.first == EnhancementType::ArmorClass) || (enhancement.first == EnhancementType::Wisdom) || (enhancement.first == EnhancementType::Charisma));
    CPPUNIT_ASSERT(enhancement.second >= 1 && enhancement.second <= 5);
}

//! @brief Test case for checking Weapon enhancement.
void TestItem::testWeaponEnhancement() {
    Weapon weapon("Weapon");
    auto enhancement = weapon.getEnhancement();
    CPPUNIT_ASSERT((enhancement.first == EnhancementType::AttackBonus) || (enhancement.first == EnhancementType::DamageBonus));
    CPPUNIT_ASSERT(enhancement.second >= 1 && enhancement.second <= 5);
}

//! @brief Test case for checking Boots enhancement.
void TestItem::testBootsEnhancement() {
    Boots boots("Boots");
    auto enhancement = boots.getEnhancement();
    CPPUNIT_ASSERT((enhancement.first == EnhancementType::Dexterity) || (enhancement.first == EnhancementType::ArmorClass));
    CPPUNIT_ASSERT(enhancement.second >= 1 && enhancement.second <= 5);
}

//! @brief Test case for adding an item into the container.
void TestItem::testAddItemInContainer() {
    int size = ContainerObject->getSize();
    ContainerObject->addItem(ShieldObject);
    CPPUNIT_ASSERT(ContainerObject->getSize() == size + 1);
}

//! @brief Test case for removing an item from the container.
void TestItem::testRemoveItemFromContainer() {
    int size = ContainerObject->getSize();
    ContainerObject->removeItem(ArmorObject->getName());
    CPPUNIT_ASSERT(ContainerObject->getSize() == 0);
}