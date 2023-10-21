# CMakeLists PROJECT Pathfinding

set (PATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HEADERS
    "${PATH_DIR}/macro.h"
)

set(SOURCES
   "${PATH_DIR}/main.cpp" 




   # LIB 
   "${PATH_DIR}/lib/ImGUI/imgui.cpp"
   "${PATH_DIR}/lib/ImGUI/imgui_tables.cpp"
   "${PATH_DIR}/lib/ImGUI/imgui_widgets.cpp"
   "${PATH_DIR}/lib/ImGUI/imgui_draw.cpp"
   # Pour demo 
   "${PATH_DIR}/lib/ImGUI/imgui_demo.cpp"
   # Link src : ImGui to SFML
   "${PATH_DIR}/lib/ImGUI-SFML/imgui-SFML.cpp"
)

include_directories(${HEADERS})

add_executable(Pathfinding
    ${HEADERS}
    ${SOURCES}
)

find_package(OpenGL REQUIRED)
target_link_libraries(Pathfinding ${OPENGL_gl_LIBRARY})

target_include_directories(Pathfinding 
    PUBLIC
	$<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${HEADER_DIR}>
        "${PATH_DIR}/lib/SFML/include"
        "${PATH_DIR}/lib/ImGUI"
        "${PATH_DIR}/lib/ImGUI/backends"
        "${PATH_DIR}/lib/ImGUI-SFML"
)

target_link_directories(Pathfinding 
    PUBLIC
	"${PATH_DIR}/lib/SFML/lib"  
)

# Remove GLOB_RECURSE
file(GLOB_RECURSE OTHER_LINK_LIBRARIES  ${PATH_DIR}/lib/SFML/lib/*.lib)
target_link_libraries(Pathfinding ${OTHER_LINK_LIBRARIES})

# Copy DLL
add_custom_command(TARGET Pathfinding PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PATH_DIR}/lib/SFML/bin/ $<TARGET_FILE_DIR:Pathfinding>
)

if (CMAKE_VERSION VERSION_GREATER 3.8)
  set_property(TARGET Pathfinding PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET Pathfinding PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET Pathfinding PROPERTY CXX_STANDARD_REQUIRED on)