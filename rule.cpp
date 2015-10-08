#include "rule.h"
#include <iostream>

Rule::Rule(bool(*rule)(sf::Vector2u positionOnMap, sf::Vector2i positionInTiles), std::vector<Block>* container, BlockType blockType)
{
	this->ruleFull = rule;
	ruleType = RULE_TYPE_FULL;
	this->container = container;
	this->blockType = blockType;
}

Rule::Rule(bool(*rule)(sf::Vector2u positionOnMap), std::vector< Block >* container, BlockType blockType)
{
	ruleType = RULE_TYPE_SIMPLE;
	this->ruleSimple = rule;
	this->container = container;
	this->blockType = blockType;
}

Rule::Rule(std::vector< Block >* container, BlockType blockType)
{
	ruleType = RULE_TYPE_ALWAYS_TRUE;
	this->blockType = blockType;
	this->container = container;
}


bool Rule::executeRule(sf::Vector2u positionOnMap, sf::Vector2i positionInTiles)
{
	switch(ruleType)
	{
		case RULE_TYPE_FULL:
			return ruleFull(positionOnMap, positionInTiles);
		
		case RULE_TYPE_SIMPLE:
			return ruleSimple(positionOnMap);
			
		case RULE_TYPE_ALWAYS_TRUE:
			return true;
	}
	return false;
}

bool Rule::executeRule(sf::Vector2u positionOnMap)
{
	return executeRule(positionOnMap, sf::Vector2i(-1, -1));
}

BlockType Rule::getBlockType()
{
	return blockType;
}

std::vector<Block>* Rule::getContainer()
{
	return container;
}

