#include "indices.h"

int main(){
	tIndicePalabras indice;
	inicializaIndiceVacio(indice);
	std::string buscada;
	std::string archivoinicial;
	std::cout << "Introduzca el fichero a partir del cual se creara el indice: ";
	std::cin >> archivoinicial;
	std::cout << "Cargando...";
	while (!CompArchivoINI(archivoinicial)){
		std::cout << "[INCORRECTO]. Introduzca otro archivo: ";
		std::cin >> archivoinicial;
		std::cout << "Cargando...";
	}
	std::cout << "[CORRECTO]" << '\n';
	std::cout << "Creando tablas...";
	crearTabla(indice, archivoinicial);
	std::cout << "[CORRECTO]" << '\n' << '\n';
	std::cout << "Se han encontrado " << indice.tamano << " palabras\n";
	std::cout << "La informacion ha sido caragada. Puede comenzar con las busquedas." << '\n';
	int pos = 0;
	std::cout << "Introduzca una palabra ('fin' para acabar): ";
	std::cin >> buscada;
	std::cout << '\n';
	while (buscada != "fin"){
		if (!busquedaBinaria(indice, buscada, pos)) std::cout << "No se han encontrado resultados para '" << buscada << "'." << '\n' <<'\n';
		else if (busquedaBinaria(indice, buscada, pos)){
			for (int i = 0; i < indice.array[pos].valor.tamano; ++i)
				std::cout << "Encontrada en: " << indice.array[pos].valor.array[i] << '\n' << '\n';
			}
		std::cout << "Introduzca una palabra ('fin' para acabar): ";
		std::cin >> buscada;
		std::cout << '\n';
		}
	std::cout << "Gracias por usar nuestro buscador " << '\n';
	return 0;
}