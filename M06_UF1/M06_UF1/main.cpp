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

int currentLevel = 0;

int level_num = 0;
int max_bombs = 10;

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

//=============TEXTURAS=============//
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

int printTextures(Vector3& BlockBoxSize, Vector3& playerSize) {

	for (int layer = 0; layer < 3; layer++) {
		int offset_x = (-level[currentLevel].width / 2);
		int offset_z = (-level[currentLevel].height / 2);

		for (int i = 0; i < level[currentLevel].height; i++) {
			for (int j = 0; j < level[currentLevel].width; j++) {
				int x_increment = j;
				int z_increment = i;
				if (BlockBoxSize.x == 2.0f && (x_increment != 0 || z_increment != 0))
				{
					x_increment += x_increment * (BlockBoxSize.x / BlockBoxSize.x);
					z_increment += z_increment * (BlockBoxSize.z / BlockBoxSize.z);
				}
				Vector3 BlockBoxPos = {
					offset_x + x_increment,
					0.0f,
					offset_z + z_increment
				};
				int textureLayer = 0;

				if (layer == 0) {
					textureLayer = level[currentLevel].background[i][j];
				}
				else if (layer == 1) {
					textureLayer = level[currentLevel].foreground[i][j];
					BlockBoxPos.y += BlockBoxSize.y;
				}
				else if (layer == 2) {
					//collision
				}
				if (textureLayer != 0) {
					DrawCubeTexture(textura.texures[textureLayer], BlockBoxPos, BlockBoxSize.x, BlockBoxSize.y, BlockBoxSize.z, WHITE);
					DrawCubeWires(BlockBoxPos, BlockBoxSize.x, BlockBoxSize.y, BlockBoxSize.z, BLACK);
					//DrawCubeWires(BlockBoxPos, BlockBoxSize.x, BlockBoxSize.y, BlockBoxSize.z, DARKGRAY);
				}
			}
		}
	}

	return 0;
}

//=============PLAYER=============//
int chekCollisionPlayer(Vector3& playerPosition, Vector3& playerSize, Vector3& playerPosition_prev, Vector3& BlockBoxSize, Color& playerColor, bool collision) {
	//Check collisions player vs enemy-box

	int currentLevel = 0;

	int offset_x = (-level[currentLevel].width / 2);
	int offset_z = (-level[currentLevel].height / 2);

		for (int i = 0; i < level[currentLevel].height; i++) {
			for (int j = 0; j < level[currentLevel].width; j++) {
				int x_increment = j;
				int z_increment = i;
				if (BlockBoxSize.x == 2.0f && (x_increment != 0 || z_increment != 0))
				{
					x_increment += x_increment * (BlockBoxSize.x / BlockBoxSize.x);
					z_increment += z_increment * (BlockBoxSize.z / BlockBoxSize.z);
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

//=============BLOCKS=============//

//=============BOMBS=============//
int setbombs(bomb& bombs) {
		bombs.BombPos = { 1.0f, 1.0f, 1.0f };
		bombs.BombSize = 0.2f;
		
		bombs.time_current = 0.0f;
		bombs.time_limit = 8.0f;
		
		bombs.BombColor = BLACK;
		bombs.BombColor_hot = ORANGE;
		bombs.BombColor_explosion= RED;

		bombs.active = false;
		bombs.max_expansion = false;
	return 0;
}

void checkBombActive(Vector3 playerPosition) {
		
	for (int i = 0; i < max_bombs; i++) {
		if (!bombs[i].active) {
			bombs[i].active = true;
			bombs[i].BombPos = playerPosition;
			return;
		}
	}
}

int colorBomb(bomb& bombs, Color color) {
	bombs.BombColor.r = color.r - (bombs.time_current / bombs.time_limit);
	bombs.BombColor.g = color.g - (bombs.time_current / bombs.time_limit);
	bombs.BombColor.b = color.b - (bombs.time_current / bombs.time_limit);
	return 0;
}

int generateBomb() {
	float current_time = GetFrameTime();
	
	for (int i = 0; i < max_bombs; i++) {
		if (bombs[i].active) {
			//std::cout << bombs[i].BombPos.x << std::endl;
			//std::cout << bombs[i].BombPos.z << std::endl;

			int tempPosBombx = bombs[i].BombPos.x;
			if (bombs[i].BombPos.x > 0.0f)
			{
				if (bombs[i].BombPos.x >= ((float)tempPosBombx + 0.5)) {
					if (tempPosBombx % 2 == 0) {
						bombs[i].BombPos.x = ((float)tempPosBombx + 1.0f);
						//std::cout << "Mayor Positivo Par: " << bombs[i].BombPos.x << std::endl;
					}
					if (tempPosBombx % 2 != 0) {
						bombs[i].BombPos.x = ((float)tempPosBombx + 1.0f);
						//std::cout << "Mayor Positivo Impar: " << bombs[i].BombPos.x << std::endl;
					}
				}
				else if (bombs[i].BombPos.x < ((float)tempPosBombx + 0.5)) {
					if (tempPosBombx % 2 == 0) {
						bombs[i].BombPos.x = (float)tempPosBombx;
						//std::cout << "Menor Positivo Par: " << bombs[i].BombPos.x << std::endl;
					}
					if (tempPosBombx % 2 != 0) {
						bombs[i].BombPos.x = (float)tempPosBombx;
						//std::cout << "Menor Positivo Impar: " << bombs[i].BombPos.x << std::endl;
					}
				}
			}
			if (bombs[i].BombPos.x < 0.0f)
			{

				if (bombs[i].BombPos.x <= ((float)tempPosBombx - 0.5)) {
					if (tempPosBombx % 2 == 0) {
						bombs[i].BombPos.x = ((float)tempPosBombx - 1.0f);
						//std::cout << "Menor Negativo Par: " << bombs[i].BombPos.x << tempPosBombx << std::endl;
					}
					if (tempPosBombx % 2 != 0) {
						bombs[i].BombPos.x = ((float)tempPosBombx - 1.0f);
						//std::cout << "Menor Negativo Impar: " << bombs[i].BombPos.x << std::endl;
					}
				}
				else if (bombs[i].BombPos.x > ((float)tempPosBombx - 0.5)) {
					if (tempPosBombx % 2 == 0) {
						bombs[i].BombPos.x = (float)tempPosBombx;
						//std::cout << "Mayor Negativo Par: " << bombs[i].BombPos.x << std::endl;
					}
					if (tempPosBombx % 2 != 0) {
						bombs[i].BombPos.x = (float)tempPosBombx;
						//std::cout << "Mayor Negativo Impar: " << bombs[i].BombPos.x << std::endl;
					}
				}
			}

			int tempPosBombz = bombs[i].BombPos.z;
			if (bombs[i].BombPos.z > 0.0f)
			{
				if (bombs[i].BombPos.z >= ((float)tempPosBombz + 0.5)) {
					if (tempPosBombz % 2 == 0) {
						bombs[i].BombPos.z = ((float)tempPosBombz + 1.0f);
						std::cout << "Mayor Positivo Par: " << bombs[i].BombPos.z << std::endl;
					}
					if (tempPosBombz % 2 != 0) {
						bombs[i].BombPos.z = ((float)tempPosBombz + 1.0f);
						std::cout << "Mayor Positivo Impar: " << bombs[i].BombPos.z << std::endl;
					}
				}
				else if (bombs[i].BombPos.z < ((float)tempPosBombz + 0.5)) {
					if (tempPosBombz % 2 == 0) {
						bombs[i].BombPos.z = (float)tempPosBombz;
						std::cout << "Menor Positivo Par: " << bombs[i].BombPos.z << std::endl;
					}
					if (tempPosBombz % 2 != 0) {
						bombs[i].BombPos.z = (float)tempPosBombz;
						std::cout << "Menor Positivo Impar: " << bombs[i].BombPos.z << std::endl;
					}
				}
			}
			if (bombs[i].BombPos.z < 0.0f)
			{

				if (bombs[i].BombPos.z <= ((float)tempPosBombz - 0.5)) {
					if (tempPosBombz % 2 == 0) {
						bombs[i].BombPos.z = ((float)tempPosBombz - 1.0f);
						std::cout << "Menor Negativo Par: " << bombs[i].BombPos.z << std::endl;
					}
					if (tempPosBombz % 2 != 0) {
						bombs[i].BombPos.z = ((float)tempPosBombz - 1.0f);
						std::cout << "Menor Negativo Impar: " << bombs[i].BombPos.z << std::endl;
					}
				}
				else if (bombs[i].BombPos.z > ((float)tempPosBombz - 0.5)) {
					if (tempPosBombz % 2 == 0) {
						bombs[i].BombPos.z = (float)tempPosBombz;
						std::cout << "Mayor Negativo Par: " << bombs[i].BombPos.z << std::endl;
					}
					if (tempPosBombz % 2 != 0) {
						bombs[i].BombPos.z = (float)tempPosBombz;
						std::cout << "Mayor Negativo Impar: " << bombs[i].BombPos.z << std::endl;
					}
				}
			}

			//bombs[i].BombPos.x = tempPosBombx;
			//bombs[i].BombPos.z = tempPosBombz;

			DrawSphereEx(bombs[i].BombPos, bombs[i].BombSize, bombs[i].rings, bombs[i].slices, bombs[i].BombColor);
			bombs[i].time_current += current_time;
			//std::cout << bombs[i].BombPos.x << std::endl;

			if (bombs[i].BombSize >= 0.2f && bombs[i].max_expansion) {
				if (bombs[i].time_current >= 3.0f) {
					bombs[i].BombSize -= current_time * 2;
				}
				if (bombs[i].time_current >= 6.0f) {
					bombs[i].BombSize -= current_time * 4;
				}
				colorBomb(bombs[i], bombs[i].BombColor_hot);
				if (bombs[i].BombSize <= 0.2f) {

					bombs[i].max_expansion = false;
				}
			}
			if (bombs[i].time_current >= 6.0f) {
				colorBomb(bombs[i], bombs[i].BombColor_explosion);
				bombs[i].BombSize += current_time * 4;
				if (bombs[i].BombSize >= 0.6f) {

					bombs[i].max_expansion = true;
				}
			}else if (bombs[i].time_current >= 3.0f && !bombs[i].max_expansion) {
				colorBomb(bombs[i], bombs[i].BombColor_hot);
				bombs[i].BombSize += current_time * 2;
				//std::cout << bombs[i].BombSize << std::endl;
				if (bombs[i].BombSize >= 0.6f) {

					bombs[i].max_expansion = true;
				}
			}
			if (bombs[i].time_current >= bombs[i].time_limit) {
				int w = tempPosBombx;
				int h = tempPosBombz;
				std::string collisionConfirm1 = level[currentLevel].collision[h][w - 1];
				std::string collisionConfirm2 = level[currentLevel].collision[h - 1][w];
				std::string collisionConfirm3 = level[currentLevel].collision[h][w + 1];
				std::string collisionConfirm4 = level[currentLevel].collision[h + 1][w];
				if (collisionConfirm1 == "w") {
					level[currentLevel].collision[h][w - 1] = "n";
				}
				else if (collisionConfirm2 == "w") {
					level[currentLevel].collision[h - 1][w] = "n";
				}
				else if (collisionConfirm3 == "w") {
					level[currentLevel].collision[h][w + 1] = "n";
				}
				else if (collisionConfirm4 == "w") {
					level[currentLevel].collision[h + 1][w] = "n";
				}
				setbombs(bombs[i]);
			}
		}
	}
	return 0;
}

//=============RAYLIB_INIT=============//
int doRayMagic() {
	//Declara la posicion de la camara, angulo y profundidad
	Camera camera = { { 0.0f, 20.0f, 25.0f },
					  { 0.0f, 0.0f, 0.0f },
					  { 0.0f, 4.0f, 0.0f }, 35.0f, 0 };
	Vector3 playerPosition = { 0.0f, 2.0f, 0.0f };
	Vector3 playerPosition_prev = playerPosition;
	Vector3 playerSize = { 0.5f, 1.0f, 0.5f };
	Color playerColor = PINK;

	Vector3 BlockBoxSize = { 1.0f, 1.0f, 1.0f };

	for (int i = 0; i < level[currentLevel].height; i++) {
		for (int j = 0; j < level[currentLevel].width; j++) {
			if (level[currentLevel].collision[i][j] == "p1") {
				int offset_x = (-level[currentLevel].width / 2);
				int offset_z = (-level[currentLevel].height / 2);
				int x_increment = j;
				int z_increment = i;
				if (x_increment != 0 || z_increment != 0)
				{
					x_increment += x_increment * (BlockBoxSize.x / BlockBoxSize.x);
					z_increment += z_increment * (BlockBoxSize.z / BlockBoxSize.z);
				}
				playerPosition.x = offset_x + x_increment;
				playerPosition.z = offset_z + z_increment;

			}
		}
	}
	playerPosition.y = BlockBoxSize.y;
	bool collision = false;

	int screenWidth = 1760;
	int screenHeight = 990;

	//==========================================================================//
	InitWindow(screenWidth, screenHeight, "");
	SetTargetFPS(60);

	setTextres(textura.textures_num);

	bombs = new bomb[max_bombs];
	for (int i = 0; i < max_bombs; i++) {
		setbombs(bombs[i]);
	}

	//==========================================================================//
	while (!WindowShouldClose())
	{
		collision = false;

		playerPosition_prev = playerPosition;

		if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 0.1f;
		else if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 0.1f;
		else if (IsKeyDown(KEY_DOWN)) playerPosition.z += 0.1f;
		else if (IsKeyDown(KEY_UP)) playerPosition.z -= 0.1f;


		chekCollisionPlayer(playerPosition, playerSize, playerPosition_prev, BlockBoxSize, playerColor, collision);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		printTextures(BlockBoxSize, playerSize);
		if (IsKeyPressed(KEY_SPACE))
		{
			checkBombActive(playerPosition);
		}
		generateBomb();
		

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

//=============MAIN=============//
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

