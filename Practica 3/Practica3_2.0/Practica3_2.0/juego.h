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
struct tPartida{
	std::string nombrearchivo;
	int nivel, movimientos;
};
typedef tPartida tExitos[MAXE];
struct tHistoria{
	tSokoban array[MAXH];
	int cont;
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

void guardarHistorial(std::ofstream & archivo, tInfo const& jugador);
void actualizaHistorial(tInfo &jugador, tPartida const& partida);
bool deshacerMovimiento(tJuego	&juego, int &ind);
bool bloqueado(const	tJuego	&juego);
void hacerMovimiento(tJuego	&juego, tTecla tecla, int &ind);
bool cargarJuego(tJuego	& juego);
void dibujar(const tJuego & juego);
void inicializa(tJuego &juego);
tTecla leerTecla();
bool operator== (tPartida const & p1, tPartida const & p2);
bool operator< (tPartida const & p1, tPartida const & p2);
void visualiza(tInfo const&jugador);
#endif