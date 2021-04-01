#include "indices.h"
#include "matriz.h"

void crearTabla(tIndicePalabras	& tabla, const std::string &archivoInicial){
	tListaCadenas<std::string> Visitados, NoVisitados, Totales;
	tMatriz L;
	inicializaListaVacia(Visitados);
	inicializaListaVacia(NoVisitados);
	inicializaListaVacia(Totales);
	insertar(NoVisitados, archivoInicial);
	insertar(Totales, archivoInicial);
	L = matrizConstante(0.0, 1);
	while (NoVisitados.tamano > 0){
		int j;
		std::string nombrearchivo = NoVisitados.array[NoVisitados.tamano - 1];
		bool busca = buscar(Totales, nombrearchivo, j);
		insertar(Visitados, nombrearchivo);
		--NoVisitados.tamano;
		rellenaTabla(tabla, nombrearchivo, Visitados, NoVisitados, Totales, L, j);
	}
	normalizaL(L);
}
void inicializaIndiceVacio(tIndicePalabras & indice){
	indice.tamano = 0;
}

/*void LeerArchivo(std::ifstream & archivo, std::stringstream & ss){
	while (!archivo.eof()){
		std::string palabra;
		getline(archivo, palabra);
		ss << palabra << " ";
	}
}*/

void rellenaTabla(tIndicePalabras & indice, std::string nombrearchivo, tListaCadenas<std::string> & visitados, tListaCadenas<std::string> & NoVisistados, tListaCadenas<std::string> & Totales, tMatriz & L, int j){
	std::string aux;
	std::ifstream archivo;
	archivo.open(nombrearchivo);
	while (!archivo.eof()){
		int pos = 0;
		std::string palabra;
		getline(archivo, palabra);
		std::stringstream ss;
		ss << palabra;
		ss >> aux;
		while (ss){
			std::transform(aux.begin(), aux.end(), aux.begin(), std::tolower);
			if (acabaEnPunt(aux)) aux.pop_back();
			if (!esEnlace(aux)) insertarOrdenado(indice, aux, nombrearchivo);
			else{
				int i = 0;
				aux = elimina1erCaracter(aux);
				aux.pop_back();
				//if (!buscar(visitados, aux, pos) && !buscar(NoVisistados, aux, pos)) insertar(NoVisistados, aux);
				if (buscar(Totales, aux, i)) L.matriz[j][i] = 1.0;
				else {
					insertar(NoVisistados, aux);
					insertar(Totales, aux);
					AmpliaMatriz1(L);
					L.matriz[j][L.tam - 1] = 1.0;
				}
			}
			ss >> aux;
		}
	}
	archivo.close();
}

bool esEnlace(std::string palabra){
	if (palabra[0] == '<' && palabra[palabra.size() - 1] == '>')
		return true;
	else return false;
}
bool acabaEnPunt(std::string palabra){
	if (!std::isalnum(palabra[palabra.size() - 1]) && palabra[palabra.size() - 1] != '>') return true;
	else return false;
}
std::string elimina1erCaracter(std::string palabra){
	std::string palabra2;
	for (int i = 0; i < palabra.size() - 1; ++i)
		palabra2.push_back(palabra[i + 1]);
	return palabra2;
}
bool CompArchivoINI(std::string nombrearchivo){
	std::ifstream archivo;
	archivo.open(nombrearchivo);
	if (archivo.is_open()){
		archivo.close();
		return true;
	}
	else return false;
}

void AmpliaMatriz1(tMatriz & L){
	++L.tam;
	for (int i = 0; i < L.tam; ++i){
		L.matriz[i][L.tam - 1] = 0.0;
		L.matriz[L.tam - 1][i] = 0.0;
	}
}

tVector CalculoPageRank()









