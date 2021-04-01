//Practica 3. Javier Guzmán Muñoz y Jorge Villarrubia Elvira. Grupo 3. Doble Grado en ING Informática- Matemáticas
#include <iostream>
#include "Sokoban.h"
#include <string>
#include <fstream>
#include <conio.h>
#include <iomanip>


#ifndef juego_h
#define juego_h
const int MAXH = 10;
const int MAXE = 100;
const int MAX_IND = 9;
struct tPartida{
	std::string nombrearchivo;
	int nivel, movimientos;
};
typedef tPartida tExitos[MAXE];
struct tHistoria{
	tSokoban array[MAXH];
	int cont, ind;
};
struct tInfo{
	std::string nombrejugador;
	tExitos exitos;
	int cont;
};
struct tJuego{
	tHistoria historia;
	tSokoban estadoTablero;
	int numMovimientos;
	std::string nFichero;
	int nivel;
};

int menu();
void guardarHistorial(tInfo const& jugador);

/*Cuando el usuario introduce la opción salir, guarda en un fichero con el nombre que ha indicado al inicio del programalos
niveles superados por el jugador siempre y cuando no hayan sido superados previamente
o se hayan superado en menos movimientos insertando de manera ordenada los nuevos niveles que se superan*/

void actualizaHistorial(tInfo &jugador, tPartida const& partida);

/* Cuando el usuario supera un nivel, actualiza tInfo con la información de tPartida superado insertando de manera ordenada los nuevos niveles que se superan o actualizando los queya existen se han superado menos movimientos */

bool deshacerMovimiento(tJuego	&juego);
bool bloqueado(const	tJuego	&juego);
void hacerMovimiento(tJuego	&juego, tTecla tecla);
bool cargarJuego(tJuego	& juego);
void dibujar(const tJuego & juego);
void inicializa(tJuego &juego);
tTecla leerTecla();
bool operator== (tPartida const & p1, tPartida const & p2);
bool operator< (tPartida const & p1, tPartida const & p2);
void visualiza(tInfo const&jugador);
void asignaPos(tJuego & juego, tCasilla asig1, tCasilla asig2, tCasilla asig3, int i, int j, bool mirar2mas);
#endif