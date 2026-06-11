add_executable(main
  Main.cpp
)

add_custom_target(copy-resources ALL
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_SOURCE_DIR}/src/resources
                          ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(main copy-resources)


target_link_libraries(main PUBLIC lib_core)
