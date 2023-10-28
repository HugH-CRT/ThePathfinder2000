/**
* @file AssetManager.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "AssetManager.h"

#include "logger.h"

/**
* @fn LoadTexture
* @brief Load a texture from a file
* @param name : name of the texture
* @param fileName : path of the file
*
* @details Exit the program if the file is not found
*/
void AssetManager::LoadTexture(const std::string& name, const std::string& fileName)
{
	sf::Texture texture;

	if (texture.loadFromFile(fileName))
	{
		_textures[name] = texture;
	}
	else
	{
		Logger::error("Error loading texture: " + fileName);
		exit(1); // @Todo : throw an exception
	}
}

/**
* @fn GetTexture
* @brief Get a texture
* @param name : name of the texture
*
* @details Exit the program if the texture is not found
*/
sf::Texture& AssetManager::GetTexture(const std::string& name)
{
	if (_textures.find(name) == _textures.end())
	{
		Logger::error("Error texture not found: " + name);
		exit(1); // @Todo : throw an exception
	}
	
	return _textures.at(name);
}

/**
* @fn LoadFont
* @brief Load a font from a file
* @param name : name of the font
* @param fileName : path of the file
*
* @details Exit the program if the file is not found
*/
void AssetManager::LoadFont(const std::string& name, const std::string& fileName)
{
	if (sf::Font font; font.loadFromFile(fileName))
	{
		_fonts[name] = font;
	}
	else
	{
		Logger::error("Error loading font: " + fileName);
		exit(1); // @Todo : throw an exception
	}
}

/**
* @fn GetFont
* @brief Get a font from a file
* @param name : name of the font
*
* @details Exit the program if the font is not found
*/
sf::Font& AssetManager::GetFont(const std::string& name)
{
	if (_fonts.find(name) == _fonts.end())
	{
		Logger::error("Error font not found: " + name);
		exit(1); // @Todo : throw an exception
	}
	
	return _fonts.at(name);
}