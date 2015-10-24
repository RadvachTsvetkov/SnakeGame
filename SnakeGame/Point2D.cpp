#include "Point2D.h"

Point2D::Point2D(int row = 0, int col = 0)
	:row(row), col(col)
{
}

void Point2D::SetPoint(int row, int col)
{
	this->row = row;
	this->col = col;
}

void Point2D::SetPoint(const Point2D &point)
{
	this->SetPoint(point.GetRow(), point.GetCol());
}

int Point2D::GetRow() const
{
	return this->row;
}

int Point2D::GetCol() const
{
	return this->col;
}