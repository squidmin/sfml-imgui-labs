add_executable(geometry geometry.cpp ./tilemap/Tile.cpp ./tilemap/Canvas.cpp ./tilemap/Grid.cpp)
target_link_libraries(geometry PRIVATE ImGui-SFML::ImGui-SFML)

add_executable(sort_colors sort_colors.cpp)
target_link_libraries(sort_colors PRIVATE ImGui-SFML::ImGui-SFML)

add_executable(square_grid_1 square_grid_1.cpp)
target_link_libraries(square_grid_1 PRIVATE ImGui-SFML::ImGui-SFML)

add_executable(square_grid_2 square_grid_2.cpp)
target_link_libraries(square_grid_2 PRIVATE ImGui-SFML::ImGui-SFML)

# Copy DLLs needed for runtime on Windows
# if(WIN32)
#     if (BUILD_SHARED_LIBS)
#         add_custom_command(TARGET square_grid_1 POST_BUILD
#                 COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                 $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
#                 $<TARGET_FILE:sfml-graphics>
#                 $<TARGET_FILE:sfml-window>
#                 $<TARGET_FILE:sfml-system>
#                 $<TARGET_FILE_DIR:square_grid_1>)
#     endif()
#     if (BUILD_SHARED_LIBS)
#         add_custom_command(TARGET square_grid_2 POST_BUILD
#                 COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                 $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
#                 $<TARGET_FILE:sfml-graphics>
#                 $<TARGET_FILE:sfml-window>
#                 $<TARGET_FILE:sfml-system>
#                 $<TARGET_FILE_DIR:square_grid_2>)
#     endif()
# endif()
