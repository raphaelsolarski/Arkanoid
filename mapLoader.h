#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "block.h"
#include "rule.h"

class MapLoader
{
public:
	MapLoader(std::string filename, sf::Texture* blocksTexture);
	~MapLoader();
	void addRule(bool(*rule)(sf::Vector2u positionOnMap, sf::Vector2i positionInTiles), std::vector<Block>* container, BlockType blockType);
	void addRule(bool(*rule)(sf::Vector2u positionOnMap), std::vector<Block>* container, BlockType blockType);
	void addRule(std::vector<Block>* container, BlockType blockType);
	void loadMap();
	
private:
	std::vector<Rule> rules;
	std::ifstream mapFileOfLevel;
	sf::Texture* blocksTexture;
};