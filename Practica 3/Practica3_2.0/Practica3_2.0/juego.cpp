//Practica 3. Javier Guzmán Muñoz y Jorge Villarrubia Elvira. Grupo 3. Doble Grado en ING Informática- Matemáticas
#include "juego.h"


bool deshacerMovimiento(tJuego	&juego, int &ind){ // Decirle lo que he pasado como parametro y el por qué
	bool deshecho;
	if (ind != 0 && juego.historia.cont > 0){ 
		juego.estadoTablero = juego.historia.array[ind - 1];
		ind--;
		--juego.numMovimientos;
		deshecho = true;
	}
	else if (ind == 0 && juego.historia.cont > 0){
		juego.estadoTablero = juego.historia.array[9];
		ind = 9;
		--juego.numMovimientos;
		deshecho = true;
	}
	else {
		deshecho = false;
	}
	return deshecho;
}
bool operator== (tPartida const & p1, tPartida const & p2){
	bool igual = false;
	if (p1.nombrearchivo == p2.nombrearchivo && p1.nivel == p2.nivel) igual = true;

	return igual;
}

bool operator< (tPartida const & p1, tPartida const & p2){
	bool menor = false;
	if ((p1.nombrearchivo < p2.nombrearchivo) || (p1.nombrearchivo == p2.nombrearchivo && p1.nivel < p2.nivel)) menor = true;
	return menor;
}

void visualiza(tInfo const&jugador){
	if (jugador.cont > 0){
		std::cout << std::setw(20) << "FICHERO" << std::setw(6) << "NIVEL" << std::setw(5) << "MOVS" << '\n';
		for (int i = 0; i < jugador.cont; ++i) std::cout << std::setw(20) << jugador.exitos[i].nombrearchivo << std::setw(6) << jugador.exitos[i].nivel << std::setw(5) << jugador.exitos[i].movimientos << '\n';
	}
	else std::cout << "Aun no has superado ningun nivel!" << '\n';
}


bool bloqueado(const tJuego	&juego){
	bool bloqueado = false;
	int cajasencontradas = 0, i = 0;
	while (!bloqueado && juego.estadoTablero.cajastotal - juego.estadoTablero.cajascolocadas > cajasencontradas){
		int j = 0;
		while (!bloqueado && j < juego.estadoTablero.ncolumnas){
			if (juego.estadoTablero.tTablero[i][j] == Caja){
				++cajasencontradas;
				if ((juego.estadoTablero.tTablero[i - 1][j] == Muro || juego.estadoTablero.tTablero[i + 1][j] == Muro)){
					if ((juego.estadoTablero.tTablero[i][j - 1] == Muro || juego.estadoTablero.tTablero[i][j + 1] == Muro)) bloqueado = true;
				}
			}
			++j;
		}
		++i;
	}


	return bloqueado;
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



void hacerMovimiento(tJuego	&juego, tTecla tecla, int &ind){

	int i, j;
	switch (tecla)
	{
	case Arriba:{
					i = -1;
					j = 0;
	}
		break;
	case Abajo:{
				   i = 1;
				   j = 0;
	}                                      // Contemplar caso salir y nada en el main
		break;
	case Derecha:{
					 i = 0;
					 j = 1;
	}
		break;
	case Izquierda:{
					   i = 0;
					   j = -1;
	} break;

	}
	if (juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] == Jugador || juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] == DestinoJ){
		switch (juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador])
		{
		case Jugador: {
					  switch (juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j])
					  {
					  case Caja:{

								   switch (juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j])
								   {
								   case Libre:{
												juego.historia.array[ind] = juego.estadoTablero;
												ind = (ind + 1) % MAXH;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j] = Caja;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = Libre;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = Jugador;
												juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
												juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
												juego.numMovimientos++;
								   } break;
								   case DestinoL:{
												juego.historia.array[ind] = juego.estadoTablero;
												ind = (ind + 1) % MAXH;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j] = DestinoC;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = Libre;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = Jugador;
												juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
												juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
												juego.estadoTablero.cajascolocadas++;
												juego.numMovimientos++;
										
								   } break;
								   default:{}
									 
								   }
								   
					  }
						  break;
					  case DestinoC:{
								   switch (juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j])
								   {
								   case Libre:{
												juego.historia.array[ind] = juego.estadoTablero;
												ind = (ind + 1) % MAXH;
												if (juego.historia.cont < MAXH) ++juego.historia.cont;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j] = Caja;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = Libre;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = DestinoJ;
												juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
												juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
												juego.estadoTablero.cajascolocadas--;
												juego.numMovimientos++;
											
								   } break;
								   case DestinoL:{
												juego.historia.array[ind] = juego.estadoTablero;
												ind = (ind + 1) % MAXH;
												if (juego.historia.cont < MAXH) ++juego.historia.cont;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j] = DestinoC;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = Libre;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = DestinoJ;
												juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
												juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
											
												juego.numMovimientos++;
								   } break;
								   default:{}
								
								   }
								   
					  }
						  break;
					  case Libre:{
								   juego.historia.array[ind] = juego.estadoTablero;
								   ind = (ind + 1) % MAXH;
								   if (juego.historia.cont < MAXH) ++juego.historia.cont;
								   juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = Libre;
								   juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = Jugador;
								   juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
								   juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
								   juego.numMovimientos++;
								
					  }
						  break;
					  case DestinoL:{
								   juego.historia.array[ind] = juego.estadoTablero;
								   ind = (ind + 1) % MAXH;
								   if (juego.historia.cont < MAXH) ++juego.historia.cont;
								   juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = Libre;
								   juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = DestinoJ;
								   juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
								   juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
								   juego.numMovimientos++;
								
					  }
						  break;
					  default:{}
					  }


		} break;
		case DestinoJ: {
					  switch (juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j])
					  {
					  case Caja:{
								   switch (juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j])
								   {
								   case Libre:{
												juego.historia.array[ind] = juego.estadoTablero;
												ind = (ind + 1) % MAXH;
												if (juego.historia.cont < MAXH) ++juego.historia.cont;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j] = Caja;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = DestinoL;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = Jugador;
												juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
												juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
												juego.numMovimientos++;
										
								   } break;
								   case DestinoL:{
												juego.historia.array[ind] = juego.estadoTablero;
												ind = (ind + 1) % MAXH;
												if (juego.historia.cont < MAXH) ++juego.historia.cont;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j] = DestinoC;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = DestinoL;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = Jugador;
												juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
												juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
												juego.estadoTablero.cajascolocadas++;
												juego.numMovimientos++;
										
								   } break;
								   default:{}
									   
								   }
					  }
						  break;
					  case DestinoC:{
								   switch (juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j])
								   {
								   case Libre:{
												juego.historia.array[ind] = juego.estadoTablero;
												ind = (ind + 1) % MAXH;
												if (juego.historia.cont < MAXH) ++juego.historia.cont;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j] = Caja;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = DestinoL;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = DestinoJ;
												juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
												juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
												juego.estadoTablero.cajascolocadas--;
												juego.numMovimientos++;
											
								   } break;
								   case DestinoL:{
												juego.historia.array[ind] = juego.estadoTablero;
												ind = (ind + 1) % MAXH;
												if (juego.historia.cont < MAXH) ++juego.historia.cont;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + 2 * i][juego.estadoTablero.columnajugador + 2 * j] = DestinoC;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = DestinoL;
												juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = DestinoJ;
												juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
												juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
												juego.numMovimientos++;
											
								   } break;
								   default:{}
									 
								   }
								   
					  } break;
					  case Libre:{
								   juego.historia.array[ind] = juego.estadoTablero;
								   ind = (ind + 1) % MAXH;
								   if (juego.historia.cont < MAXH) ++juego.historia.cont;
								   juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = DestinoL;
								   juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = Jugador;
								   juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
								   juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
								   juego.numMovimientos++;
								 
					  } break;
					  case DestinoL:{
								   juego.historia.array[ind] = juego.estadoTablero;
								   ind = (ind + 1) % MAXH;
								   if (juego.historia.cont < MAXH) ++juego.historia.cont;
								   juego.estadoTablero.tTablero[juego.estadoTablero.filajugador][juego.estadoTablero.columnajugador] = DestinoL;
								   juego.estadoTablero.tTablero[juego.estadoTablero.filajugador + i][juego.estadoTablero.columnajugador + j] = DestinoJ;
								   juego.estadoTablero.filajugador = juego.estadoTablero.filajugador + i;
								   juego.estadoTablero.columnajugador = juego.estadoTablero.columnajugador + j;
								   juego.numMovimientos++;
								
					  } break;
					  default:{}
					  }
		}
		}
	}
	

}

int encontrarPartida(tInfo &jugador, tPartida const& partida, bool &encontrado){
	int ini = 0, fin = jugador.cont, mitad, pos;
	encontrado = false;
	while (ini < fin && !encontrado){
		mitad = (ini + fin - 1) / 2;
		if (partida == jugador.exitos[mitad]) encontrado = true;
		else if (partida < jugador.exitos[mitad]) fin = mitad;
		else ini = mitad + 1;
	}
	if (encontrado) pos = mitad;
	else pos = ini;
	return pos;
}

void guardarHistorial(std::ofstream & archivo, tInfo const& jugador){
	if (archivo.is_open()){
		for (int i = 0; i < jugador.cont; ++i) {
			archivo << jugador.exitos[i].nombrearchivo << " " << jugador.exitos[i].nivel << " " << jugador.exitos[i].movimientos;
			if (i < jugador.cont - 1) archivo << '\n';
		}
		archivo.close();
	}
	else std:: cout << "No se puede crear el archivo" << '\n';
}


void actualizaHistorial(tInfo &jugador, tPartida const& partida){
	bool encontrado;
	int pos;
   pos =  encontrarPartida(jugador, partida, encontrado);
   if (encontrado && jugador.exitos[pos].movimientos > partida.movimientos) jugador.exitos[pos].movimientos = partida.movimientos;
   else if (!encontrado){
	   jugador.cont++;
	   for (int i = jugador.cont - 1; i > pos; --i){
		   jugador.exitos[i] = jugador.exitos[i - 1];
	   }
	   jugador.exitos[pos] = partida;
   }
}

void dibujar(const tJuego & juego){
	system("cls");
	tCasilla casilla;
	std::cout << "Fichero: " << juego.nFichero << " " << "Nivel: " << juego.nivel << std::endl;
	for (int i = 0; i < juego.estadoTablero.nfilas -1; ++i){
		for (int j = 0; j < juego.estadoTablero.ncolumnas; ++j){
			casilla = juego.estadoTablero.tTablero[i][j];
			dibujaCasilla(casilla);
		}
		std::cout << std::endl;
	}
	colorFondo(0);
	std::cout << "Numero de movimientos: " << juego.numMovimientos << std::endl;
}

void inicializa(tJuego &juego){
	for (int i = 0; i < MAX; ++i)
	for (int j = 0; j < MAX; ++j)
		juego.estadoTablero.tTablero[i][j] = Libre;
	juego.numMovimientos = 0;
}

bool cargarJuego(tJuego	& juego){
	bool cargado;
	std::ifstream archivo;
	std::cout << "Introduzca el nombre del archivo desde el que desea cargar los datos: ";
	std::cin >> juego.nFichero;
	std::cout << "Introduzca el nivel en el que desea jugar: ";
	std::cin >> juego.nivel;
	archivo.open(juego.nFichero);
	if (archivo.is_open()){
		cargado = cargarNivel(archivo, juego.estadoTablero, juego.nivel);
		archivo.close();
	}
	else{
		std::cout << "No se ha podido abrir el archivo " << juego.nFichero << std::endl;
		cargado = false;
	}
	return cargado;
}