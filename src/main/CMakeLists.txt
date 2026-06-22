add_executable(main
  Main.cpp
)

add_custom_target(copy-resources ALL
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_SOURCE_DIR}/src/resources
                          ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(main copy-resources)


target_link_libraries(main PUBLIC lib_core)

if(APPLE)
    # ── macOS (ld) ────────────────────────────────────────────────────────────
    target_link_options(main PRIVATE
            -Wl,-force_load,$<TARGET_FILE:lib_core>
    )

elseif(WIN32)
    # ── Windows ───────────────────────────────────────────────────────────────
    if(MSVC)
        # Cas 1 : Visual Studio / MSVC
        target_link_options(main PRIVATE
                /WHOLEARCHIVE:$<TARGET_FILE:lib_core>
        )
    elseif(MINGW OR CYGWIN OR CMAKE_COMPILER_IS_GNUCC)
        # Cas 2 : MinGW / GCC sur Windows
        target_link_options(main PRIVATE
                -Wl,--whole-archive
                $<TARGET_FILE:lib_core>
                -Wl,--no-whole-archive
        )
    endif()

else()
    # ── Linux / Autres (GNU ld / lld) ─────────────────────────────────────────
    target_link_options(main PRIVATE
            -Wl,--whole-archive
            $<TARGET_FILE:lib_core>
            -Wl,--no-whole-archive
    )
endif()
