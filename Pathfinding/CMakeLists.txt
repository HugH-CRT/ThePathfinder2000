# CMakeLists PROJECT Pathfinding

project(Pathfinding)

set (PATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SFML_HEADER ${LIB_DIR}/SFML/include)
set(ImGUI_HEADER ${LIB_DIR}/ImGUI)
set(ImGUI_SFML_HEADER ${LIB_DIR}/ImGUI-SFML)

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
    "${PATH_DIR}/UI/UIElements/UIElement.h"
    "${PATH_DIR}/UI/UIElements/UI_Button/UIButton.h"
    "${PATH_DIR}/UI/UIElements/UI_CheckBox/UICheckbox.h"
    "${PATH_DIR}/UI/UIElements/UI_Image/UIImage.h"
    "${PATH_DIR}/UI/UIElements/UI_Text/UIText.h"
    "${PATH_DIR}/UI/UIElements/UI_TextField/UITextField.h"
    "${PATH_DIR}/UI/Events/UIEvent.h"
    "${PATH_DIR}/UI/Events/UIEventListener.h"
    "${PATH_DIR}/UI/Widget/UIWidget.h"
    "${PATH_DIR}/UI/Widget/GameWidget/GameWidget.h"
    "${PATH_DIR}/UI/Widget/MainMenuWidget/MainMenuWidget.h"
    "${PATH_DIR}/UI/Widget/PauseWidget/PauseWidget.h"
    "${PATH_DIR}/UI/Widget/SplashWidget/SplashWidget.h"
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
    "${PATH_DIR}/UI/UIElements/UIElement.cpp"
    "${PATH_DIR}/UI/UIElements/UI_Button/UIButton.cpp"
    "${PATH_DIR}/UI/UIElements/UI_CheckBox/UICheckbox.cpp"
    "${PATH_DIR}/UI/UIElements/UI_Image/UIImage.cpp"
    "${PATH_DIR}/UI/UIElements/UI_Text/UIText.cpp"
    "${PATH_DIR}/UI/UIElements/UI_TextField/UITextField.cpp"
    "${PATH_DIR}/UI/Events/UIEventListener.cpp"
    "${PATH_DIR}/UI/Widget/UIWidget.cpp"
    "${PATH_DIR}/UI/Widget/GameWidget/GameWidget.cpp"
    "${PATH_DIR}/UI/Widget/MainMenuWidget/MainMenuWidget.cpp"
    "${PATH_DIR}/UI/Widget/PauseWidget/PauseWidget.cpp"
    "${PATH_DIR}/UI/Widget/SplashWidget/SplashWidget.cpp"

   # LIB 
   #"${PATH_DIR}/lib/ImGUI/imgui.cpp"
   #"${PATH_DIR}/lib/ImGUI/imgui_tables.cpp"
   #"${PATH_DIR}/lib/ImGUI/imgui_widgets.cpp"
   #"${PATH_DIR}/lib/ImGUI/imgui_draw.cpp"
   # Pour demo 
   #"${PATH_DIR}/lib/ImGUI/imgui_demo.cpp"
   # Link src : ImGui to SFML
   #"${PATH_DIR}/lib/ImGUI-SFML/imgui-SFML.cpp"
)

include_directories(
    "${PATH_DIR}"
    "${PATH_DIR}/core"
    "${PATH_DIR}/Managers"
    "${PATH_DIR}/StateMachine"
    "${PATH_DIR}/UI"
    ${SFML_HEADER}
    ${ImGUI_HEADER}
    ${ImGUI_SFML_HEADER}
)

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${HEADER_DIR}>
	$<BUILD_INTERFACE:${LOGGER_HEADER}>
	# $<BUILD_INTERFACE:${SFML_HEADER}>
	# $<BUILD_INTERFACE:${ImGUI_HEADER}>
	# $<BUILD_INTERFACE:${ImGUI_SFML_HEADER}>
    ${SFML_HEADER}
    ${ImGUI_HEADER}
    ${ImGUI_SFML_HEADER}
)

target_link_directories(${PROJECT_NAME}
    PUBLIC
	"${PATH_DIR}/SFML/lib"  
)

# Remove GLOB_RECURSE
file(GLOB_RECURSE OTHER_LINK_LIBRARIES  ${LIB_DIR}/SFML/lib/*.lib)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
	${OPENGL_gl_LIBRARY}
	${OTHER_LINK_LIBRARIES}
    PRIVATE
	Logger
)

# Copy DLL
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${LIB_DIR}/SFML/bin/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

if (CMAKE_VERSION VERSION_GREATER 3.8)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED on)