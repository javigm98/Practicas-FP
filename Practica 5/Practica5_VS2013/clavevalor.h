//clavevalor.h
//Javier Guzmán Muñoz. Doble Grado en Ingeniería Informática - Matemáticas.
#include "listaCadenas.h"
#ifndef clavevalor_h
#define clavevalor_h

struct tClaveValor{
	std::string clave;
	tListaCadenas<std::string> valor;
};
struct tIndicePalabras{
	int tamano, capacidad;
	tClaveValor * array;
};
bool busquedaBinaria(tIndicePalabras const&	l, std::string const& s, int & pos);
/*Esta función unicamente llama a la funcion de busqueda recursiva con los mismos parametros con los que se llama a ella
y eligiendo como inicio del vector el valor 0, y como fin su tamaño. Así se evita tener que modificar el codigo de la
practica 4, no siendo necesario tenr que añadir dos parametros mas cada vez que se llama a la funcion de busqueda binaria*/
void insertarOrdenado(tIndicePalabras & idx, std::string const& palabra, std::string const& nombreArchivo);
/*Dada una palabra y un fichero en el que aparece se busca esa palabra en el indice. En caso de estar, se busca en la lista
de archivos en los que aparece el fihero dado. Si no esta, se inserta al final con el procedimiento insertar. En caso de no
estar la palabra se desplazan a la derecha las palabras del índice que irían después de ella (por orden alfabético) 
y se inserta la palabra en su correspondiennte posición, insertando despues en la lista de archivos en los que aparece 
el nombre de fichero que pasamos a la función*/
void desplazarDerecha(tIndicePalabras & idx, int pos);
/*Dada una posición desplaza una posición a la derecha todos los elementos del índice que estén a la derecha de dicha posición
dejando un hueco libre en la posicion dada. Esta función se usa para ayudar a abrir hueco en la función InsertarOrdenado.
Aquí se amplia la capacidad del indice si no hay mas posiciones libres a la derecha para abrir hueco.*/
void AmpliaIndice(tIndicePalabras & indice);
/*Esta función amplía la capacidad del índice de palabras con la formula dada, ayudandose de una lista auxiliar para inicilizar
los valores en memoria dinámica*/
bool BusquedaRec(tIndicePalabras const&	l, std::string const& s, int ini, int fin, int & pos);
/*Implementacion del algoritmo de Busqueda Binaria en el modo recursivo visto en clase*/

#endif