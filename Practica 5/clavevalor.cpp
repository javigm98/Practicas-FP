//clavevalor.cpp
//Javier Guzmán Muñoz. Doble Grado en Ingeniería Informática - Matemáticas.
#include "clavevalor.h"
#include "indices.h"
#include "checkML.h"

bool busquedaBinaria(tIndicePalabras const&	l, std::string const& s, int & pos){
	return BusquedaRec(l, s, 0, l.tamano, pos);
}

void insertarOrdenado(tIndicePalabras & idx, std::string const& palabra, std::string const& nombreArchivo){
	int pos = 0, a = 0;
		if (busquedaBinaria(idx, palabra, pos)){
			if (!buscar(idx.array[pos].valor, nombreArchivo, a)) insertar(idx.array[pos].valor, nombreArchivo);
		}
		else{
			desplazarDerecha(idx, pos);
			idx.array[pos].valor.capacidad = TAM_INI;
			idx.array[pos].valor.vector = new std::string[TAM_INI];
			idx.array[pos].clave = palabra;
			inicializaListaVacia(idx.array[pos].valor);
			insertar(idx.array[pos].valor, nombreArchivo);
		}
}
void desplazarDerecha(tIndicePalabras & idx, int pos){
	if (idx.tamano == idx.capacidad) AmpliaIndice(idx);
	for (int i = idx.tamano; i > pos; --i)
		idx.array[i] = idx.array[i - 1];
	idx.tamano++;
}

void AmpliaIndice(tIndicePalabras & indice) {
	tIndicePalabras aux;
	aux.tamano = indice.tamano;
	aux.capacidad = (indice.capacidad * 3) / 2 + 1;
	aux.array = new tClaveValor[aux.capacidad];
	for (int i = 0; i < aux.tamano; ++i) {
		aux.array[i] = indice.array[i];
	}
	delete[] indice.array;
	indice = aux;
}

bool BusquedaRec(tIndicePalabras const&	l, std::string const& s, int ini, int fin, int & pos) {
	bool enc;
	if (ini == fin) {
		pos = ini;
		enc = false;
	}
	else {
		int mitad = (ini + fin - 1) / 2;
		if (s < l.array[mitad].clave)
			enc = BusquedaRec(l, s, ini, mitad, pos);
		else if (l.array[mitad].clave < s)
			enc = BusquedaRec(l, s, mitad + 1, fin, pos);
		else {
			pos = mitad;
			enc = true;
		}
	}
	return enc;
}
