#include <gtest/gtest.h>

#include "Peasents.h"

TEST(Manpower, addPeopleIgnoresNonPositiveAmounts) {
    Peasents peasents = Peasents(10, "Peasent.png", 5, 100, 1.0, 1.0);

    peasents.addPeople(0);
    peasents.addPeople(-3);

    ASSERT_EQ(10, peasents.getQuantity());
    ASSERT_EQ(5, peasents.getAvailable());
}

TEST(Manpower, addPeopleIncreasesQuantityAndAvailablePeople) {
    Peasents peasents = Peasents(10, "Peasent.png", 5, 100, 1.0, 1.0);

    peasents.addPeople(3);

    ASSERT_EQ(13, peasents.getQuantity());
    ASSERT_EQ(8, peasents.getAvailable());
}

TEST(Manpower, usePeopleRejectsInvalidOrUnavailableAmounts) {
    Peasents peasents = Peasents(10, "Peasent.png", 5, 100, 1.0, 1.0);

    ASSERT_FALSE(peasents.usePeople(-1));
    ASSERT_FALSE(peasents.usePeople(6));
    ASSERT_EQ(5, peasents.getAvailable());
}

TEST(Manpower, restRestoresAvailabilityAndConsumesFeedBonus) {
    Peasents peasents = Peasents(10, "Peasent.png", 5, 100, 1.0, 1.0);

    ASSERT_TRUE(peasents.usePeople(3));
    peasents.feeded();
    peasents.rest();

    ASSERT_EQ(10, peasents.getAvailable());
    ASSERT_EQ(1.5, peasents.getMoral());

    peasents.rest();
    ASSERT_EQ(1.5, peasents.getMoral());
}

TEST(Manpower, MoralIsNotBellow0) {
	Peasents peasents = Peasents(10, "Peasent.png", 5, 100, 0, 1.0);
	peasents.action(5);
	ASSERT_EQ(0, peasents.getMoral());
}

TEST(Manpower, MoralIsNotAbove2) {
    Peasents peasents = Peasents(10, "Peasent.png", 5, 100, 1.9, 1.0);
    peasents.feeded();
    peasents.rest();
    ASSERT_EQ(2, peasents.getMoral());
}
