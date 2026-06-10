#include <gtest/gtest.h>

#include "Peasents.h"

TEST(Peasents, constructor) {
    Peasents peasents = Peasents(100, "Peasent.png", 100, 100, 1.0, 1.0);

    ASSERT_EQ(1.0, peasents.getProductivity());
    ASSERT_EQ(100, peasents.getAvailable());
    ASSERT_EQ(100, peasents.getHealth());
    ASSERT_EQ(100, peasents.getQuantity());
    ASSERT_EQ(1.0, peasents.getMoral());
    ASSERT_EQ("Peasent.png", peasents.getSprite());
}

TEST(Peasents, action) {
    Peasents peasents = Peasents(100, "Peasent.png", 100, 100, 1.0, 1.0);

    int nb = peasents.action(50);

    ASSERT_EQ(1.1, peasents.getProductivity());
    ASSERT_EQ(50, peasents.getAvailable());
    ASSERT_EQ(0.9, peasents.getMoral());
    ASSERT_EQ(nb, 50);
}

TEST(Peasents, rest) {
    Peasents peasents = Peasents(100, "Peasent.png", 100, 100, 1.0, 1.0);
    peasents.action(50);

    ASSERT_EQ(50, peasents.getAvailable());

    peasents.rest();

    ASSERT_EQ(100, peasents.getAvailable());
}