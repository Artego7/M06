#pragma once
#include "raylib.h"
#include <iostream>
#include <string>

struct Map
{
	std::string title;

	int width;
	int height;

	enum EstacionDelAno {
		Inviero,
		Primavera,
		Verano,
		Otono
	}Estacion;

	int** land;

	Vector3 landSize;
	Vector3 landPos;

	Color color;
};



int main();
int doRayMagic();

int loadMap(std::ifstream& game_conf);

int printLand();