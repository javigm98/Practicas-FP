#include "Sokoban.h"
#include <cmath>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
using namespace std;



int menu(){
	int opc;
		cout << "1. Jugar partida." << '\n';
		cout << "0 - Salir." << '\n' << '\n';
		cin >> opc;
		while (opc < 0 || opc > 2){
			cout << "Opcion no valida: ";
			cin >> opc;
		}
		while (cin.fail())
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";
			cin >> opc;
		}
		cin.sync();
		return opc;
}


void colorFondo(int	color)	{
	HANDLE	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void dibujaCasilla(tCasilla	casilla){
	switch (casilla)
	{
	case Libre:{
				   colorFondo(1);
				   cout << "  ";
	} break;
	case Muro:{
				  colorFondo(2);
				  cout << "  ";
	}break;
	case DestinoL: {
					   colorFondo(4);
					   cout << "..";
	}break;
	case DestinoC:{
					  colorFondo(8);
					  cout << "()";
	}break;
	case DestinoJ:{
					  colorFondo(14);
					  cout << "00";
	}break;
	case Jugador:{
					 colorFondo(14);
					 cout << "00";
	}break;
	case Caja:{
				  colorFondo(8);
				  cout << "()";
	}

	}
}

bool cargarNivel(ifstream &fichero, tSokoban &sokoban, int	nivel){
	string linea, lineanivel;
	bool encontrado = false;

	while (!encontrado && !fichero.eof()){
		getline(fichero, linea);
		if (linea == "Level " + to_string(nivel)) encontrado = true;
	}
	bool salir = false;
	sokoban.ncolumnas = 0;
	sokoban.nfilas = 0;
	sokoban.cajastotal = 0;
	sokoban.cajascolocadas = 0;
	do{
		getline(fichero, lineanivel);
		for (int j = 0; j < lineanivel.size(); ++j){
			sokoban.tTablero[sokoban.nfilas][j] = CaracterAEnum(lineanivel[j]);
			if (CaracterAEnum(lineanivel[j]) == Jugador || CaracterAEnum(lineanivel[j]) == DestinoJ){
				sokoban.filajugador = sokoban.nfilas;
				sokoban.columnajugador = j;
			}
			else if (CaracterAEnum(lineanivel[j]) == Caja || CaracterAEnum(lineanivel[j]) == DestinoC){
				++sokoban.cajastotal;
				if (CaracterAEnum(lineanivel[j]) == DestinoC){
					++sokoban.cajascolocadas;
				}
			}
		}
		if (lineanivel.size() > sokoban.ncolumnas) sokoban.ncolumnas = lineanivel.size();
		if (lineanivel == "" || fichero.eof()) salir = true;
		++sokoban.nfilas;
	} while (!salir);



	return encontrado;
}

tTecla leerTecla(){
	int dir;
	tTecla tecla;
	cin.sync();
	dir = _getch();
	if (dir == 0xe0){
		dir = _getch();
	}
	switch (dir)
	{
	case 27:{
				tecla = Salir;
	}
		break;
	case 72:{
				tecla = Arriba;
	} break;
	case 80:{
				tecla = Abajo;
	} break;
	case 77:{
				tecla = Derecha;
	} break;
	case 75:{
				tecla = Izquierda;
	} break;
	case 100:{
				tecla = Deshacer;
	} break;
	case 68: {
				tecla = Deshacer;
	} break;

	default: { tecla = Nada;
	}
	}
	return tecla;
}