#include "block.h"

//konstruktory
Block::Block(sf::Vector2i blockSize)
{
	this->blockSize = blockSize;
}

//setter do pola blockType
void Block::setBlockType(BlockType blockType)
{
	this->blockType = blockType;
}

//getter do pola blockType
BlockType Block::getBlockType()
{
	return blockType;
}

//getter do pola blockSize
sf::Vector2i Block::getBlockSize()
{
	return blockSize;
}