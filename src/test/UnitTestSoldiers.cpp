#include <gtest/gtest.h>

#include "Soldiers.h"

TEST(Soldiers, Constructor) {
    Soldiers soldiers = Soldiers(100, "Soldier.png", 100, 100, 1.0, 1.0);

    ASSERT_EQ(1.0, soldiers.getStrenght());
    ASSERT_EQ(100, soldiers.getAvailable());
    ASSERT_EQ(100, soldiers.getHealth());
    ASSERT_EQ(100, soldiers.getQuantity());
    ASSERT_EQ(1.0, soldiers.getMoral());
    ASSERT_EQ("Soldier.png", soldiers.getSprite());
}

TEST(Soldiers, action) {
    Soldiers soldiers = Soldiers(100, "Soldier.png", 100, 100, 1.0, 1.0);

    int nb = soldiers.action(50);

    ASSERT_EQ(50, soldiers.getAvailable());
    ASSERT_EQ(0.9, soldiers.getMoral());
    ASSERT_EQ(nb, 50);
}