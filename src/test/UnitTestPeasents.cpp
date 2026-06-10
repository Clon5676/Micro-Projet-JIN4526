#include <gtest/gtest.h>

#include "Peasents.h"

TEST(Peasents, constructor) {
    Peasents peasents = Peasents(1.0,"Peasent.png", 100, 100, 1.0, 100 );

    ASSERT_EQ(1.0, peasents.getProductivity());
    ASSERT_EQ(100, peasents.getAvailable());
    ASSERT_EQ(100, peasents.getHealth());
    ASSERT_EQ(100, peasents.getQuantity());
    ASSERT_EQ(1.0, peasents.getMoral());
    ASSERT_EQ("Peasent.png", peasents.getSprite());
}