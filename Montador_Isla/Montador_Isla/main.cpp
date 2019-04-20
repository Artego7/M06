#include "main.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>

Map isla;

//=============LOADISLA=============//
int loadMap(std::ifstream& game_conf) {
	std::string word;
	int value = -10;

		isla.land = new int*[isla.width];
	for (int i = 0; i < isla.width; i++)
	{
		for (int j = 0; j < isla.height; j++)
		{
			isla.land[i] = new int[isla.height];
			std::getline(game_conf, word, ';');
			value = std::stoi(word);
			isla.land[i][j] = value;
			std::cout << isla.land[i][j] << ";";
		}
		std::cout << std::endl;
		std::getline(game_conf, word, '\n');
	}
	return 0;
}


//=============COLOR=============//

int printLand() {


	for (int i = 0; i < isla.height; i++) {
	float offset_x = (-isla.width / 2);
	float offset_z = (-isla.height / 2);
		for (int j = 0; j < isla.width; j++) {
			int x_increment = j;
			int z_increment = i;
			isla.landPos = {
				offset_x + x_increment,
				0.0f,
				offset_z + z_increment
			};
			if (isla.land[i][j] == 0) {
				isla.color = BLUE;
			}
			else if (isla.land[i][j] == 1 || isla.land[i][j] == 2) {
				isla.color = YELLOW;
			}
			else if (isla.land[i][j] >= 3 || isla.land[i][j] <= 5) {
				isla.color = GREEN;
			}
			else if (isla.land[i][j] >= 6 || isla.land[i][j] <= 7) {
				isla.color = DARKGREEN;
			}
			else if (isla.land[i][j] >= 8 || isla.land[i][j] <= 11) {
				isla.color = BROWN;
			}
			else if (isla.land[i][j] >= 12 || isla.land[i][j] <= 14) {
				isla.color = DARKBROWN;
			}
			else if (isla.land[i][j] >= 15 || isla.land[i][j] <= 16) {
				isla.color = WHITE;
			}
			DrawCube(isla.landPos, isla.landSize.x, isla.land[i][j] + 1, isla.landSize.z, isla.color);
		}
	}

	return 0;
}

//=============RAYLIB=============//
int doRayMagic() {
	//Declara la posicion de la camara, angulo y profundidad
	Camera camera = { { 0.0f, 20.0f, 25.0f },
					  { 0.0f, 0.0f, 0.0f },
					  { 0.0f, 4.0f, 0.0f }, 35.0f, 0 };

	isla.landSize = { 1.0f, 1.0f, 1.0f };

	int screenWidth = 1760;
	int screenHeight = 990;

	//==========================================================================//
	InitWindow(screenWidth, screenHeight, "");
	SetCameraMode(camera, CAMERA_ORBITAL);
	SetTargetFPS(60);


	//==========================================================================//
	while (!WindowShouldClose())
	{
		UpdateCamera(&camera);
		//if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 0.1f;
		//else if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 0.1f;
		//else if (IsKeyDown(KEY_DOWN)) playerPosition.z += 0.1f;
		//else if (IsKeyDown(KEY_UP)) playerPosition.z -= 0.1f;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		printLand();


		DrawGrid(100, 1.0f);        // Draw a grid

		EndMode3D();

		DrawText("Move player with cursors to collide", 220, 40, 20, GRAY);

		DrawFPS(10, 10);

		//==========================================================================//

		//==========================================================================//
		EndDrawing();

	}
	CloseWindow();

	return 0;
}
//================================//

int main() {

	std::ifstream game_conf("../Montador_Isla/Map.csv");
	if (!game_conf.is_open()) {
		std::cout
			<< "ERROR: Error al abrir el archivo" << std::endl;
		return 1;
	}
	std::string word;

	while (game_conf.good()) {
		std::getline(game_conf, word, ';');

		if (word.compare("ISLA") == 0) {
			std::getline(game_conf, word, '\n');
			std::getline(game_conf, word, ';');
			isla.title = word;
			std::getline(game_conf, word, '\n');
			std::getline(game_conf, word, ';');
			isla.height = std::stoi(word);
			std::getline(game_conf, word, ';');
			isla.width = std::stoi(word);
			std::getline(game_conf, word, '\n');
			std::getline(game_conf, word, ';');
			if (word.compare("ESTACION") == 0) {
				int estacion;
				std::getline(game_conf, word, ';');
				estacion = std::stoi(word);
				switch (estacion)
				{
				case 0:
					isla.Estacion = isla.Inviero;
					break;
				case 1:
					isla.Estacion = isla.Primavera;
					break;
				case 2:
					isla.Estacion = isla.Verano;
					break;
				case 3:
					isla.Estacion = isla.Otono;
					break;
				default:
					break;
				}
			}
			else {
				std::cout << "No Hay estacion" << std::endl;
				return 1;
			}
			std::getline(game_conf, word, '\n');

			std::cout << isla.title << std::endl;
			for (int i = 0; i < isla.title.length(); i++) {
				std::cout << '=';
			}
			std::cout << std::endl;
			std::cout << isla.height << std::endl;
			std::cout << isla.width << std::endl;
			std::cout << "Estacion: " << isla.Estacion << std::endl;

		}

		if (word.compare("MAPA") == 0) {
			std::getline(game_conf, word, '\n');
			loadMap(game_conf);
		}
	}

	doRayMagic();
	return 0;
}