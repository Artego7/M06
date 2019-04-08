#pragma once
#include "raylib.h"
#include <iostream>
#include <fstream>

struct bomb {
	Vector3 BombPos;
	float BombSize;
	
	Color BombColor;
	Color BombColor_hot = RED;
	Color BombColor_explosion = RED;
	
	bool active = false;
	
	float time_limit = 10.0f;
	float time_current = 0.0f;

	float expansion_time = 2.0f;
	float expansion_time_curr = 0.0f;


};

int main(int argc, char* argv[]);
int setTextres(int num);
int printTextures(Vector3 BlockBoxSize);
int chekCollisionPlayer(Vector3& playerPosition, Vector3& playerSize, Vector3& playerPosition_prev, Vector3& BlockBoxSize, Color& playerColor, bool collision);
int setbombs();
int bombGenerator(Vector3 playerPosition);
int printBomb();
int doRayMagic();
