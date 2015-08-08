#include "gameState.h"

// Tutaj nale�y doda� include'y wszystkich wykorzystywanych state'�w w grze
#include "game.h"
#include "mainMenu.h"
#include "loadingMenu.h"

//pocz�tkowe ustawienie zmiennych statycznych
int GameState::nextLevel = 1; //nast�pny level jest domy�lnie ustawiony na level pierwszy
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
			//tutaj nale�y zaimplementowa� stworzenie ka�dego dodanego state'a
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

//funkcja inicjalizuj�ca(jako parametr podaje si� wska�nik do pocz�tkowego state'a
//GameState::init(new Game())
void GameState::init(GameState* initialState, sf::RenderWindow* newWindow)
{
	window = newWindow;
	currentState = initialState;
}

//getter do currentState potrzebny, aby by�o mo�na manipulowa� na 
GameState& GameState::getCurrentState()
{
	return *currentState;
}

//sprz�tanie po ostatnim state'cie
void GameState::freeResources()
{
	if (currentState != nullptr)
		delete currentState;
}