#include <SFML\Graphics.hpp>

//typ wyliczeniowy okre�laj�cy rodzaj bloczku
//przy tworzeniu nowego rodzaju bloczku, nale�y tu dopisa� jego typ
enum BlockType
{
	BLOCK_TYPE_UNBREAKABLE,
	BLOCK_TYPE_BREAKABLE,
};

//block to nic innego jak klasa sprite rozszerzona o pole blockType
class Block : public sf::Sprite
{
public:
	Block();
	Block(sf::Vector2f position, BlockType blockType);	//konstruktor
	BlockType getBlockType();	//getter do pola blockType
private:
	BlockType blockType;
};