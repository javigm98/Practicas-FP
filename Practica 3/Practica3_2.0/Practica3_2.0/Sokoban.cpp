//Practica 3. Javier Guzmán Muñoz y Jorge Villarrubia Elvira. Grupo 3. Doble Grado en ING Informática- Matemáticas
#include "Sokoban.h"



int menu(){
	int opc;
		std::cout << "1. Jugar partida." << '\n';
		std::cout << "2. Visualizar informacion del jugador" << '\n';
		std::cout << "0. Salir." << '\n' << '\n';

		std::cin >> opc;
		while (opc < 0 || opc > 2){
			std::cout << "Opcion no valida: ";
			std::cin >> opc;
		}
		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.sync();
			std::cout << "Dame un entero: ";
			std::cin >> opc;
		}
		std::cin.sync();
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
				   std::cout << "  ";
	} break;
	case Muro:{
				  colorFondo(2);
				  std::cout << "  ";
	}break;
	case DestinoL: {
					   colorFondo(4);
					   std::cout << "..";
	}break;
	case DestinoC:{
					  colorFondo(11);
					  std::cout << "()";
	}break;
	case DestinoJ:{
					  colorFondo(14);
					  std::cout << "00";
	}break;
	case Jugador:{
					 colorFondo(14);
					 std::cout << "00";
	}break;
	case Caja:{
				  colorFondo(8);
				  std::cout << "()";
	}

	}
}

bool cargarNivel(std::ifstream &fichero, tSokoban &sokoban, int	nivel){
	std::string linea, lineanivel;
	bool encontrado = false;

	while (!encontrado && !fichero.eof()){
		getline(fichero, linea);
		if (linea == "Level " + std::to_string(nivel)) encontrado = true;
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
	std::cin.sync();
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