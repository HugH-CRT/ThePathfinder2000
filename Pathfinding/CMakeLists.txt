# CMakeLists PROJECT Pathfinding


set(CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Pathfinding/src")

set(SOURCES
	"${CMAKE_SOURCE_DIR}/main.cpp" 
	"${CMAKE_SOURCE_DIR}/lib/ImGUI/imgui.cpp"
	"${CMAKE_SOURCE_DIR}/lib/ImGUI/imgui_tables.cpp"
	"${CMAKE_SOURCE_DIR}/lib/ImGUI/imgui_widgets.cpp"
	"${CMAKE_SOURCE_DIR}/lib/ImGUI/imgui_draw.cpp"
    # Pour demo 
    "${CMAKE_SOURCE_DIR}/lib/ImGUI/imgui_demo.cpp"
    # Link src : ImGui to SFML
	"${CMAKE_SOURCE_DIR}/lib/ImGUI-SFML/imgui-SFML.cpp"
)

add_executable(Pathfinding ${SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(Pathfinding ${OPENGL_gl_LIBRARY})

target_include_directories(Pathfinding PUBLIC
    "${CMAKE_SOURCE_DIR}/lib/SFML/include"
    "${CMAKE_SOURCE_DIR}/lib/ImGUI"
    "${CMAKE_SOURCE_DIR}/lib/ImGUI/backends"
    "${CMAKE_SOURCE_DIR}/lib/ImGUI-SFML"
)

target_link_directories(Pathfinding PUBLIC
    "${CMAKE_SOURCE_DIR}/lib/SFML/lib" 
)

file(GLOB_RECURSE OTHER_LINK_LIBRARIES  ${CMAKE_SOURCE_DIR}/lib/SFML/lib/*.lib)

target_link_libraries(Pathfinding ${OTHER_LINK_LIBRARIES})

add_custom_command(TARGET Pathfinding PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/lib/SFML/bin/ $<TARGET_FILE_DIR:Pathfinding>
)

if (CMAKE_VERSION VERSION_GREATER 3.8)
  set_property(TARGET Pathfinding PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET Pathfinding PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET Pathfinding PROPERTY CXX_STANDARD_REQUIRED on)