#include <SFML\Graphics.hpp>

//typ wyliczeniowy okre�laj�cy rodzaj bloczku
enum BlockType
{
	BLOCK_TYPE_UNBREAKABLE,
	BLOCK_TYPE_BREAKABLE,
};

class Block : public sf::Sprite
{
public:
	Block(sf::Vector2f position, BlockType blockType);	//konstruktor
	BlockType getBlockType();	//getter do pola blockType
private:
	BlockType blockType;
};