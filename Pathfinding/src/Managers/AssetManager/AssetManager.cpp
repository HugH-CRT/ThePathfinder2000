#include "AssetManager.h"

#include <iostream>

void AssetManager::LoadTexture(const std::string& name, const std::string& fileName)
{
	sf::Texture texture;

	if (texture.loadFromFile(fileName))
	{
		this->_textures[name] = texture;
	}
	else {
		std::cout << "Error loading texture: " << fileName << std::endl;
		exit(1);
	}
}

sf::Texture& AssetManager::GetTexture(const std::string& name)
{
	return this->_textures.at(name);
}

void AssetManager::LoadFont(const std::string& name, const std::string& fileName)
{
	if (sf::Font font; font.loadFromFile(fileName))
	{
		this->_fonts[name] = font;
	}
	else
	{
		std::cout << "Error loading font: " << fileName << std::endl;
		exit(1);
	}
}

sf::Font& AssetManager::GetFont(const std::string& name)
{
	return this->_fonts.at(name);
}