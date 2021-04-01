#include "listaCadenas.h"
#ifndef clavevalor_h
#define clavevalor_h

const int MAX_INDICE = 200;
struct tClaveValor{
	std::string clave;
	tListaCadenas<std::string> valor;
};
struct tIndicePalabras{
	int tamano;
	tClaveValor array[MAX_INDICE];
};
bool busquedaBinaria(tIndicePalabras const&	l, std::string const& s, int & pos);
void insertarOrdenado(tIndicePalabras & idx, std::string const& palabra, std::string const& nombreArchivo);
void desplazarDerecha(tIndicePalabras & idx, int pos);
void inicializaListaVacia(tListaCadenas<std::string> & lista);




#endif