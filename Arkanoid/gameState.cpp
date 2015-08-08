#include "gameState.h"

// Tutaj nale¿y dodaæ include'y wszystkich wykorzystywanych state'ów w grze
#include "game.h"
#include "mainMenu.h"
#include "loadingMenu.h"

//pocz¹tkowe ustawienie zmiennych statycznych
int GameState::nextLevel = 1; //nastêpny level jest domyœlnie ustawiony na level pierwszy
GameStates GameState::stateID = GAME_STATE_NULL;
GameStates GameState::nextState = GAME_STATE_NULL;
GameState* GameState::currentState = nullptr;
sf::RenderWindow* GameState::window = nullptr;

void GameState::changeState()
{
	if (nextState != GAME_STATE_NULL)
	{
		if (nextState != GAME_STATE_EXIT)
		{
			delete currentState;
		}
		switch (nextState)
		{
			//tutaj nale¿y zaimplementowaæ stworzenie ka¿dego dodanego state'a
		case GAME_STATE_GAME:
			currentState = new Game(nextLevel);
			break;
		case GAME_STATE_MAIN_MENU:
			currentState = new MainMenu();
			break;
		case GAME_STATE_LOADING_MENU:
			currentState = new LoadingMenu();
			break;
		}
		stateID = nextState;
		nextState = GAME_STATE_NULL;
	}
}

void GameState::setNextState(GameStates newState)
{
	if (nextState != GAME_STATE_EXIT)
	{
		nextState = newState;
	}
}

GameStates GameState::getStateID()
{
	return stateID;
}

//funkcja inicjalizuj¹ca(jako parametr podaje siê wskaŸnik do pocz¹tkowego state'a
//GameState::init(new Game())
void GameState::init(GameState* initialState, sf::RenderWindow* newWindow)
{
	window = newWindow;
	currentState = initialState;
}

//getter do currentState potrzebny, aby by³o mo¿na manipulowaæ na 
GameState& GameState::getCurrentState()
{
	return *currentState;
}

//sprz¹tanie po ostatnim state'cie
void GameState::freeResources()
{
	if (currentState != nullptr)
		delete currentState;
}