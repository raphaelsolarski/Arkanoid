#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "block.h"

enum RuleType
{
	RULE_TYPE_SIMPLE,
	RULE_TYPE_FULL,
	RULE_TYPE_ALWAYS_TRUE
};

class Rule
{
public:
	Rule(bool(*rule)(sf::Vector2u positionOnMap, sf::Vector2i positionInTiles), std::vector<Block>* container, BlockType blockType);
	Rule(bool(*rule)(sf::Vector2u positionOnMap), std::vector<Block>* container, BlockType blockType);
	Rule(std::vector<Block>* container, BlockType blockType);
	
	bool executeRule(sf::Vector2u positionOnMap, sf::Vector2i positionInTiles);
	bool executeRule(sf::Vector2u positionOnMap);
	BlockType getBlockType();
	std::vector< Block >* getContainer();
	
private:
	bool(*ruleFull)(sf::Vector2u positionOnMap, sf::Vector2i positionInTiles);
	bool(*ruleSimple)(sf::Vector2u positionOnMap);
	std::vector<Block>* container;
	BlockType blockType;
	RuleType ruleType;
};