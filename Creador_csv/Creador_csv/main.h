#pragma once
#include <iostream>
#include <string>

struct Map {
	std::string nombre;
	
	int ancho;
	int alto;

	int maxAncho = 256;
	int maxAlto = 256;

	enum EstacionDelAno {
		Inviero,
		Primavera,
		Verano,
		Otono
	}Estacion;

	int** terreno;

	bool rellenoBase = false;
	bool procedural = false;
};



int main();

int escribirArchivoCSV();
int generarMapa(std::ofstream& archivo);