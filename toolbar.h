#pragma once
#include "gameConfig.h"
////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
class game;
class toolbar
{

private:
	int height, width;	
	string toolbarItemImages[ITM_CNT]; //array to hold paths to images of diffrent items in the toolbar
	game* pGame;
	int level;
	int lives;
	int score;

public:
	toolbar(game* r_pGame);
	toolbarItem getItemClicked(int x);
	void drawState() const;
	void setLevel(int level);
	void setLives(int lives);
	void setScore(int score);
	int getLevel();
	int getLives();
	int getScore();
};

