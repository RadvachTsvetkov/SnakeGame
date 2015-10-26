#ifndef __CONSOLEINPUTREADER_H_INCLUDED__
#define __CONSOLEINPUTREADER_H_INCLUDED__

#include <unordered_map>
#include "IInputReader.h"

class ConsoleInputReader : public IInputReader
{
private:
	MoveDirection newDirection;
	std::unordered_map<char, MoveDirection> directionByCharInput;
public:
	ConsoleInputReader(char up, char right, char down, char left);

	bool ConsoleInputReader::ReadInput(MoveDirection &directionCandidate);
};

#endif