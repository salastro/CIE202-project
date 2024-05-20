#include "toolbar.h"
#include "game.h"
//#include "grid.h"


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(game* pG)
{	
	height = config.toolBarHeight;
	width = config.windWidth;
	this->pGame = pG;
	window* pWind = pGame->getWind();
	
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each toolbar item
	// toolbarItemImages[ITM_SIGN] = "images\\ToolbarItems\\toolbar_sign.jpg";
	toolbarItemImages[ITM_CAR] = "images\\ToolbarItems\\car.jpg";
	toolbarItemImages[ITM_HOUSE] = "images\\ToolbarItems\\house.jpg";
	toolbarItemImages[ITM_TREE] = "images\\ToolbarItems\\tree.jpg";
	toolbarItemImages[ITM_PLANE] = "images\\ToolbarItems\\airplane.jpg";
	toolbarItemImages[ITM_ICECREAM] = "images\\ToolbarItems\\icecream.jpg";
	toolbarItemImages[ITM_CLOUD] = "images\\ToolbarItems\\cloud.jpg";
	toolbarItemImages[ITM_Rotate] = "images\\ToolbarItems\\toolbar_Rotate.jpg";
	toolbarItemImages[ITM_Plus] = "images\\ToolbarItems\\toolbar_plus.jpg";
	toolbarItemImages[ITM_Minus] = "images\\ToolbarItems\\toolbar_Minus.jpg";
	toolbarItemImages[ITM_Refresh] = "images\\ToolbarItems\\toolbar_Refresh.jpeg";
	toolbarItemImages[ITM_Hint] = "images\\ToolbarItems\\toolbar_Hint.jpg";
	toolbarItemImages[ITM_Delete] = "images\\ToolbarItems\\toolbar_Delete.jpg";
	toolbarItemImages[ITM_GameLevel] = "images\\ToolbarItems\\toolbar_Level.jpg";
	toolbarItemImages[ITM_Save] = "images\\ToolbarItems\\toolbar_Save.jpg";
	toolbarItemImages[ITM_Load] = "images\\ToolbarItems\\toolbar_Load.jpg";
	toolbarItemImages[ITM_EXIT] = "images\\ToolbarItems\\toolbar_Exit.jpg";


	//TODO: Prepare image for each toolbar item and add it to the list

	//Draw toolbar item one image at a time
	for (int i = 0; i < ITM_CNT; i++)
		pWind->DrawImage(toolbarItemImages[i], i * config.toolbarItemWidth, 0, config.toolbarItemWidth, height);
	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.windWidth - 300, config.toolBarHeight / 4, "Lives: " + to_string(lives));
	pWind->DrawString(config.windWidth - 200, config.toolBarHeight / 4, "Time: " + to_string(level));
	pWind->DrawString(config.windWidth - 100, config.toolBarHeight / 4, "Score: " + to_string(score));

	//Draw a line under the toolbar
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, height,width , height);
}



//handles clicks on toolbar icons, returns ITM_CNT if the click is not inside the toolbar
toolbarItem toolbar::getItemClicked(int x)
{
	
	if (x > ITM_CNT * config.toolbarItemWidth)	//click outside toolbar boundaries
		return ITM_CNT;
	
	
	//Check whick toolbar item was clicked
	//==> This assumes that toolbar items are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

	return (toolbarItem)(x / config.toolbarItemWidth);

}

void toolbar::set_level(int level)
{
	this->level = level;
}

void toolbar::set_lives(int lives)
{
	this->lives = lives;
}

void toolbar::set_score(int score)
{
	this->score = score;
}

