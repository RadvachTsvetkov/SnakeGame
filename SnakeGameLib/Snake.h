#ifndef __SNAKE_H_INCLUDED__
#define __SNAKE_H_INCLUDED__

class IRenderer;
class IInputReader;

#include <list>
#include <memory>
#include <string>
#include "MapValue.h"
#include "MoveDirection.h"
#include "Point2D.h"

class Snake
{
private:
	static const std::string YOUR_SCORE_IS_MESSAGE;
	static const std::string GAME_OVER_MESSAGE;
	static const int MINIMUM_MAP_WIDTH;
	static const int MINIMUM_MAP_HEIGHT;
	static const int TAIL_START_LENGTH;

	const int MAP_WIDTH;
	const int MAP_HEIGHT;
	const int SCORE_VALUE;

	bool gameOver;
	IRenderer &renderer;
	IInputReader &inputReader;
	Point2D head;
	Point2D food;
	std::unique_ptr<MapValue[]> map;
	MoveDirection direction;
	int tailLength;
	std::list<Point2D> tail;
	int score;

	void ReadInput();
	void Update();
	void Render();

	void SetHeadNewPosition();
	void SetMapValueOnPosition(int row, int col, MapValue value);
	void SetMapValueOnPosition(const Point2D &point, MapValue value); 
	MapValue GetMapValueFromPosition(int row, int col) const;
	MapValue GetMapValueFromPosition(const Point2D &point) const;
	void GenerateFood();
	void InitSnakeTail();
	void InitMapWalls();
	void VerifyMapSize() const;
public:
	void StartGame();
	Snake(IRenderer &renderer, IInputReader &inputReader, int mapWidth, int mapHeight, int scorePerFood);
};

#endif