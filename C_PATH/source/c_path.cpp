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