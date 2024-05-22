#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "operations.h"
#include "grid.h"
#include <ctime>
#include<chrono>
#include <thread>




//Main class that coordinates the game operation
class game
{

	/// Add more members if needed
	
	toolbar* gameToolbar;
	window* pWind;	//Pointer to the CMU graphics window
	grid* shapesGrid;
	bool exitFlag = false;

	clock_t startClock;
	time_t countdownDuration; // in seconds


public:
	game();
	~game();
	void setExitFlag(bool flag);
	string getSrting() const;	 //Returns a string entered by the user
	void createWind(int, int, int, int); //creates the game window
	void clearStatusBar() const;	//Clears the status bar
	void printMessage(string msg) const;	//Print a message on Status bar
	void createToolBar();		//creates the toolbar
	void createGrid();		//creates the shapes grid

	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid
	toolbar* getToolbar() const; //returns a pointer to the shapes toolbar

	//creates an operation according to the toolbar item clicked
	operation* createRequiredOperation(toolbarItem clickedItem);



	void run();	//start the game

	void test(); // Test modules

	void setStartClock(time_t duration); // Initialize startClock and countdown duration
	time_t getStartClock();
	void updateTime(); // Function to update and display the countdown timer
	// Other members and functions of the game class...

	// Assuming pWind is a pointer to a window or drawing object
	//YourWindowType* pWind;

	void timer();
	void generateRandomShapes();

};

