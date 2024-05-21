#pragma once

class game;
/////////////////////////////////// class operation  //////////////////
//Base class of all operations supported by the application
class operation
{
protected:
	game* pGame;	//pointer to the game class
public:
	operation(game* r_pGame);

	//Function Act:
	//Implements the action that should be taken by this operation
	//Should be overriden by derived classes
	virtual void Act() = 0;
};
/////////////////////////////////// class operAddSign  //////////////////
//Responsible for 
//1- collectign data about a new Sign shape to add
//2- Adding the new shape to the list of shapes (throgh the grid class)
class operAddSign :public operation
{
public:
	operAddSign(game* r_pGame);
	virtual void Act();
};

class operCar :public operation
{
public:
	operCar(game* r_pGame);
	virtual void Act();
};

class operHouse :public operation
{
public:
	operHouse(game* r_pGame);
	virtual void Act();
};

class operTree :public operation
{
public:
	operTree(game* r_pGame);
	virtual void Act();
};

class operAirplane :public operation
{
public:
	operAirplane(game* r_pGame);
	virtual void Act();
};

class operIcecream :public operation
{
public:
	operIcecream(game* r_pGame);
	virtual void Act();
};
class operCloud :public operation
{
public:
	operCloud(game* r_pGame);
	virtual void Act();
};
class operRotate :public operation
{
public:
	operRotate(game* r_pGame);
	virtual void Act();
};

class operPlus :public operation
{
public:
	operPlus(game* r_pGame);
	virtual void Act();
};

class operMinus :public operation
{
public:
	operMinus(game* r_pGame);
	virtual void Act();
};

class operDelete : public operation
{
public:
	operDelete(game* r_pGame);
	virtual void Act();

};

class operHint : public operation
{
public:
	operHint(game* r_pGame);
	virtual void Act();

};

class operGameLevel : public operation
{
public:
	operGameLevel(game* r_pGame);
	virtual void Act();

};
class operSave : public operation
{
public:
	operSave(game* r_pGame);
	virtual void Act();

};
class operLoad : public operation
{
public:
	operLoad(game* r_pGame);
	virtual void Act();

};

class operRefresh : public operation
{
public:
	operRefresh(game* r_pGame);
	virtual void Act();

};

class operExit : public operation
{
public:
	operExit(game* r_pGame);
	virtual void Act();

};


