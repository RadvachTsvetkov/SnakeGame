#include <exception>
#include <iostream>

#include "Snake.h"
#include "ConsoleRenderer.h"
#include "ConsoleInputReader.h"

int main()
{
	int mapWidth = 25;
	int mapHeight = 15;
	int scoreValue = 10;

	ConsoleRenderer consoleRenderer;
	ConsoleInputReader consoleInputReader('w', 'd', 's', 'a');
	
	try
	{
		Snake snake(consoleRenderer, consoleInputReader, mapWidth, mapHeight, scoreValue);
		snake.StartGame();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}