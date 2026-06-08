add_library(lib_core
  Manpower.cpp
  Game.cpp
)

set (BUILD_SHARED_LIBS FALSE)

FetchContent_Declare( sfml
    URL https://github.com/SFML/SFML/archive/refs/tags/3.0.1.tar.gz
)
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)


set(CMAKE_CXX_STANDARD 23)

target_include_directories(lib_core PUBLIC ./)
#target_link_libraries(main PUBLIC lib_core pugixml sfml-graphics)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
