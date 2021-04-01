//listaCadenas.h
//Javier Guzmán Muñoz. Doble Grado en Ingeniería Informática - Matemáticas.
#include <iostream>
#include <string>

#ifndef listaCadenas_h
#define listaCadenas_h

const int MAX_ARRAY = 100;

template<typename T>
struct tListaCadenas{ // Tipo generico tListaCadenas que incluye un array del tipo T y un contador.
	int tamano;
	T array[MAX_ARRAY];
};
template <typename T>
/* Dado un elemento del tipo T lo inserta al final de la correspondiente lista tListaCadenas,
aumentando en 1 el tamaño de la misma.*/
void insertar(tListaCadenas<T> & l, T const & s){
	if (l.tamano < MAX_ARRAY){ //Nos aseguramos de que no sobrepasamos el maximo del array.
		l.array[l.tamano] = s;
		l.tamano++;
	}
} 
template <typename T>
/*Dado un elemento del tipo T busca en un tListaCadenas de ese tipo dicho elemento, recorriendo la lista desde el principio
y parando cuando lo encuentra. Devuelve si se ha encontrado dicho elemento y la posicion en la que se encuentra */
bool buscar(tListaCadenas<T> const & l, T const	& s, int & pos){
	bool encontrado = false;
	int i = 0;
	pos = 0;
	while (!encontrado && i < l.tamano){
		if (s == l.array[i]){
			encontrado = true;
			pos = i;
		}
		else{
			++i;
		}
	}
	return encontrado;
}
template <typename T>
//Pone el contador de un tListaCadenas a 0
void inicializaListaVacia(tListaCadenas<T> & lista) {
	lista.tamano = 0;
}


#endif