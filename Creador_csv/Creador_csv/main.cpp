#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>


Map mapa;


int generarMapa(std::ofstream& archivo) {
	int opcion;

	std::cout << "Como quieres generar el mapa:" << std::endl;
	std::cout << "0: Manual" << std::endl;
	std::cout << "1: Procedural" << std::endl;
	std::cin >> opcion;

	switch (opcion)
	{
	case 0: //Manual
		for (int i = 0; i < mapa.ancho; i++) {
			mapa.terreno = new int*[mapa.ancho];
			for (int j = 0; j < mapa.alto; j++) {
				mapa.terreno[i] = new int[mapa.alto];
				mapa.terreno[i][j] = 0;
			}
		}
		break;
	case 1: //Procedural
		for (int i = 0; i < mapa.ancho; i++) {
			mapa.terreno = new int*[mapa.ancho];
			for (int j = 0; j < mapa.alto; j++) {
				mapa.terreno[i] = new int[mapa.alto];
				mapa.terreno[i][j] = rand() % 17;
				std::cout << mapa.terreno[i][j];
				archivo << mapa.terreno[i][j] << ";";
			}
			archivo << ";\n";
			std::cout << std::endl;
		}
		break;

	default:
		std::cout << "No es un valor valido" << std::endl;
		generarMapa(archivo);
		break;
	}
	return 0;
}

int escribirArchivoCSV() {
	std::ofstream archivo;
	archivo.open("../../Montador_Isla/Montador_Isla/Map.csv", std::ofstream::out);

	if (archivo.fail()) {
		std::cout << "No se ha abierto el archivo" << std::endl;
		return 1;
	}
	std::cout << "Dime el nombre de tu isla:" << std::endl;
	std::cin >> mapa.nombre;
	do
	{
		std::cout << "===========================================================================" << std::endl;
		std::cout << "===========================================================================" << std::endl;
		std::cout << "WARNING" << std::endl;
		std::cout << "===========================================================================" << std::endl;
		std::cout << "Tanto el alto como el ancho tienen un maximo de 256." << std::endl;
		std::cout << "La aplicacion que se usa para ejecutar el mapa esta limitado a 18 por 18," << std::endl;
		std::cout << "un rango mas alto de bloques puede probocar que no funcione el programa." << std::endl;
		std::cout << "===========================================================================" << std::endl;
		std::cout << "===========================================================================" << std::endl;

		std::cout << "Dime el alto de tu isla:" << std::endl;
		std::cin >> mapa.alto;
		std::cout << "Dime el ancho de tu isla:" << std::endl;
		std::cin >> mapa.ancho;
		if (mapa.alto >= mapa.maxAlto || mapa.ancho >= mapa.maxAncho) {
			std::cout << "Tanto el ancho como el alto tienen un maximo de 256." << std::endl;
			std::cout << "Porfavor escriba un rango nuevo." << std::endl;
		}
		if (mapa.alto == 0 || mapa.ancho == 0) {
			std::cout << "Tanto el ancho como el alto tienen que tener un valor diferente a 0." << std::endl;
			std::cout << "Porfavor escriba un rango nuevo." << std::endl;
		}
	} while (mapa.alto >= mapa.maxAlto || mapa.ancho >= mapa.maxAncho
		|| mapa.alto == 0 || mapa.ancho == 0);
	int estacion;
	do
	{
		std::cout << "Dime el numero de la estacion del ano quieres:" << std::endl;
		std::cout << "(0:Inviero, 1:Primavera, 2:Verano, 3:Otono)" << std::endl;
		std::cin >> estacion;
		switch (estacion)
		{
		case 0:
			mapa.Estacion = mapa.Inviero;
			break;
		case 1:
			mapa.Estacion = mapa.Primavera;
			break;
		case 2:
			mapa.Estacion = mapa.Verano;
			break;
		case 3:
			mapa.Estacion = mapa.Otono;
			break;
		default:
			std::cout << "Solo son validos los numeros entre el 0 y el 3." << std::endl;
			std::cout << "Porfavor escriba de nuevo." << std::endl;
			break;
		}
	} while (estacion > 3 || estacion < 0);

	archivo << "ISLA" << ";;\n"
		<< mapa.nombre << ";;\n"
		<< mapa.alto << ";" << mapa.ancho << ";;\n"
		<< "ESTACION" << ";" << mapa.Estacion << ";;\n"
		<< "MAPA" << ";;\n";

	generarMapa(archivo);
	
	archivo.close();
	return 0;
}



int main() {
	srand(time(NULL));

	escribirArchivoCSV();

	return 0;
}


