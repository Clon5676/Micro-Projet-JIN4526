#include <gtest/gtest.h>

#include "Event.h"

#include <filesystem>
#include <fstream>

namespace {
std::filesystem::path writeEventFile() {
    const std::filesystem::path path = std::filesystem::temp_directory_path() / "micro_projet_events_test.txt";
    std::ofstream file(path);
    file << "First event\n";
    file << "Second event\n";
    file << "Third event\n";
    return path;
}
}

TEST(Event, activateCyclesThroughLoadedEventsUsingDayModulo) {
    const std::filesystem::path path = writeEventFile();
    const Event event(path.string());

    ASSERT_EQ("First event", event.activate(0));
    ASSERT_EQ("Second event", event.activate(1));
    ASSERT_EQ("Third event", event.activate(2));
    ASSERT_EQ("First event", event.activate(3));

    std::filesystem::remove(path);
}
