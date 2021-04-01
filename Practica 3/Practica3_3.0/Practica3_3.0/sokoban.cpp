
//Practica 3. Javier Guzmán Muñoz y Jorge Villarrubia Elvira. Grupo 3. Doble Grado en ING Informática- Matemáticas
#include "Sokoban.h"

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
	std::string nivelbuscado = "Level " + std::to_string(nivel);
	while (!encontrado && !fichero.eof()){
		getline(fichero, linea);
		if (linea == nivelbuscado) encontrado = true;
	}
	if (encontrado){
		bool salir = false;
		sokoban.ncolumnas = 0;
		sokoban.nfilas = 0;
		sokoban.cajastotal = 0;
		sokoban.cajascolocadas = 0;
		do{
			getline(fichero, lineanivel);
			for (int j = 0; j < lineanivel.size(); ++j){
				tCasilla casilla = CaracterAEnum(lineanivel[j]);
				sokoban.tTablero[sokoban.nfilas][j] = casilla;
				if (casilla == Jugador || casilla == DestinoJ){
					sokoban.filajugador = sokoban.nfilas;
					sokoban.columnajugador = j;
				}
				else if (casilla == Caja || casilla == DestinoC){
					++sokoban.cajastotal;
					if (casilla == DestinoC){
						++sokoban.cajascolocadas;
					}
				}
			}
			if (lineanivel.size() > sokoban.ncolumnas) sokoban.ncolumnas = lineanivel.size();
			if (lineanivel == "" || fichero.eof())
				salir = true;
			if (lineanivel != "") ++sokoban.nfilas;
		} while (!salir);
	}
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

	default: { tecla = leerTecla();
	}
	}
	return tecla;
}
tCasilla CaracterAEnum(char c){
	tCasilla casilla;
	switch (c){
	case '#': {
				  casilla = Muro;
	}
		break;
	case ' ': {
				  casilla = Libre;
	}
		break;
	case '.': {
				  casilla = DestinoL;
	}
		break;
	case '$': {
				  casilla = Caja;
	}
		break;
	case '@': {
				  casilla = Jugador;
	}
		break;
	case '*': {
				  casilla = DestinoC;
	}
		break;
	case '+': {
				  casilla = DestinoJ;
	}
	}
	return casilla;
}