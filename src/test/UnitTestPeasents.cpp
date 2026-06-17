#include <gtest/gtest.h>

#include "Peasents.h"

TEST(Peasents, constructor) {
    Peasents peasents = Peasents(100, "Peasent.png", 100, 100, 1.0, 1.0);

    ASSERT_EQ(1.0, peasents.getProductivity());
    ASSERT_EQ(100, peasents.getAvailable());
    ASSERT_EQ(100, peasents.getHealth());
    ASSERT_EQ(100, peasents.getQuantity());
    ASSERT_EQ(1.0, peasents.getMoral());
    ASSERT_EQ("Manpower", peasents.getName());
}

TEST(Peasents, action) {
    Peasents peasents = Peasents(100, "Peasent.png", 100, 100, 1.0, 1.0);

    int nb = peasents.action(50);

    ASSERT_EQ(1.1, peasents.getProductivity());
    ASSERT_EQ(50, peasents.getAvailable());
    ASSERT_EQ(0.9, peasents.getMoral());
    ASSERT_GE(nb, 40);
    ASSERT_LE(nb, 60);
}

TEST(Peasents, rest) {
    Peasents peasents = Peasents(100, "Peasent.png", 100, 100, 1.0, 1.0);
    peasents.action(50);

    ASSERT_EQ(50, peasents.getAvailable());

    peasents.rest();

    ASSERT_EQ(100, peasents.getAvailable());
}

TEST(Peasents, actionFailsWhenNotEnoughPeopleAreAvailable) {
    Peasents peasents = Peasents(100, "Peasent.png", 10, 100, 1.0, 1.0);

    int resources = peasents.action(11);

    ASSERT_EQ(0, resources);
    ASSERT_EQ(10, peasents.getAvailable());
    ASSERT_EQ(1.0, peasents.getProductivity());
    ASSERT_EQ(1.0, peasents.getMoral());
}

TEST(Peasents, recruitSpendsFoodAndAddsOneAvailablePeasant) {
    Food food = Food(20, "Food.png");
    Peasents peasents = Peasents(2, "Peasent.png", 2, 100, 1.0, 1.0);

    ASSERT_TRUE(peasents.recruit(food));

    ASSERT_EQ(0, food.getQuantity());
    ASSERT_EQ(3, peasents.getQuantity());
    ASSERT_EQ(3, peasents.getAvailable());
}

TEST(Peasents, recruitFailsWithoutEnoughFood) {
    Food food = Food(19, "Food.png");
    Peasents peasents = Peasents(2, "Peasent.png", 2, 100, 1.0, 1.0);

    ASSERT_FALSE(peasents.recruit(food));

    ASSERT_EQ(19, food.getQuantity());
    ASSERT_EQ(2, peasents.getQuantity());
    ASSERT_EQ(2, peasents.getAvailable());
}
