#pragma once
#include <SFML\Graphics.hpp>

//typ okreœlaj¹cy wszystkie stany gry
//jeœli dodajesz nowy stan to musisz go tutaj uwzglêdniæ
enum GameStates
{
	GAME_STATE_NULL,
	GAME_STATE_RESTUME,		//state, który ka¿e przywróciæ uœpion¹ grê
	GAME_STATE_MAIN_MENU,
	GAME_STATE_LOADING_MENU,
	GAME_STATE_PAUSE_MENU,
	GAME_STATE_GAME,
	GAME_STATE_EXIT
};

//g³ówna klasa GameState po której bêdzie dziedziczyæ ka¿da klasa state'a
class GameState
{
public:
	static void freeResources();
	static void changeState();
	static void setNextState(GameStates newState);
	static void init(GameState* initialState, sf::RenderWindow *window);
	static GameStates getStateID();
	static GameState& getCurrentState();
	virtual void handleEvents() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~GameState(){};

protected:
	static int nextLevel;		//numer aktualnego poziomu
	static GameStates stateID;
	static GameStates nextState;
	static GameState *currentState;
	static GameState *sleepedState;	//wskaŸnik do uœpionego state'a (potrzebne dla menu pauzy);
	static sf::RenderWindow * window;	//wskaŸnik do okna gry(wspólnego dla wszystkich state'ów)
};