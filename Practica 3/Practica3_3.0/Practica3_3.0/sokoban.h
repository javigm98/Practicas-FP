//Practica 3. Javier Guzmán Muñoz y Jorge Villarrubia Elvira. Grupo 3. Doble Grado en ING Informática- Matemáticas

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
/*Con esta función se asigna a cada carácter leído de un fichero de texto su correspondiente tCasilla*/
tTecla leerTecla();
//Esta función ya esta comentada en juego.h, copia aquí el comentario y borrala de allí que es aquí donde le corresponde estar!!!!!!!!!!!!
//Su implementación si que está en sokoban.cpp, por lo que lo unico que tienes que borrar es el prototi`po de juego.h!!!!!!!
void dibujaCasilla(tCasilla	casilla);
/*Mediante un switch imprimimos por pantalla el color de fondo y el caracter correspondiente a cada casilla del tablero*/
void colorFondo(int	color);
/*Cambia el color del fondo de la consola cuando se imprime un caracter enn función de un valor entero que indica el color deseado*/
bool cargarNivel(std::ifstream &fichero, tSokoban	&sokoban, int	nivel);
/*Dados un fichero abierto y un numero de nivel, va leyendo líneas del fichero hasta que se encuentra la expresión 'Level' y el número del nivel indicado. 
Una vez encontrado el encabezado del nivel continúa cargando lìneas del fichero y guardando uno a uno los tCasilla correspondientes a los caracteres leidos 
(mediante la llamada a la función CaracterAEnum) en la matriz tTablero, acabando cuando encuentra la primera línea en blanco. 
La función devuelve un valor booleano que indica si se ha encontrado o no el nivel buscado tras recorrerse todo el fichero en caso negativo. */
#endif
//en el main.cpp acuerdate de borrar el #include <iostream>, que no es necesario ya que esta declarado en juego.h y juego.cpp!!!!!!!!!!!!!!!!!