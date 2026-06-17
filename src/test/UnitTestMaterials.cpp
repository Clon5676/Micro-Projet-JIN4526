#include <gtest/gtest.h>

#include "Materials.h"

TEST(Materials, constructor) {
    Materials materials = Materials(100);

    ASSERT_EQ(100, materials.getQuantity());
    ASSERT_EQ("Materials", materials.getName());
}

TEST(Materials, spendRemovesQuantityWhenEnoughIsAvailable) {
    Materials materials = Materials(100);

    ASSERT_TRUE(materials.spend(35));

    ASSERT_EQ(65, materials.getQuantity());
}
