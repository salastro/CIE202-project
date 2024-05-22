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
	int level = 1;
	int lives = 5;
	int score = 0;
	int time = 0;
	
public:
	toolbar(game* r_pGame);
	toolbarItem getItemClicked(int x);
	void drawState() const;
	void setLevel(int level);
	void setLives(int lives);
	void setScore(int score);
	void setTime(int time);
	int getLevel();
	int getLives();
	int getScore();
	int getTime();
};

