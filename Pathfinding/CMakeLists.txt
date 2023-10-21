# CMakeLists PROJECT Pathfinding

project(Pathfinding)

set (PATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HEADERS
    "${PATH_DIR}/macro.h"
    "${PATH_DIR}/core/Game.h"
    "${PATH_DIR}/Managers/AssetManager/AssetManager.h"
    "${PATH_DIR}/Managers/InputManager/InputManager.h"
    "${PATH_DIR}/StateMachine/StateMachine.h"
    "${PATH_DIR}/StateMachine/State.h"
    "${PATH_DIR}/StateMachine/GameState/GameState.h"
    "${PATH_DIR}/StateMachine/MainMenu/MainMenuState.h"
    "${PATH_DIR}/StateMachine/SplashState/SplashState.h"
	"${PATH_DIR}/StateMachine/PauseState/PauseState.h"
    "${PATH_DIR}/defined.h"
       
)

set(SOURCES
   "${PATH_DIR}/main.cpp" 
   "${PATH_DIR}/core/Game.cpp"
   "${PATH_DIR}/Managers/AssetManager/AssetManager.cpp"
   "${PATH_DIR}/Managers/InputManager/InputManager.cpp"
   "${PATH_DIR}/StateMachine/StateMachine.cpp"
   "${PATH_DIR}/StateMachine/GameState/GameState.cpp"
   "${PATH_DIR}/StateMachine/SplashState/SplashState.cpp"
   "${PATH_DIR}/StateMachine/MainMenu/MainMenuState.cpp"
   	"${PATH_DIR}/StateMachine/PauseState/PauseState.cpp"

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

include_directories(
    "${PATH_DIR}"
    "${PATH_DIR}/core"
    "${PATH_DIR}/lib"
    "${PATH_DIR}/Managers"
    "${PATH_DIR}/StateMachine"
)

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
	$<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${HEADER_DIR}>
	$<BUILD_INTERFACE:${C_PATH_HEADER}>
        "${PATH_DIR}/lib/SFML/include"
        "${PATH_DIR}/lib/ImGUI"
        "${PATH_DIR}/lib/ImGUI/backends"
        "${PATH_DIR}/lib/ImGUI-SFML"
)

target_link_directories(${PROJECT_NAME}
    PUBLIC
	"${PATH_DIR}/lib/SFML/lib"  
)

# Remove GLOB_RECURSE
file(GLOB_RECURSE OTHER_LINK_LIBRARIES  ${PATH_DIR}/lib/SFML/lib/*.lib)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
	${OPENGL_gl_LIBRARY}
	${OTHER_LINK_LIBRARIES}
    PRIVATE
	CustomPath
)

# Copy DLL
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PATH_DIR}/lib/SFML/bin/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

if (CMAKE_VERSION VERSION_GREATER 3.8)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED on)