#include <iostream>
#include <fstream>
#include <string>
#include <array>


struct tableros {
	int* background;
	int* foreground;
	char* collision;
	int width;
	int height;
};

std::string* array_textures;
struct levels {
	std::string title;
	int level = 0;
	tableros tableros;
}levels;

std::string* array_tablero;
int textures_num = 0;
int level_num = 0;


int	loadTextures(std::ifstream& game_conf, int num) {
	std::string word;

	array_textures = new std::string[num + 1];
	array_textures[0] = "none";
	for (int i = 1; i < num + 1; i++) {
		std::getline(game_conf, word, ';');
		std::getline(game_conf, word, ';');
		array_textures[i] = word;
		std::cout << array_textures[i] << '\n';
		std::getline(game_conf, word, '\n');
	}
	return 0;
};

int loadLevel(std::ifstream& game_conf, int num) {
	std::string word;
	for (int i = 0; i < num; i++) {
		std::getline(game_conf, word, ';');
		std::getline(game_conf, word, ';');
		levels.level = std::stoi(word);
		std::cout << "Nivel: " << levels.level << '\n';
		std::getline(game_conf, word, ';');
		levels.title = word;
		std::cout << "Titulo: " << levels.title << '\n';
		std::getline(game_conf, word, ';');
		levels.tableros.width = std::stoi(word);
		std::getline(game_conf, word, ';');
		levels.tableros.height = std::stoi(word);
		std::cout << "Tablero: " << '\n' 
			<< "Ancho:" << levels.tableros.width << '\n' 
			<< "Alto:" << levels.tableros.height << '\n';

	}
	return 0;
};


int main(int argc, char* argv[]) {
	std::ifstream game_conf("../M06_UF1/Game.csv");
	if (!game_conf.is_open()) {
		std::cout << "ERROR: Error al abrir el archivo" << '\n';
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
			textures_num = std::stoi(word);
			std::getline(game_conf, word, '\n');
			std::cout << "TEXTURAS" << '\n';
			loadTextures(game_conf, textures_num);
			for (int i = 0; i < title.length(); i++) {
				std::cout << '=';
			}
			std::cout << '\n';
		}

		if (word.compare("LEVELS") == 0) {
			std::getline(game_conf, word, ';');
			level_num = std::stoi(word);
			std::getline(game_conf, word, '\n');
			std::cout << "NIVELES" << '\n';
			loadLevel(game_conf, level_num);

		}
	}
	game_conf.close();
	return 0;
}

