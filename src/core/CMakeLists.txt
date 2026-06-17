add_library(lib_core
  Manpower.cpp
  Game.cpp
        Food.cpp
        Soldiers.cpp
        Peasents.cpp
        Materials.cpp
        GameEvent.cpp
        EventStrategy.h
        FoodEventStrategy.h
        FoodEventStrategy.cpp
        MaterialsEventStrategy.h
        MaterialsEventStrategy.cpp
        PeasentAvailableEventStrategy.h
        PeasentAvailableEventStrategy.cpp
        EventStrategyFactory.h
)

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
