CC=g++
CFLAGS=-c -Wall -Wextra -Wpedantic -std=c++11
LFLAGS=-Wall -Wextra -Wpedantic
LLIB=-lsfml-window -lsfml-graphics -lsfml-system
ALLOBJ=aboutMenu.o ball.o block.o defeatMenu.o game.o gameState.o levelFinishedMenu.o loadingMenu.o main.o mainMenu.o pauseMenu.o

ALL: $(ALLOBJ)
	$(CC) $(LFLAGS) -o Arkanoid $(ALLOBJ) $(LLIB)

aboutMenu.o: aboutMenu.cpp
	$(CC) $(CFLAGS) -o aboutMenu.o aboutMenu.cpp

ball.o: ball.cpp
	$(CC) $(CFLAGS) -o ball.o ball.cpp

block.o: block.cpp
	$(CC) $(CFLAGS) -o block.o block.cpp

defeatMenu.o: defeatMenu.cpp
	$(CC) $(CFLAGS) -o defeatMenu.o defeatMenu.cpp

game.o: game.cpp
	$(CC) $(CFLAGS) -o game.o game.cpp

gameState.o: gameState.cpp
	$(CC) $(CFLAGS) -o gameState.o gameState.cpp

levelFinishedMenu.o: levelFinishedMenu.cpp
	$(CC) $(CFLAGS) -o levelFinishedMenu.o levelFinishedMenu.cpp

loadingMenu.p: loadingMenu.cpp
	$(CC) $(CFLAGS) -o loadingMenu.o loadingMenu.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o main.cpp

mainMenu.o: mainMenu.cpp
	$(CC) $(CFLAGS) -o mainMenu.o mainMenu.cpp

pauseMenu.o: pauseMenu.cpp
	$(CC) $(CFLAGS) -o pauseMenu.o pauseMenu.cpp
