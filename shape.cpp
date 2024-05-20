#include "shape.h"
#include "game.h"
#include "gameConfig.h"

shape::shape(game* r_pGame, point ref)
{
	RefPoint = ref;
	pGame = r_pGame;
	fillColor = config.fillColor;
	borderColor = config.penColor;
	orientation = 0;
}

void shape::setRefPoint(point p)
{
	RefPoint = p;
}

point shape::getRefPoint() const { return RefPoint; }

void shape::move(Direction direction)
{
	movePoint(direction, RefPoint);
}

void rotateAroundPoint(point& p, const point& pivot)
{
	// Save old points for future calculation
	point ptmp = p;

	// Rotation around point formula
	// x' = -(y-ry)+rx
	// y' =  (x-rx)+ry
	p.x = -(ptmp.y - pivot.y) + pivot.x;
	p.y = ptmp.x - pivot.x + pivot.y;
}

void movePoint(Direction direction, point& RefPoint)
{
	switch (direction)
	{
	case UP:
		RefPoint.y -= config.moveStep;
		break;
	case RIGHT:
		RefPoint.x += config.moveStep;
		break;
	case DOWN:
		RefPoint.y += config.moveStep;
		break;
	case LEFT:
		RefPoint.x -= config.moveStep;
		break;
	}
}
