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
	int lives = 5;
	int level = 1;
	int score = 0;

public:
	toolbar(game* r_pGame);
	toolbarItem getItemClicked(int x);
	void set_level(int level);
	void set_lives(int lives);
	void set_score(int score);
};

