/**
* @file c_path.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "c_path.h"

#include <filesystem>

#if DEBUG_LOG
#include <iostream>
#endif 

/**
* @fn TempDir
* @brief Retourne au format std::string le chemin de fichier temporaire.
* @return std::string 
*/
std::string C_PATH::TempDir()
{
	std::string temp_path = std::filesystem::temp_directory_path().generic_string();

#if DEBUG_LOG
	std::cout << "Temp Dir : " << temp_path << "\n";
#endif 

	return temp_path;
}

/**
* @fn CurrentDir
* @brief Retourne au format std::string le chemin de fichier actuelle. 
* @return std::string
*/
std::string C_PATH::CurrentDir()
{
	std::string current_path = std::filesystem::current_path().generic_string();

#if DEBUG_LOG
	std::cout << "Current Dir : " << current_path << "\n";
#endif 

	return current_path;
}

/**
* @fn UserDir
* @brief Retourne au format std::string le chemin de fichier de l'utilisateur
* @return std::string
*/
std::string C_PATH::UserDir()
{
	// @todo : A FINIR
	std::string user_path = std::filesystem::current_path().generic_string();
	
#if DEBUG_LOG
	std::cout << "User Dir : " << user_path << "\n";
#endif 

	return user_path;
}

/**
* @fn DocumentDir
* @brief Retourne au format std::string le chemin de fichier des documents de l'utilisateur
* @return std::string
*/
std::string C_PATH::DocumentDir()
{
	// @todo : A FINIR
	std::string document_path = std::filesystem::current_path().generic_string();

#if DEBUG_LOG
	std::cout << "Documents Dir : " << document_path << "\n";
#endif 

	return document_path;
}

/**
* @fn ProjectDir
* @brief Retourne au format std::string le chemin de fichier de l'emplacement du projet
* @return std::string
*/
std::string C_PATH::ProjectDir()
{

	// @todo : A FINIR
	std::string project_path = std::filesystem::current_path().generic_string();

#if DEBUG_LOG
	std::cout << "Project Dir : " << project_path << "\n";
#endif

	return project_path;
}
