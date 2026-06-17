#include <gtest/gtest.h>

#include "Food.h"
#include "Materials.h"
#include "ResourcePackage.h"

TEST(ResourcePackage, constructorUsesProvidedName) {
    ResourcePackage stockpile("Stockpile");

    ASSERT_EQ("Stockpile", stockpile.getName());
    ASSERT_EQ(0, stockpile.getQuantity());
}

TEST(ResourcePackage, getQuantitySumsAllChildren) {
    Food food = Food(25);
    Materials materials = Materials(75);
    ResourcePackage stockpile("Stockpile");

    stockpile.add(food);
    stockpile.add(materials);

    ASSERT_EQ(100, stockpile.getQuantity());
}

TEST(ResourcePackage, setQuantityAndAddQuantityAffectFirstChildOnly) {
    Food food = Food(25);
    Materials materials = Materials(75);
    ResourcePackage stockpile("Stockpile");

    stockpile.add(food);
    stockpile.add(materials);

    stockpile.setQuantity(30);
    ASSERT_EQ(30, food.getQuantity());
    ASSERT_EQ(75, materials.getQuantity());
    ASSERT_EQ(105, stockpile.getQuantity());

    stockpile.addQuantity(5);
    ASSERT_EQ(35, food.getQuantity());
    ASSERT_EQ(110, stockpile.getQuantity());
}

TEST(ResourcePackage, spendConsumesChildrenInOrder) {
    Food food = Food(25);
    Materials materials = Materials(75);
    ResourcePackage stockpile("Stockpile");

    stockpile.add(food);
    stockpile.add(materials);

    ASSERT_TRUE(stockpile.spend(40));

    ASSERT_EQ(0, food.getQuantity());
    ASSERT_EQ(60, materials.getQuantity());
    ASSERT_EQ(60, stockpile.getQuantity());
}

TEST(ResourcePackage, spendFailsWithoutChangingChildrenWhenAmountIsInvalidOrTooHigh) {
    Food food = Food(25);
    Materials materials = Materials(75);
    ResourcePackage stockpile("Stockpile");

    stockpile.add(food);
    stockpile.add(materials);

    ASSERT_FALSE(stockpile.spend(-1));
    ASSERT_FALSE(stockpile.spend(101));

    ASSERT_EQ(25, food.getQuantity());
    ASSERT_EQ(75, materials.getQuantity());
}

TEST(ResourcePackage, clearRemovesChildrenFromTotal) {
    Food food = Food(25);
    ResourcePackage stockpile("Stockpile");

    stockpile.add(food);
    stockpile.clear();

    ASSERT_EQ(0, stockpile.getQuantity());
}
