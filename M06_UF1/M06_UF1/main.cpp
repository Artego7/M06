#include "raylib.h"
#include "load_csv.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>

texturas textura;
levels* level;
bomb* bombs;

int level_num = 0;
int max_bombs = 10;
int current_bomb = 0;

//////////////COMPROVACIONES///////////////////
//std::cout << level_num << std::endl;
//std::cout << textura.textures_num << std::endl;
//std::cout << textura.array_textures[1] << std::endl;
//std::cout << textura.array_textures[2] << std::endl;
//std::cout << textura.array_textures[3] << std::endl;
//std::cout << textura.array_textures[4] << std::endl;
//std::cout << level[0].level << std::endl;
//std::cout << level[0].height << std::endl;
//std::cout << level[0].width << std::endl;
//std::cout << level[0].title << std::endl;
//
//for (int i = 0; i < level[0].height; ++i)
//{
//	for (int j = 0; j < level[0].width; j++)
//	{
//		std::cout << level[0].background[i][j];
//	}
//	std::cout << std::endl;
//}
//for (int i = 0; i < level[0].height; ++i)
//{
//	for (int j = 0; j < level[0].width; j++)
//	{
//		std::cout << level[0].foreground[i][j];
//	}
//	std::cout << std::endl;
//}
//for (int i = 0; i < level[0].height; ++i)
//{
//	for (int j = 0; j < level[0].width; j++)
//	{
//		std::cout << level[0].collision[i][j];
//	}
//	std::cout << std::endl;
//}


int setTextres(int num) {
	textura.img_textures = new Image[num + 1];
	textura.texures = new Texture2D[num + 1];

	for (int i = 1; i <= num; ++i) {
		std::string temp_texture = "../texturas/" + textura.array_textures[i];
		std::cout << temp_texture << std::endl;
		textura.img_textures[i] = LoadImage(temp_texture.c_str());
		textura.texures[i] = LoadTextureFromImage(textura.img_textures[i]);
	}

	return 0;
}

int printTextures(Vector3 BlockBoxSize) {
	int currentLevel = 0;
	float alturaBloque = 0;

	for (int layer = 0; layer < 3; layer++) {
		int offset_x = -level[currentLevel].width;
		int offset_z = -level[currentLevel].height;
		float update_size_x = BlockBoxSize.x;
		float update_size_y = BlockBoxSize.y;
		float update_size_z = BlockBoxSize.z;
		for (int i = 0; i < level[currentLevel].height; i++) {
			for (int j = 0; j < level[currentLevel].width; j++) {
				int x_increment = j;
				int y_increment = 0;
				int z_increment = i;
				if (x_increment != 0 || z_increment != 0)
				{
					x_increment += (x_increment * (BlockBoxSize.x / update_size_x));
					z_increment += (z_increment * (BlockBoxSize.z / update_size_z));
				}
				Vector3 BlockBoxPos = {
					offset_x + x_increment,
					0.0f,
					offset_z + z_increment };
				int textureLayer = 0;

				if (layer == 0)
				{
					textureLayer = level[currentLevel].background[i][j];
				}
				else if (layer == 1)
				{
					textureLayer = level[currentLevel].foreground[i][j];
					BlockBoxPos.y = 2.0f;
					alturaBloque = 2.0f;
				}
				else if (layer == 2)
				{
					//collision
				}
				if (textureLayer != 0) 
				{
					DrawCubeTexture(textura.texures[textureLayer], BlockBoxPos, BlockBoxSize.x, BlockBoxSize.y, BlockBoxSize.z, WHITE);
					//DrawCubeWires(BlockBoxPos, BlockBoxSize.x, BlockBoxSize.y, BlockBoxSize.z, DARKGRAY);
				}
			}
		}
	}

	return 0;
}
int chekCollisionPlayer(Vector3& playerPosition, Vector3& playerSize, Vector3& playerPosition_prev, Vector3& BlockBoxSize, Color& playerColor, bool collision) {
	//Check collisions player vs enemy-box

	int currentLevel = 0;
	float alturaBloque = 0;


		int offset_x = -level[currentLevel].width;
		int offset_z = -level[currentLevel].height;
		float update_size_x = BlockBoxSize.x;
		float update_size_y = BlockBoxSize.y;
		float update_size_z = BlockBoxSize.z;
		for (int i = 0; i < level[currentLevel].height; i++) {
			for (int j = 0; j < level[currentLevel].width; j++) {
				int x_increment = j;
				int z_increment = i;
				if (x_increment != 0 || z_increment != 0)
				{

					x_increment += (x_increment * (BlockBoxSize.x / update_size_x));
					z_increment += (z_increment * (BlockBoxSize.z / update_size_z));
				}
				Vector3 BlockBoxPos = {
					offset_x + x_increment,
					1.0f,
					offset_z + z_increment };

				std::string collisionConfirm = level[currentLevel].collision[i][j];

				if ((collisionConfirm == "y" || collisionConfirm == "w") && (CheckCollisionBoxes(
					(BoundingBox({
						(Vector3({
							(float)(playerPosition.x - playerSize.x / 2),
							(float)(playerPosition.y - playerSize.y / 2),
							(float)(playerPosition.z - playerSize.z / 2)})),
						(Vector3({
							(float)(playerPosition.x + playerSize.x / 2),
							(float)(playerPosition.y + playerSize.y / 2),
							(float)(playerPosition.z + playerSize.z / 2) }))
						})),
						(BoundingBox({
							(Vector3({
								(float)(BlockBoxPos.x - BlockBoxSize.x / 2),
								(float)(BlockBoxPos.y - BlockBoxSize.y / 2),
								(float)(BlockBoxPos.z - BlockBoxSize.z / 2)})),
							(Vector3({
								(float)(BlockBoxPos.x + BlockBoxSize.x / 2),
								(float)(BlockBoxPos.y + BlockBoxSize.y / 2),
								(float)(BlockBoxPos.z + BlockBoxSize.z / 2)}))
							}))))) {
					collision = true;
				};
				if (collision) {
					playerColor = RED;
					playerPosition = playerPosition_prev;

				}
				else {
					playerColor = PINK;
				}
			}

	}
	return 0;
}

int bombGenerator(Vector3 playerPosition) {
	bombs = new bomb[max_bombs];
	for (int i = 0; i < max_bombs; i++)
	{
		bombs[i].BombPos = { 1.0f, 1.0f, 1.0f };
		bombs[i].BombSize = 1.5f;
		bombs[i].BombColor = BLACK;   
	}
	if (IsKeyPressed(KEY_SPACE) && current_bomb <= max_bombs)
	{
		current_bomb++;
		bombs[current_bomb].BombPos = playerPosition;
		DrawSphereEx(bombs[current_bomb].BombPos, bombs[current_bomb].BombSize, 25, 25, bombs[current_bomb].BombColor);
	}
	return 0;
}

// Integrar collisiones que mire todas las casillas
// mirar en el csv y si hay y que no pase

int doRayMagic() {
	Camera camera = { { 0.0f, 40.0f, 25.0f },
					  { 0.0f, 0.0f, 0.0f },
					  { 0.0f, 4.0f, 0.0f }, 45.0f, 0 };
	Vector3 playerPosition = { 0.0f, 2.0f, 2.0f };
	Vector3 playerPosition_prev = playerPosition;
	Vector3 playerSize = { 1.0f, 2.0f, 1.0f };
	Color playerColor = PINK;

	Vector3 BlockBoxPos = { 1.0f, 1.0f, 1.0f };
	Vector3 BlockBoxSize = { 1.0f, 1.0f, 1.0f };
	
	

	bool collision = false;

	int screenWidth = 1760;
	int screenHeight = 990;


	//==========================================================================//
	InitWindow(screenWidth, screenHeight, "");
	SetTargetFPS(60);

	setTextres(textura.textures_num);

	//==========================================================================//
	while (!WindowShouldClose())
	{
		collision = false;

		playerPosition_prev = playerPosition;

		if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 0.2f;
		else if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 0.2f;
		else if (IsKeyDown(KEY_DOWN)) playerPosition.z += 0.2f;
		else if (IsKeyDown(KEY_UP)) playerPosition.z -= 0.2f;

		chekCollisionPlayer(playerPosition, playerSize, playerPosition_prev, BlockBoxSize, playerColor, collision);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		printTextures(BlockBoxSize);
		bombGenerator(playerPosition);


		

		// Draw player
		DrawCubeV(playerPosition, playerSize, playerColor);

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

int main(int argc, char* argv[]) {
	std::ifstream game_conf("../M06_UF1/Game.csv");
	if (!game_conf.is_open()) {
		std::cout
			<< "ERROR: Error al abrir el archivo" << '\n';
		return 1;
	}

	std::string word;
	std::string title;

	while (game_conf.good()) {
		std::getline(game_conf, word, ';');
		if (word.compare("TITLE") == 0) {
			std::getline(game_conf, word, ';');
			title = word;
			std::cout << title << '\n';
			for (int i = 0; i < title.length(); i++) {
				std::cout << '=';
			}
			std::cout << '\n';
			std::getline(game_conf, word, '\n');
		}

		if (word.compare("TEXTURES") == 0) {
			std::getline(game_conf, word, ';');
			textura.textures_num = std::stoi(word);
			std::getline(game_conf, word, '\n');
			std::cout << "TEXTURAS" << '\n';
			loadTextures(game_conf, textura, textura.textures_num);
			for (int i = 0; i < title.length(); i++) {
				std::cout << '=';
			}
			std::cout << '\n';
		}

		if (word.compare("LEVELS") == 0) {
			std::getline(game_conf, word, ';');
			level_num = std::stoi(word);
			std::getline(game_conf, word, '\n');
			std::cout << "NIVELES" << '\n' << '\n';
			level = new levels[level_num];
			loadLevel(game_conf, level, level_num);
		}
	}

	doRayMagic();

	game_conf.close();

	return 0;
}

