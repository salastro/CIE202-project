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
	int level = 5;
	int score = 0;

public:
	toolbar(game* r_pGame);
	toolbarItem getItemClicked(int x);
	void set_level(int lev);
	int get_level(); 
	void set_lives();
	int get_lives();
	void set_score(int s);	//handles clicks on toolbar icons, returns the "enum" of the clicekd item
	int get_score();
};

