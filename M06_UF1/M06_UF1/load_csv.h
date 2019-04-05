#pragma once
#include "raylib.h"
#include <string>

	struct levels {
		std::string title;
		int level;
		int width;
		int height;
		int** background;
		int** foreground;
		std::string** collision;
	};
	
	struct texturas {
		std::string* array_textures;
		int textures_num = 0;
		Image* img_textures;
		Texture2D* texures;
	};
	
	
	int	loadTextures(std::ifstream& game_conf, texturas& textura, int num);
	int loadLevel(std::ifstream& game_conf, levels* level, int num);

	int tableroBackground(std::ifstream& game_conf, levels& level, int width, int height);
	int tableroForeground(std::ifstream& game_conf, levels& level, int width, int height);
	int tableroCollision(std::ifstream& game_conf, levels& level, int width, int height);



