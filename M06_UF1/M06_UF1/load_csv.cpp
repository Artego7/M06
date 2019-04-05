#include "load_csv.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>




int tableroBackground(std::ifstream& game_conf, levels& level, int width, int height) {
	std::string word;
	int value = -10;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			std::getline(game_conf, word, ';');
			value = std::stoi(word);
			level.background[i][j] = value;
			std::cout << level.background[i][j];
		}
		std::cout << std::endl;
		std::getline(game_conf, word, '\n');
	}
	return 0;
};
int tableroForeground(std::ifstream& game_conf, levels& level, int width, int height) {
	std::string word;
	int value = -10;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			std::getline(game_conf, word, ';');
			value = std::stoi(word);
			level.foreground[i][j] = value;
			std::cout << level.foreground[i][j];
		}
		std::cout << std::endl;
		std::getline(game_conf, word, '\n');
	}
	return 0;
};


int tableroCollision(std::ifstream& game_conf, levels& level, int width, int height) {
	std::string word;
	std::string value = "ZZ";

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			std::getline(game_conf, word, ';');
			value = word;
			level.collision[i][j] = value;
			if (level.foreground[i][j] == 4)
			{
				level.collision[i][j] = "w";
			}
			std::cout << level.collision[i][j];
		}
		std::cout << std::endl;
		std::getline(game_conf, word, '\n');
	}
	return 0;
};


int	loadTextures(std::ifstream& game_conf, texturas& textura, int num) {
	std::string word;
	textura.array_textures = new std::string[num + 1];
	textura.array_textures[0] = "none";
	for (int i = 1; i <= num; ++i) {
		std::getline(game_conf, word, ';');
		std::getline(game_conf, word, ';');
		textura.array_textures[i] = word;
		std::cout << textura.array_textures[i] << std::endl;
		std::getline(game_conf, word, '\n');
	}
	return 0;
};

int loadLevel(std::ifstream& game_conf, levels* level, int num) {
	std::string word;
	
	for (int i = 0; i < num; ++i) {
		std::getline(game_conf, word, ';');
		if (word.compare("LEVEL") != 0)
		{
			return 1;
		}
		if (word.compare("LEVEL") == 0) {
			std::getline(game_conf, word, ';');
			int level_num = std::stoi(word);

			std::getline(game_conf, word, ';');
			std::string level_title = word;

			std::getline(game_conf, word, ';');
			int w = std::stoi(word);

			std::getline(game_conf, word, ';');
			int h = std::stoi(word);

			level[i].level = level_num;
			level[i].title = level_title;
			level[i].width = w;
			level[i].height = h;

			std::cout << "Nivel: " << level[i].level << std::endl
				<< "Titulo: " << level[i].title << std::endl
				<< "Ancho Tablero:" << level[i].width << std::endl
				<< "Alto Tablero:" << level[i].height << std::endl;
			std::getline(game_conf, word, '\n');

			for (int k = 0; k < 3; k++)
			{
				std::getline(game_conf, word, ';');
				std::string block = word;
				std::cout << word << std::endl;
				std::getline(game_conf, word, '\n');
				
				if (block.compare("BACKGROUND") == 0) {
					for (int j = 0; j < level_num; j++)
					{
						level[j].background = new int*[level[j].height];
						for (int l = 0; l < level[j].height; l++)
						{
							level[j].background[l] = new int[level[j].width];

						}
					}
					tableroBackground(game_conf, level[i], level[i].width, level[i].height);
				}
				if (block.compare("FOREGROUND") == 0) {
					for (int j = 0; j < level_num; j++)
					{
						level[j].foreground = new int*[level[j].height];

						for (int l = 0; l < level[j].height; ++l)
						{
							level[j].foreground[l] = new int[level[j].width];

						}
					}
					tableroForeground(game_conf, level[i], level[i].width, level[i].height);
				}
				if (block.compare("COLLISION") == 0) {
					for (int j = 0; j < level_num; j++)
					{
						level[j].collision = new std::string*[level[j].height];

						for (int l = 0; l < level[j].height; ++l)
						{
							level[j].collision[l] = new std::string[level[j].width];

						}
					}
					tableroCollision(game_conf, level[i], level[i].width, level[i].height);
				}
			}
		}
	}
	return 0;
};
