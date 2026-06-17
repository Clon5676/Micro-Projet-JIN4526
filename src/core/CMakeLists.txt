add_library(lib_core
        Resources.cpp
        ResourcePackage.cpp
  Manpower.cpp
  Game.cpp
        GameInput.cpp
        GameActions.cpp
        DialogueScene.cpp
        Food.cpp
        Soldiers.cpp
        Peasents.cpp
        Materials.cpp
        Event.cpp
)

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
