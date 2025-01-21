#pragma once


enum eGameStates
{
	NOT_STARTED = 0,
	STARTED,
	CONTROLS,
	RUNNING,
	NEWLEVEL,
	GAMEOVER
};

enum eKeycodes
{
	Z = 90,
	X = 88,
	C = 67,
	V = 86,
	E = 69,
	F = 70,
	SPACE = 32,
};

enum eGameStreaks
{
	NONE = 0,
	HOLEINONE = 1,
	TWOTOFOUR = 2,
    FIVETOSEVEN = 3
};

enum eLevelModifiers
{
	NIL = 1,
	UNPREDTICTABLEMOVE = 2,
	RIGIDMOVEMENT = 3,
	FOGOFWAR = 4,
};
