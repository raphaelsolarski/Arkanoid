#include "rule.h"

Rule::Rule(bool(*rule)(sf::Vector2u positionOnMap, sf::Vector2i positionInTiles), std::vector<Block>* container, BlockType blockType)
{
	this->ruleFull = rule;
	this->ruleSimple = NULL;
	this->container = container;
	this->blockType = blockType;
}

Rule::Rule(bool(*rule)(sf::Vector2u positionOnMap), std::vector< Block >* container, BlockType blockType)
{
	this->ruleFull = NULL;
	this->ruleSimple = rule;
	this->container = container;
	this->blockType = blockType;
}

bool Rule::executeRule(sf::Vector2u positionOnMap, sf::Vector2i positionInTiles)
{
	if(ruleFull != NULL)
	{
		return ruleFull(positionOnMap, positionInTiles);
	}
	else
	{
		return ruleSimple(positionOnMap);
	}
	
}

bool Rule::executeRule(sf::Vector2u positionOnMap)
{
	if(ruleSimple != NULL)
	{
		return ruleSimple(positionOnMap);
	}
	else
	{
		return ruleFull(positionOnMap, sf::Vector2i(-1, -1));
	}
}

BlockType Rule::getBlockType()
{
	return blockType;
}

std::vector<Block>* Rule::getContainer()
{
	return container;
}

