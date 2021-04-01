//Practica 3. Javier Guzm�n Mu�oz y Jorge Villarrubia Elvira. Grupo 3. Doble Grado en ING Inform�tica- Matem�ticas

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

#ifndef sokoban_h
#define sokoban_h

enum tTecla{
	Arriba, Abajo, Derecha, Izquierda, Salir, Nada, Deshacer
};
const int MAX = 50;
enum tCasilla{ Libre, Muro, DestinoL, DestinoC, DestinoJ, Jugador, Caja };
struct tSokoban{
	tCasilla tTablero[MAX][MAX];
	int nfilas, ncolumnas, filajugador, columnajugador, cajastotal, cajascolocadas;
};
tCasilla CaracterAEnum(char c);
/*Con esta funci�n se asigna a cada car�cter le�do de un fichero de texto su correspondiente tCasilla*/
tTecla leerTecla();
//Esta funci�n ya esta comentada en juego.h, copia aqu� el comentario y borrala de all� que es aqu� donde le corresponde estar!!!!!!!!!!!!
//Su implementaci�n si que est� en sokoban.cpp, por lo que lo unico que tienes que borrar es el prototi`po de juego.h!!!!!!!
void dibujaCasilla(tCasilla	casilla);
/*Mediante un switch imprimimos por pantalla el color de fondo y el caracter correspondiente a cada casilla del tablero*/
void colorFondo(int	color);
/*Cambia el color del fondo de la consola cuando se imprime un caracter enn funci�n de un valor entero que indica el color deseado*/
bool cargarNivel(std::ifstream &fichero, tSokoban	&sokoban, int	nivel);
/*Dados un fichero abierto y un numero de nivel, va leyendo l�neas del fichero hasta que se encuentra la expresi�n 'Level' y el n�mero del nivel indicado. 
Una vez encontrado el encabezado del nivel contin�a cargando l�neas del fichero y guardando uno a uno los tCasilla correspondientes a los caracteres leidos 
(mediante la llamada a la funci�n CaracterAEnum) en la matriz tTablero, acabando cuando encuentra la primera l�nea en blanco. 
La funci�n devuelve un valor booleano que indica si se ha encontrado o no el nivel buscado tras recorrerse todo el fichero en caso negativo. */
#endif
//en el main.cpp acuerdate de borrar el #include <iostream>, que no es necesario ya que esta declarado en juego.h y juego.cpp!!!!!!!!!!!!!!!!!