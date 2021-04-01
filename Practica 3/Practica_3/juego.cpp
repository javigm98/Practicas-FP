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