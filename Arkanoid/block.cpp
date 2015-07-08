#include "block.h"

//konstruktory
Block::Block()
{

}

Block::Block(sf::Vector2f position, BlockType blockType)
{
	sf::Sprite::setPosition(position);
	this->blockType = blockType;
}

//getter do pola blockType
BlockType Block::getBlockType()
{
	return blockType;
}