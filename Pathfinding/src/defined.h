/**
* @file defined.h
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/

#ifndef DEFINED_H
#define DEFINED_H

#include <filesystem>

/// ********************************** RESSOURCES PATH ********************************** ///

#define SRC_PATH std::filesystem::current_path().generic_string()
#define RSC_PATH(path) SRC_PATH + "/../../Pathfinding/rsc/" + path

#define FONT RSC_PATH("Roboto-Black.ttf")

#define SPLASH_SCENE_BACKGROUND_FILEPATH RSC_PATH("BackgroundSplashScene.png")

#define MAIN_MENU_BACKGROUND_FILEPATH RSC_PATH("BackgroundMainMenu.png")
#define MAIN_MENU_TITLE_PATH RSC_PATH("PathfinderLogo.png")
#define MAIN_MENU_PLAY_BUTTON RSC_PATH("PlayButton.png")
#define MAIN_MENU_PLAY_BUTTON_OUTER RSC_PATH("CloseButtonLogo.png")

#define GAME_BACKGROUND_FILEPATH RSC_PATH("BackgroundGame.png")
#define PAUSE_BUTTON RSC_PATH("PauseButton.png")

#define PAUSE_BACKGROUND_FILEPATH RSC_PATH("BackgroundPause.png")
#define RESUME_BUTTON RSC_PATH("ResumeButton.png")
#define HOME_BUTTON RSC_PATH("HomeButton.png")

#define START_POINT RSC_PATH("StartPoint.png")
#define END_POINT RSC_PATH("EndPoint.png")
#define WALL RSC_PATH("Wall.png")
#define PATH RSC_PATH("Path.png")
#define EMPTY_TILE RSC_PATH("EmptyTile.png")
#define CHECKPOINT RSC_PATH("CheckPoint.png")
#define PORTAL RSC_PATH("Portal.png")

#define CHECK_BOX_CHECKED RSC_PATH("CheckBoxChecked.png")
#define CHECK_BOX_UNCHECKED RSC_PATH("CheckBoxUnchecked.png")

#define FORWARD_ARROW RSC_PATH("ForwardArrow.png")
#define BACKWARD_ARROW RSC_PATH("BackwardArrow.png")

#define CLEAR_BUTTON RSC_PATH("ClearButton.png")
#define CLEAR_PATH_BUTTON RSC_PATH("ClearPathButton.png")

/// ********************************** PARAMETRES ********************************** ///

#define TITLE_WINDOW "Pathfinder2000"

#define NB_LINES 15
#define NB_COLUMNS 15

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define SPLASH_STATE_SHOW_TIME 3.0

#endif /* DEFINED_H */