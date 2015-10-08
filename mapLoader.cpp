#include <fstream>
#include <iostream>
#include "mapLoader.h"
#include "constants.h"
#include "rule.h"

MapLoader::MapLoader(std::string filename, sf::Texture* blocksTexture)
{
	this->blocksTexture = blocksTexture;
	
	mapFileOfLevel.open(filename);
	if (!mapFileOfLevel.is_open())
	{
		std::cout << "There isn't suitable map file" << std::endl;
		system("pause");
		exit(-1);
	}
}

MapLoader::~MapLoader()
{
	if(mapFileOfLevel.is_open())
	{
		mapFileOfLevel.close();
	}
}

void MapLoader::addRule(bool(*rule)(sf::Vector2u, sf::Vector2i) , std::vector< Block >* container, BlockType blockType)
{
	rules.push_back(Rule(rule, container, blockType));
}

void MapLoader::addRule(bool(*rule)(sf::Vector2u), std::vector< Block >* container, BlockType blockType)
{
	rules.push_back(Rule(rule, container, blockType));
}


void MapLoader::loadMap()
{
	std::vector<std::vector<sf::Vector2i> > map;
	std::vector<sf::Vector2i> newRowOfMap;
	
	std::string currentTurple;
	
	//Load values form .dat file into dynamic arrays
	if (mapFileOfLevel.is_open())
	{
		while (!mapFileOfLevel.eof())
		{
			mapFileOfLevel >> currentTurple;
			if (currentTurple[0] != 'x' && currentTurple[2] != 'x')
				newRowOfMap.push_back(sf::Vector2i(currentTurple[0] - '0', currentTurple[2] - '0'));
			else
				newRowOfMap.push_back(sf::Vector2i(-1, -1));
			
			if (mapFileOfLevel.peek() == '\n')
			{
				map.push_back(newRowOfMap);
				newRowOfMap.clear();
			}
		}
		if (!newRowOfMap.empty())
		{
			map.push_back(newRowOfMap);
			newRowOfMap.clear();
		}
	}
	
	for(std::vector<Rule>::iterator currentRule = rules.begin(); currentRule != rules.end(); currentRule++)
	{
		for (unsigned int row = 0; row < map.size(); row++)
		{
			for (unsigned int column = 0; column < map[row].size(); column++)
			{
				if (map[row][column].x != -1)
				{
					Block newBlock(sf::Vector2i(TILE_SIZE_X, TILE_SIZE_Y));
					//check if the block belongs to border
					if (currentRule->executeRule(sf::Vector2u(column, row), map[row][column]))
					{	
						newBlock.setBlockType(currentRule->getBlockType());
						newBlock.setPosition(sf::Vector2f(static_cast<float>(column * TILE_SIZE_X), static_cast<float>(row * TILE_SIZE_Y)));
						newBlock.setTexture(*blocksTexture);
						newBlock.setTextureRect(sf::IntRect(map[row][column].x * TILE_SIZE_X, map[row][column].y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y));
						currentRule->getContainer()->push_back(newBlock);
					}
				}
			}
		}
	}
}
