#ifndef __IINPUTREADER_H_INCLUDED__
#define __IINPUTREADER_H_INCLUDED__

#include "MoveDirection.h"

class IInputReader
{
public:
	virtual bool ReadInput(MoveDirection &directionCandidate) = 0;
};

#endif