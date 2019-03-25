#pragma once
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]);
int	loadTextures(std::ifstream& game_conf, int num);
int loadLevel(std::ifstream& game_conf, int num);