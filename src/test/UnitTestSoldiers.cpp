#include <gtest/gtest.h>

#include "Soldiers.h"

TEST(Soldiers, Constructor) {
    Soldiers soldiers = Soldiers(100, "Soldier.png", 100, 100, 1.0, 1.0);

    ASSERT_EQ(1.0, soldiers.getStrenght());
    ASSERT_EQ(100, soldiers.getAvailable());
    ASSERT_EQ(100, soldiers.getHealth());
    ASSERT_EQ(100, soldiers.getQuantity());
    ASSERT_EQ(1.0, soldiers.getMoral());
    ASSERT_EQ("Manpower", soldiers.getName());
}

TEST(Soldiers, action) {
    Soldiers soldiers = Soldiers(100, "Soldier.png", 100, 100, 1.0, 1.0);

    int nb = soldiers.action(50);

    ASSERT_EQ(50, soldiers.getAvailable());
    ASSERT_EQ(0.9, soldiers.getMoral());
    ASSERT_GE(nb, 40);
    ASSERT_LE(nb, 60);
}

TEST(Soldiers, actionFailsWhenNotEnoughPeopleAreAvailable) {
    Soldiers soldiers = Soldiers(100, "Soldier.png", 10, 100, 1.0, 1.0);

    int damage = soldiers.action(11);

    ASSERT_EQ(0, damage);
    ASSERT_EQ(10, soldiers.getAvailable());
    ASSERT_EQ(1.0, soldiers.getMoral());
}

TEST(Soldiers, getMaxRecruitableUsesScarcestResource) {
    Food food = Food(45);
    Materials materials = Materials(30);
    Soldiers soldiers = Soldiers(5, "Soldier.png", 5, 100, 1.0, 1.0);

    ASSERT_EQ(2, soldiers.getMaxRecruitable(food, materials));
}

TEST(Soldiers, recruitSpendsFoodAndMaterialsAndAddsSoldiers) {
    Food food = Food(45);
    Materials materials = Materials(45);
    Soldiers soldiers = Soldiers(5, "Soldier.png", 5, 100, 1.0, 1.0);

    ASSERT_TRUE(soldiers.recruit(food, materials, 2));

    ASSERT_EQ(15, food.getQuantity());
    ASSERT_EQ(15, materials.getQuantity());
    ASSERT_EQ(7, soldiers.getQuantity());
    ASSERT_EQ(7, soldiers.getAvailable());
}

TEST(Soldiers, recruitFailsForInvalidOrUnaffordableAmount) {
    Food food = Food(15);
    Materials materials = Materials(15);
    Soldiers soldiers = Soldiers(5, "Soldier.png", 5, 100, 1.0, 1.0);

    ASSERT_FALSE(soldiers.recruit(food, materials, 0));
    ASSERT_FALSE(soldiers.recruit(food, materials, 2));

    ASSERT_EQ(15, food.getQuantity());
    ASSERT_EQ(15, materials.getQuantity());
    ASSERT_EQ(5, soldiers.getQuantity());
    ASSERT_EQ(5, soldiers.getAvailable());
}
