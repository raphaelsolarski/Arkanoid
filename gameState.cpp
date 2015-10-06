#include "gameState.h"

// Tutaj nale¿y dodaæ include'y wszystkich wykorzystywanych state'ów w grze
#include "game.h"
#include "mainMenu.h"
#include "loadingMenu.h"
#include "pauseMenu.h"
#include "levelFinishedMenu.h"
#include "defeatMenu.h"
#include "aboutMenu.h"

//pocz¹tkowe ustawienie zmiennych statycznych
int GameState::nextLevel = 1; //nastêpny level jest domyœlnie ustawiony na level pierwszy
GameStates GameState::stateID = GAME_STATE_NULL;
GameStates GameState::nextState = GAME_STATE_NULL;
GameState* GameState::currentState = nullptr;
GameState* GameState::sleepedState = nullptr;
sf::RenderWindow* GameState::window = nullptr;

void GameState::changeState()
{
	if (nextState != GAME_STATE_NULL)
	{
		if (nextState != GAME_STATE_EXIT && nextState != GAME_STATE_PAUSE_MENU)
		{
			delete currentState;
		}
		switch (nextState)
		{
			//tutaj nale¿y zaimplementowaæ stworzenie ka¿dego dodanego state'a
		case GAME_STATE_GAME:
			currentState = new Game(nextLevel);
			stateID = GAME_STATE_GAME;
			break;

		case GAME_STATE_MAIN_MENU:
			if (sleepedState != nullptr)	//sprawdzam czy nie istnieje uœpiony state(przypadek, gdy przechodzi siê do menu z menu pauzy)
			{
				delete sleepedState;
				sleepedState = nullptr;
			}
			currentState = new MainMenu();
			stateID = GAME_STATE_MAIN_MENU;
			break;

		case GAME_STATE_LOADING_MENU:
			currentState = new LoadingMenu();
			stateID = GAME_STATE_LOADING_MENU;
			break;

		case GAME_STATE_PAUSE_MENU:
			sleepedState = currentState;	//usypiam grê
			currentState = new	PauseMenu();//tworzê state menu pauzy
			stateID = GAME_STATE_PAUSE_MENU;
			break;

		case GAME_STATE_RESTUME:			//przywracam uœpion¹ grê 
			currentState = sleepedState;
			sleepedState = nullptr;
			stateID = GAME_STATE_GAME;
			break;

		case GAME_STATE_LEVEL_FINISHED_MENU:
			currentState = new LevelFinishedMenu();
			stateID = GAME_STATE_LEVEL_FINISHED_MENU;
			break;

		case GAME_STATE_DEFEAT_MENU:
			currentState = new DefeatMenu();
			stateID = GAME_STATE_DEFEAT_MENU;
			break;

		case GAME_STATE_ABOUT_MENU:
			currentState = new AboutMenu();
			stateID = GAME_STATE_ABOUT_MENU;
			break;

		case GAME_STATE_EXIT:
			stateID = GAME_STATE_EXIT;
			break;

		}
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
	//uwolnienie ostatniego state'a
	if (currentState != nullptr)
		delete currentState;

	//uwolnienie uœpionego state'a
	if (sleepedState != nullptr)
		delete sleepedState;
}