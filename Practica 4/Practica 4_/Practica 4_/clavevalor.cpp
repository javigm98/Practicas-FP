//clavevalor.cpp
//Javier Guzmán Muñoz. Doble Grado en Ingeniería Informática - Matemáticas.
#include "clavevalor.h"
#include "indices.h"

bool busquedaBinaria(tIndicePalabras const&	l, std::string const& s, int & pos){
	int ini = 0, fin = l.tamano, mitad;
	bool encontrado = false;
	while (ini < fin && !encontrado) {
		mitad = (ini + fin - 1) / 2; // división entera
		if (s < l.array[mitad].clave) fin = mitad;
		else if (l.array[mitad].clave < s) ini = mitad + 1;
		else encontrado = true;
	}
	if (encontrado) pos = mitad; // en la posición mitad
	else pos = ini;  // No encontrado, le corresponde la posición ini (=fin)
	return encontrado;
}

void insertarOrdenado(tIndicePalabras & idx, std::string const& palabra, std::string const& nombreArchivo){
	int pos = 0, a = 0;
	if (idx.tamano < MAX_INDICE){ //Nos aseguramos de que no sobrepasamos el maximo del array
		if (busquedaBinaria(idx, palabra, pos)){
			if (!buscar(idx.array[pos].valor, nombreArchivo, a)) insertar(idx.array[pos].valor, nombreArchivo);
		}
		else{
			desplazarDerecha(idx, pos);
			idx.array[pos].clave = palabra;
			inicializaListaVacia(idx.array[pos].valor);
			insertar(idx.array[pos].valor, nombreArchivo);
		}
	}
}
void desplazarDerecha(tIndicePalabras & idx, int pos){
	for (int i = idx.tamano; i > pos; --i)
		idx.array[i] = idx.array[i - 1];
	idx.tamano++;
}
