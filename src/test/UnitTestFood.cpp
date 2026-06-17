#include <gtest/gtest.h>

#include "../core/Food.h"

class MyFixture : public ::testing::Test {
  protected:

      void SetUp() override {
          food = Food(100, "fichier.png");
      }

      void TearDown() override {
          food = Food();
      }

      Food food;
};

TEST(Food, constructor) {
    Food food = Food(100, "fichier.png");

    ASSERT_EQ(100, food.getQuantity());
    ASSERT_EQ("Food", food.getName());
}

TEST_F(MyFixture, setQuantity) {
    food.setQuantity(50);
    ASSERT_EQ(50, food.getQuantity());
}

TEST_F(MyFixture, addQuantity) {
    food.addQuantity(50);
    ASSERT_EQ(150, food.getQuantity());
}

TEST_F(MyFixture, setQuantityDoesNotGoBelowZero) {
    food.setQuantity(-10);
    ASSERT_EQ(0, food.getQuantity());
}

TEST_F(MyFixture, addQuantityDoesNotGoBelowZero) {
    food.addQuantity(-150);
    ASSERT_EQ(0, food.getQuantity());
}

TEST_F(MyFixture, spendRemovesQuantityWhenEnoughIsAvailable) {
    ASSERT_TRUE(food.spend(40));
    ASSERT_EQ(60, food.getQuantity());
}

TEST_F(MyFixture, spendFailsWhenAmountIsInvalidOrTooHigh) {
    ASSERT_FALSE(food.spend(-1));
    ASSERT_FALSE(food.spend(101));
    ASSERT_EQ(100, food.getQuantity());
}
