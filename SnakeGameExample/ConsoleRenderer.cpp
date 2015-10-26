#include <iostream>
#include <string>
#include "ConsoleRenderer.h"

void ConsoleRenderer::Render(const std::unique_ptr<MapValue[]> &map, int mapWidth, int mapHeight)
{
	system("cls");

	for (int row = 0; row < mapHeight; row++)
	{
		for (int col = 0; col < mapWidth; col++)
		{
			MapValue currentValue = this->GetMapValueFromPosition(map, mapWidth, row, col);
			char currentChar = this->GetMapChar(currentValue);
			std::cout << currentChar;
		}

		std::cout << std::endl;
	}
}

void ConsoleRenderer::RenderSingleMessage(const std::string &msg)
{
	std::cout << msg << std::endl;
}

MapValue ConsoleRenderer::GetMapValueFromPosition(const std::unique_ptr<MapValue[]> &map, int mapWidth, int row, int col)
{
	return map[col + row * mapWidth];
}

char ConsoleRenderer::GetMapChar(MapValue value)
{
	switch (value)
	{
	case MapValue::HEAD:
		return '@';
	case MapValue::SEGMENT:
		return 'o';
	case MapValue::WALL:
		return '#';
	case MapValue::FOOD:
		return 'F';
	default: // MapValue::EMPTY
		return ' ';
	}
}

