#pragma once
#include <SFML\Graphics.hpp>

//typ wyliczeniowy okreœlaj¹cy rodzaj bloczku
//przy tworzeniu nowego rodzaju bloczku, nale¿y tu dopisaæ jego typ
enum BlockType
{
	BLOCK_TYPE_PADDLE,
	BLOCK_TYPE_UNBREAKABLE,
	BLOCK_TYPE_BREAKABLE,
};

//block to nic innego jak klasa sprite rozszerzona o pole blockType
class Block : public sf::Sprite
{
public:
	Block(sf::Vector2i blockSize);
	BlockType getBlockType();	//getter do pola blockType
	void setBlockType(BlockType blockType);	//setter do pola blockType
	sf::Vector2i getBlockSize();
private:
	sf::Vector2i blockSize;
	BlockType blockType;
};