#include <iostream>
#include "juego.h"
#include "Sokoban.h"
int main(){
	int opc;
	bool exito, Bloqueado, movido, deshecho;
	tTecla tecla;
	tJuego juego;
	opc = menu();
	while (opc != 0){
		int ind = 0;
		switch (opc)
		{
		case 1:{
				   inicializa(juego);
				   exito = cargarJuego(juego);
				   if (exito){
					   dibujar(juego);
					   juego.historia.cont = 0;
					   tecla = leerTecla();
					   if (tecla == Deshacer) std::cout << "Haga un primer movimiento" << '\n';
					   while (tecla == Nada) tecla = leerTecla();
					   while (tecla != Salir && juego.estadoTablero.cajascolocadas < juego.estadoTablero.cajastotal){
	
						   if (tecla != Deshacer) {
							   hacerMovimiento(juego, tecla, ind); // Decirle a Javi que es porque daba error
							   dibujar(juego);
							   Bloqueado = bloqueado(juego);

							   if (Bloqueado) std::cout << "Bloqueado" << '\n';
						   }
						   else {
								   deshecho = deshacerMovimiento(juego, ind);  // Pensar como hacer para que no lo haga más de 10 veces
								   if (deshecho) --juego.historia.cont;
							   dibujar(juego);
						   }
						   if (juego.estadoTablero.cajascolocadas < juego.estadoTablero.cajastotal) tecla = leerTecla();
						   while (tecla == Nada) tecla = leerTecla();
					   }
						  
					   if (juego.estadoTablero.cajascolocadas == juego.estadoTablero.cajastotal){
						   std::cout << "¡¡Nivel superado!!" << '\n';
					   }
				   }
				   else{
					   std::cout << "No se ha podido cargar el juego" << '\n';
				   }
		} break;
		case 2:{

		}
		}
		opc = menu();
	}


	return 0;
}