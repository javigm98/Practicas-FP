#include "clavevalor.h"
#include "indices.h"

bool busquedaBinaria(tIndicePalabras const&	l, std::string const& s, int & pos){
	int ini = 0, fin = l.tamano, mitad;
	bool encontrado = false;
	while (ini < fin && !encontrado) {
		mitad = (ini + fin - 1) / 2; // divisi�n entera
		if (s < l.array[mitad].clave) fin = mitad;
		else if (l.array[mitad].clave < s) ini = mitad + 1;
		else encontrado = true;
	}
	if (encontrado) pos = mitad; // en la posici�n mitad
	else pos = ini;  // No encontrado, le corresponde la posici�n ini (=fin)
	return encontrado;
}

void insertarOrdenado(tIndicePalabras & idx, std::string const& palabra, std::string const& nombreArchivo){
	int pos = 0, a = 0;
	if (busquedaBinaria(idx, palabra, pos)){
		if (!buscar(idx.array[pos].valor, nombreArchivo, a)) insertar(idx.array[pos].valor, nombreArchivo);
	}
	else if (!busquedaBinaria(idx, palabra, pos)){
		desplazarDerecha(idx, pos);
		idx.array[pos].clave = palabra;
		inicializaListaVacia(idx.array[pos].valor);
		insertar(idx.array[pos].valor, nombreArchivo);
	}
}
void desplazarDerecha(tIndicePalabras & idx, int pos){
	for (int i = idx.tamano; i > pos; --i)
		idx.array[i] = idx.array[i - 1];
	idx.tamano++;
}

void inicializaListaVacia(tListaCadenas<std::string> & lista){
	lista.tamano = 0;
}