/**
 * @file AssetManager.h
 *
 * @brief Manage the assets of the game
 *
 * @author yoan.laurain@ynov.com
 *
 */

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

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