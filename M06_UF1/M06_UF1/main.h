#pragma once
#include "raylib.h"
#include <iostream>
#include <fstream>

struct bomb {
	Vector3 BombPos;
	float BombSize;
	
	int rings = 6;
	int slices = 6;

	Color BombColor;
	Color BombColor_hot;
	Color BombColor_explosion;
	
	
	float time_limit;
	float time_current;

	bool active;
	bool max_expansion;
};

int main(int argc, char* argv[]);

int doRayMagic();

//=============TEXTURAS=============//
int setTextres(int num);
int printTextures(Vector3& BlockBoxSize, Vector3& playerSize);

//=============PLAYER=============//
int chekCollisionPlayer(Vector3& playerPosition, Vector3& playerSize, Vector3& playerPosition_prev, Vector3& BlockBoxSize, Color& playerColor, bool collision);

//=============BOMBS=============//
int setbombs(bomb& bombs);
int colorBomb(bomb& bombs, Color color);
void checkBombActive(Vector3 playerPosition);
int generateBomb();

//=============BLOCKS=============//
int destroyBlocks();

