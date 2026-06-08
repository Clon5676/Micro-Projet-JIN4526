add_executable(main
  Main.cpp
)
add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources/init.xml)
file(GLOB RESOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/resources/*.*)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/init.xml
                   DEPENDS ${RESOURCES}
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${RESOURCES}
                           ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(main copy-resources)


target_link_libraries(main PUBLIC lib_core)
