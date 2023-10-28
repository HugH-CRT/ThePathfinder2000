/**
* @file AssetManager.h
*
* @brief Manage the assets of the game
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

/**
* @class AssetManager
* @brief 
*/
class AssetManager
{
	
public: 
	AssetManager() {}
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;
	~AssetManager() {}

	void LoadTexture(const std::string& name, const std::string& fileName);
	sf::Texture& GetTexture(const std::string& name);

	void LoadFont(const std::string& name, const std::string& fileName);
	sf::Font& GetFont(const std::string& name);

private: 
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
};

#endif /* _ASSET_MANAGER_H */