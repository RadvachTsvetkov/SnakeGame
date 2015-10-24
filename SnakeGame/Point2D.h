#ifndef __POINT2D_H_INCLUDED__
#define __POINT2D_H_INCLUDED__

class Point2D
{
private:
	int row;
	int col;
public:
	Point2D(int row, int col);

	void SetPoint(int row, int col);
	void SetPoint(const Point2D &point);

	int GetRow() const;
	int GetCol() const;
};

#endif