#include <conio.h>
#include "ConsoleInputReader.h"

ConsoleInputReader::ConsoleInputReader(char up, char right, char down, char left)
{
	this->directionByCharInput[up] = MoveDirection::UP;
	this->directionByCharInput[right] = MoveDirection::RIGHT;
	this->directionByCharInput[down] = MoveDirection::DOWN;
	this->directionByCharInput[left] = MoveDirection::LEFT;
}

bool ConsoleInputReader::ReadInput(MoveDirection &directionCandidate)
{
	if (_kbhit())
	{
		char input = _getch();
		if (this->directionByCharInput.find(input) != this->directionByCharInput.end())
		{
			// Key exists.
			directionCandidate = this->directionByCharInput[input];
			return true;
		}
	}

	return false;
}