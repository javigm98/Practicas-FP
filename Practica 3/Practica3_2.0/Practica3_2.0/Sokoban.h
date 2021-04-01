//Practica 3. Javier Guzmán Muñoz y Jorge Villarrubia Elvira. Grupo 3. Doble Grado en ING Informática- Matemáticas

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

#ifndef sokoban_h
#define sokoban_h

typedef enum tTecla{
	Arriba, Abajo, Derecha, Izquierda, Salir, Nada, Deshacer
};
const int MAX = 50;
typedef enum tCasilla{ Libre, Muro, DestinoL, DestinoC, DestinoJ, Jugador, Caja };
struct tSokoban{
	tCasilla tTablero[MAX][MAX];
	int nfilas, ncolumnas, filajugador, columnajugador, cajastotal, cajascolocadas;
};
int menu();
tCasilla CaracterAEnum(char c);
tTecla leerTecla();
void dibujaCasilla(tCasilla	casilla);
void colorFondo(int	color);
bool cargarNivel(std:: ifstream &fichero, tSokoban	&sokoban, int	nivel);

#endif