#include "grid.h"
#include "game.h"
#include "gameConfig.h"


grid::grid(point r_uprleft, int wdth, int hght, game* pG)
{
	uprLeft = r_uprleft;
	height = hght;
	width = wdth;
	pGame = pG;
	rows = height / config.gridSpacing;
	cols = width / config.gridSpacing;
	shapeCount = 0;

	for (int i = 0; i < MaxShapeCount; i++)
		shapeList[i] = nullptr;

	activeShape = nullptr;
}

grid::~grid()
{
	for (int i = 0; i < shapeCount; i++)
		delete shapeList[i];
}

void grid::draw() const
{
	clearGridArea();
	window* pWind = pGame->getWind();

	pWind->SetPen(config.gridDotsColor, 1);
	pWind->SetBrush(config.gridDotsColor);

	//draw dots showing the grid reference points
	for (int r = 1; r < rows; r++)
		for (int c = 0; c < cols; c++)
			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
	//pWind->DrawPixel(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y);

//Draw ALL shapes
	for (int i = 0; i < shapeCount; i++)
		if (shapeList[i])
			shapeList[i]->draw();	//draw each shape

	//Draw the active shape
	if (activeShape)
		activeShape->draw();
}

void grid::clearGridArea() const
{
	window* pWind = pGame->getWind();
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(uprLeft.x, uprLeft.y, uprLeft.x + width, uprLeft.y + height);
}

//Adds a shape to the randomly created shapes list.
bool grid::addShape(shape* newShape)
{
	//TODO:
	// 1- Check that the shape can be drawn witout being clipped by grid boundaries
	if (shapeCount > MaxShapeCount)
		return false;
	shapeList[shapeCount++] = newShape;
	return true;
}

shape* grid::getActiveShape() const
{
	return activeShape;
}

void grid::setActiveShape(shape* actShape)
{
	activeShape = actShape;
}

bool grid::matchShape() {
	bool isSameOrientation;
	bool isSameRefPoint;
	bool isSameType;
	bool isSameSize;
	for (int i = 0; i < shapeCount; i++)
	{
		shape* currentShape = shapeList[i];
		if (currentShape && activeShape)
		{
			isSameOrientation = (currentShape->getOrientation() % 4) == (activeShape->getOrientation() % 4);
			isSameRefPoint =
				(currentShape->getRefPoint().x == activeShape->getRefPoint().x)
				&&
				(currentShape->getRefPoint().y == activeShape->getRefPoint().y);
			isSameType = currentShape->getType() == activeShape->getType();
			isSameSize = currentShape->getSize() == activeShape->getSize();
			if (isSameRefPoint && isSameType && isSameOrientation && isSameSize)
			{
				delete shapeList[i];
				shapeList[i] = nullptr;
				deleteShape();
				return true;
			}
		}
	}
	return false;
}

void grid::deleteShape()
{
	if (activeShape)
	{
		delete activeShape;
		activeShape = nullptr;
	}
}

int grid::getShapeCount() const
{
	return shapeCount; 
}

shape** grid::getShapeList()
{
	return shapeList;
}

void grid::clearGrid()
{
	for (int i = 0; i < shapeCount; i++)
	{
		setActiveShape(shapeList[i]);
		deleteShape();
		shapeList[i] = nullptr;
	}
		
	
}