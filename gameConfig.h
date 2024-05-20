#pragma once
#include "CMUgraphicsLib/CMUgraphics.h"


//The folowing struct contains all game configurations
// (MAY be loaded from a configuration file later)
__declspec(selectany) //This line to prevent "redefinition error"
struct
{
	int	windWidth = 1200, windHeight = 600,	//Window width and height
		wx = 5, wy = 5,			//Window starting coordinates

		//The window is divded into 3 areas: toolbar, Working area, and statusbar
		toolBarHeight = 60,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		toolbarItemWidth = 55,			//Width of each icon in toolbar
		statusBarHeight = 50;	//Status Bar Height

	int remainingHeight = windHeight - toolBarHeight - statusBarHeight;

	int gridHeight = int(remainingHeight * (2 / 3.0)); 		//The grid is where bricks can be drawn

	//Default colors
	color	penColor = RED,			//color used to draw borders/write messages
		fillColor = RED,			//shapes fill color (Default)
		bkGrndColor = LAVENDER,		//Screen Background color
		statusBarColor = LIGHTSEAGREEN;	//background color of the status
	int penWidth = 3;			//width of the pen that draws shapes


	color gridDotsColor = RED;
	int gridSpacing = 30;	//spacing between grid points

	////// Configuration for the composite shapes //////
	// default Ref Point for any newly created shape 
	int RefX = windWidth / 2;
	int RefY = windHeight / 2;

	////-----  Sign Shape Confoguration ---------////
	// For the Sign shape, define width and height of both rectangles
	struct {
		int baseWdth = 20, baseHeight = 80;
		int topWdth = 100, topHeight = 50;
	}sighShape;

	struct {
		int radius = 50;
	}cloudShape;

	struct {
		int baseWidth = 100, baseHeight = 50;
		int roofWidth = 100, roofHeight = 50;
	}houseShape;

	struct {
		int trunkHeight = 100, trunkWidth = 20;
		int crownRad = 35;
	}treeShape;

	struct {
		int scoopRad = 25;
		int coneHeight = 100;
	}icecreamShape;

	struct {
		int bodyHeight = 150, bodyWidth = 30;
		int wingHeight = 40, wingWidth = 100;
		int tailHeight = 12, tailWidth = 12;
	}planeShape;

	struct {
		int bodyHeight = 50, bodyWidth = 100;
		int headHeight = 25, headWidth = 50;
		int wheelRad = 15;
	}carShape;

}config;


enum toolbarItem //The items of the  toolbar (you should add more items)
{
	//Note: Items are ordered here as they appear in the toolbar
	//If you want to change the toolbar items order, just change the order here
	// ITM_SIGN,		//Sign shape item
	ITM_CAR,
	ITM_HOUSE,
	ITM_TREE,
	ITM_PLANE,
	ITM_ICECREAM,
	ITM_CLOUD,

	ITM_Rotate,
	ITM_Plus,
	ITM_Minus,
	ITM_Refresh,
	ITM_Hint,
	ITM_Delete,
	ITM_GameLevel,
	ITM_Save,
	ITM_Load,
	ITM_EXIT,

	ITM_CNT		//no. of toolbar items ==> This should be the last line in this enum

};



