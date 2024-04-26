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
	toolbarItemImages[ITM_SIGN] = "images\\toolbarItems\\toolbar_sign.jpg";
	toolbarItemImages[ITM_Rotate] = "images\\toolbarItems\\toolbar_Rotate.jpg";
	toolbarItemImages[ITM_Plus] = "images\\toolbarItems\\toolbar_plus.jpg";
	toolbarItemImages[ITM_Minus] = "images\\toolbarItems\\toolbar_Minus.jpg";
	toolbarItemImages[ITM_Refresh] = "images\\toolbarItems\\toolbar_Refresh.jpeg";
	toolbarItemImages[ITM_Hint] = "images\\toolbarItems\\toolbar_Hint.jpg";
	toolbarItemImages[ITM_Delete] = "images\\toolbarItems\\toolbar_Delete.jpg";
	toolbarItemImages[ITM_GameLevel] = "images\\toolbarItems\\toolbar_Level.jpg";
	toolbarItemImages[ITM_Save] = "images\\toolbarItems\\toolbar_Save.jpg";
	toolbarItemImages[ITM_Load] = "images\\toolbarItems\\toolbar_Load.jpg";
	toolbarItemImages[ITM_EXIT] = "images\\toolbarItems\\toolbar_Exit.jpg";


	//TODO: Prepare image for each toolbar item and add it to the list

	//Draw toolbar item one image at a time
	for (int i = 0; i < ITM_CNT; i++)
		pWind->DrawImage(toolbarItemImages[i], i * config.toolbarItemWidth, 0, config.toolbarItemWidth, height);
	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.windWidth - 350, config.statusBarHeight / 2, "Lives: " + to_string(lives));
	pWind->DrawString(config.windWidth - 250, config.statusBarHeight / 2, "time: " + to_string(level));
	pWind->DrawString(config.windWidth - 150, config.statusBarHeight / 2, "score: " + to_string(score));

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

void toolbar::set_level()
{
	level = 0;
}

void toolbar::set_lives()
{
	lives = 0;

}

void toolbar::set_score()
{
	score = 0;
}

