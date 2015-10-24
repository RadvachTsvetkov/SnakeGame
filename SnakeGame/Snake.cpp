#include <assert.h>
#include <string>
#include <Windows.h>

#include "Snake.h"
#include "IRenderer.h"
#include "IInputReader.h"

Snake::Snake(IRenderer &renderer, IInputReader &inputReader, int mapWidth, int mapHeight, int scorePerFood) : renderer(renderer), inputReader(inputReader),
	MAP_WIDTH(mapWidth), MAP_HEIGHT(mapHeight), SCORE_VALUE(scorePerFood),
	gameOver(false), direction(MoveDirection::UP), tailLength(TAIL_START_LENGTH), score(0), map(new MapValue[mapWidth * mapHeight]{}),
	head(MAP_HEIGHT / 2, MAP_WIDTH / 2), food(Point2D(0, 0))
{
	this->VerifyMapSize();
	 
	this->InitMapWalls();

	// Initialize Head
	this->SetMapValueOnPosition(head, MapValue::HEAD);

	this->InitSnakeTail();

	this->GenerateFood();
}

void Snake::StartGame()
{
	while (!gameOver)
	{
		this->ReadInput();
		this->Update();
		this->Render();

		Sleep(150);
	}

	this->renderer.RenderSingleMessage("\tGame over!");
}

void Snake::ReadInput()
{
	MoveDirection directionCandidate;
	if (this->inputReader.ReadInput(directionCandidate))
	{
		switch (directionCandidate)
		{
		case MoveDirection::UP:
			if (this->direction != MoveDirection::DOWN)
			{
				this->direction = directionCandidate;
			}
		case MoveDirection::RIGHT:
			if (this->direction != MoveDirection::LEFT)
			{
				this->direction = directionCandidate;
			}
			break;
		case MoveDirection::DOWN:
			if (this->direction != MoveDirection::UP)
			{
				this->direction = directionCandidate;
			}
			break;
		case MoveDirection::LEFT:
			if (this->direction != MoveDirection::RIGHT)
			{
				this->direction = directionCandidate;
			}
			break;
		}
	}
}

void Snake::Update()
{
	Point2D oldHead(this->head.GetRow(), this->head.GetCol());
	this->SetHeadNewPosition();

	MapValue newHeadPositionValue = this->GetMapValueFromPosition(head);
	int oldTailLength = tailLength;
	if (newHeadPositionValue == MapValue::FOOD)
	{
		this->tailLength++;
		this->GenerateFood();
		this->score += SCORE_VALUE;
	}
	else if (newHeadPositionValue != MapValue::EMPTY)
	{
		this->gameOver = true;
	}

	if (!this->gameOver)
	{
		// Set Head's new position on the map
		this->SetMapValueOnPosition(head, MapValue::HEAD);

		bool isFoodEaten = oldTailLength < this->tailLength;
		if (!isFoodEaten)
		{
			// Detach last segment and SET its position on the map to MapValue::EMPTY
			Point2D lastSegment = tail.back();
			this->tail.pop_back();
			this->SetMapValueOnPosition(lastSegment, MapValue::EMPTY);
		}

		// Attach new segment to old-head's position
		this->tail.push_front(oldHead);
		this->SetMapValueOnPosition(oldHead, MapValue::SEGMENT);
	}
}

void Snake::Render()
{
	this->renderer.Render(map, MAP_WIDTH, MAP_HEIGHT);

	std::string scoreMessage = "\tYour score is: " + std::to_string(score);
	this->renderer.RenderSingleMessage(scoreMessage);
}

void Snake::SetHeadNewPosition()
{
	switch (this->direction)
	{
	case MoveDirection::UP:
		this->head.SetPoint(this->head.GetRow() - 1, this->head.GetCol());
		break;
	case  MoveDirection::RIGHT:
		this->head.SetPoint(this->head.GetRow(), this->head.GetCol() + 1);
		break;
	case  MoveDirection::DOWN:
		this->head.SetPoint(this->head.GetRow() + 1, this->head.GetCol());
		break;
	case  MoveDirection::LEFT:
		this->head.SetPoint(this->head.GetRow(), this->head.GetCol() - 1);
		break;
	}
}

void Snake::SetMapValueOnPosition(int row, int col, MapValue value)
{
	this->map[col + row * MAP_WIDTH] = value;
}

void Snake::SetMapValueOnPosition(const Point2D &point, MapValue value)
{
	this->SetMapValueOnPosition(point.GetRow(), point.GetCol(), value);
}

MapValue Snake::GetMapValueFromPosition(int row, int col) const
{
	return this->map[col + row * MAP_WIDTH];
}

MapValue Snake::GetMapValueFromPosition(const Point2D &point) const
{
	return this->GetMapValueFromPosition(point.GetRow(), point.GetCol());
}

void Snake::GenerateFood()
{
	while (true)
	{
		int col = rand() % MAP_WIDTH;
		int row = rand() % MAP_HEIGHT;
		if (this->GetMapValueFromPosition(row, col) == MapValue::EMPTY)
		{
			this->food.SetPoint(row, col);
			this->SetMapValueOnPosition(row, col, MapValue::FOOD);
			break;
		}
	}
}

void Snake::InitSnakeTail()
{
	for (int i = 1; i <= tailLength; i++)
	{
		int newSegmentRow = head.GetRow() + i;
		int newSegmentCol = head.GetCol();

		assert(this->GetMapValueFromPosition(newSegmentRow, newSegmentCol) == MapValue::EMPTY);
		Point2D newSegment(newSegmentRow, newSegmentCol);

		this->tail.push_back(newSegment);
		this->SetMapValueOnPosition(newSegment, MapValue::SEGMENT);
	}
}

void Snake::InitMapWalls()
{
	// TOP and BOTTOM walls
	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		this->SetMapValueOnPosition(row, 0, MapValue::WALL);
		this->SetMapValueOnPosition(row, MAP_WIDTH - 1, MapValue::WALL);
	}

	// LEFT and RIGHT walls
	for (int col = 1; col < MAP_WIDTH - 1; col++)
	{
		this->SetMapValueOnPosition(0, col, MapValue::WALL);
		this->SetMapValueOnPosition(MAP_HEIGHT - 1, col, MapValue::WALL);
	}
}

void Snake::VerifyMapSize() const
{
	if (MAP_WIDTH < 10)
	{
		throw std::invalid_argument("The provided map width should be greater than or equal to 10");
	}

	// consider tail length, because tail is drawn on the height as head in the center
	if (MAP_HEIGHT < 10)
	{
		throw std::invalid_argument("The provided map height should be greater than or equal to 10");
	}
}