#include "AssetManager.h"

#include <iostream>

/*
 * Brief : Load a texture from a file
 * @param name : name of the texture
 * @param fileName : path of the file
 *
 *  Exit the program if the file is not found
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
		std::cout << "Error loading texture: " << fileName << std::endl;
		exit(1); // @Todo : throw an exception
	}
}

/*
 * Brief : Get a texture
 * @param name : name of the texture
 *
 * Exit the program if the texture is not found
 */

sf::Texture& AssetManager::GetTexture(const std::string& name)
{
	if (_textures.find(name) == _textures.end())
	{
		std::cout << "Error texture not found: " << name << std::endl;
		exit(1); // @Todo : throw an exception
	}
	
	return _textures.at(name);
}

/*
 * Brief : Load a font from a file
 * @param name : name of the font
 * @param fileName : path of the file
 *
 * Exit the program if the file is not found
 */
void AssetManager::LoadFont(const std::string& name, const std::string& fileName)
{
	if (sf::Font font; font.loadFromFile(fileName))
	{
		_fonts[name] = font;
	}
	else
	{
		std::cout << "Error loading font: " << fileName << std::endl;
		exit(1); // @Todo : throw an exception
	}
}

/*
 * Brief : Get a font from a file
 * @param name : name of the font
 *
 * Exit the program if the font is not found
 */
sf::Font& AssetManager::GetFont(const std::string& name)
{
	if (_fonts.find(name) == _fonts.end())
	{
		std::cout << "Error font not found: " << name << std::endl;
		exit(1); // @Todo : throw an exception
	}
	
	return _fonts.at(name);
}