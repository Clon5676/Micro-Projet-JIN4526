add_library(lib_core
  Manpower.cpp
  Game.cpp
        GameInput.cpp
        GameActions.cpp
        DialogueScene.cpp
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
        PeasentEventStrategy.h
        PeasentEventStrategy.cpp
        SoldierEventStrategy.h
        SoldierEventStrategy.cpp
        SoldierAvailableEventStrategy.h
        SoldierAvailableEventStrategy.cpp
        EnemyHealthEventStrategy.h
        EnemyHealthEventStrategy.cpp
)

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
