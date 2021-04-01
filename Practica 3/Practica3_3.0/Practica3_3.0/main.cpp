//Practica 3. Javier Guzmán Muñoz y Jorge Villarrubia Elvira. Grupo 3. Doble Grado en ING Informática- Matemáticas
#include "juego.h"
#include "Sokoban.h"
int main(){
	int opc;
	tInfo jugador;
	tPartida partida;
	std::ifstream archivo;
	std::ofstream archivosalida;
	bool exito, Bloqueado, movido, deshecho;
	tTecla tecla;
	tJuego juego;
	std::cout << "Nombre del jugador: ";
	std::cin >> jugador.nombrejugador;
	archivo.open(jugador.nombrejugador + ".txt");
	jugador.cont = 0;
	if (archivo.is_open()){
		while (!archivo.eof()){
			archivo >> jugador.exitos[jugador.cont].nombrearchivo >> jugador.exitos[jugador.cont].nivel >> jugador.exitos[jugador.cont].movimientos;
			jugador.cont++;
		}
		archivo.close();
	}
	opc = menu();
	while (opc != 0){
		juego.historia.ind = 0;
		switch (opc)
		{
		case 1:{
				   inicializa(juego);
				   exito = cargarJuego(juego);
				   if (exito){
					   dibujar(juego);
					   juego.historia.cont = 0;
					   tecla = leerTecla();
					   while (tecla != Salir && juego.estadoTablero.cajascolocadas < juego.estadoTablero.cajastotal){

						   if (tecla != Deshacer) {
							   hacerMovimiento(juego, tecla); // Decirle a Javi que es porque daba error
							   dibujar(juego);

						   }
						   else {
							   deshecho = deshacerMovimiento(juego);  // Pensar como hacer para que no lo haga más de 10 veces
							   if (deshecho) --juego.historia.cont;
							   dibujar(juego);
						   }
						   Bloqueado = bloqueado(juego);

						   if (Bloqueado) std::cout << "Bloqueado" << '\n';
						   if (juego.estadoTablero.cajascolocadas < juego.estadoTablero.cajastotal) tecla = leerTecla();
					   }

					   if (juego.estadoTablero.cajascolocadas == juego.estadoTablero.cajastotal){
						   std::cout << "¡¡Nivel superado!!" << '\n';
						   partida.nombrearchivo = juego.nFichero;
						   partida.nivel = juego.nivel;
						   partida.movimientos = juego.numMovimientos;
						   actualizaHistorial(jugador, partida);
					   }
				   }
				   else{
					   std::cout << "No se ha podido cargar el juego" << '\n';
				   }
		} break;
		case 2:{
				   visualiza(jugador);
		}
		}
		opc = menu();
	}

	guardarHistorial(jugador);

	return 0;
}