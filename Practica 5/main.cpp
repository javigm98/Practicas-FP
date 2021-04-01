//main.cpp
//Javier Guzmán Muñoz. Doble Grado en Ingeniería Informática - Matemáticas.
#include "indices.h"
#include "checkML.h"

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tMatriz L;
	tVector a;
	tListaCadenas <std::string> Totales;
	Totales.capacidad = TAM_INI;
	Totales.vector = new std::string[Totales.capacidad];
	tListaCadenas <tFichero> paginas;
	tIndicePalabras indice;
	indice.capacidad = TAM_INI;
	inicializaIndiceVacio(indice);
	indice.array = new tClaveValor[indice.capacidad];
	std::string buscada;
	std::string archivoinicial;
	std::cout << "........................................\n";
	std::cout << ":BIENVENIDO A JOOGLE (by Javier Guzman):\n";
	std::cout << ":......................................:\n\n";
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
	crearTabla(indice, archivoinicial, Totales, L, a); //Crea la tabla, la lista de Totales y L y a para el calculo del PR
	std::cout << "[CORRECTO]" << '\n' << '\n';
	std::cout << "Se han encontrado " << indice.tamano << " palabras\n";
	tVector PageRank = CalculoPageRank(a, L); //Se calcula el PageRank de todas las paginas.
	std::cout << "La informacion ha sido caragada. Puede comenzar con las busquedas." << '\n';
	std::cout << "Introduzca una palabra ('fin' para acabar): ";
	std::cin >> buscada;
	std::transform(buscada.begin(), buscada.end(), buscada.begin(), std::tolower); //Siempre se trabaja con minusculas
	std::cout << '\n';
	while (buscada != "fin"){
		if (PaginasdePalabra(indice, buscada, PageRank, Totales, paginas)) {
			OrdenarPorPageRank(paginas);
			for (int i = 0; i < paginas.tamano; ++i) {
				std::cout << "Encontrada en: " << paginas.vector[i].nombre << ". Importancia: " << std::fixed << std::setprecision(2) << paginas.vector[i].pageRank << ".\n\n";
			}
			delete[] paginas.vector;
			paginas.vector = nullptr;
		}
		else std::cout << "No se han encontrado resultados para '" << buscada << "'.\n\n";
		std::cout << "Introduzca una palabra ('fin' para acabar): ";
		std::cin >> buscada;
		std::transform(buscada.begin(), buscada.end(), buscada.begin(), std::tolower);
		std::cout << '\n';
		}
	std::cout << "Gracias por usar nuestro buscador JOOGLE. " << '\n';
	delete[] Totales.vector;
	Totales.vector = nullptr;
	for (int i = 0; i < indice.tamano; ++i){
		delete[] indice.array[i].valor.vector;
		indice.array[i].valor.vector = nullptr;
	}
	delete[] indice.array;
	indice.array = nullptr;
	return 0;
}