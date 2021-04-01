//clavevalor.h
//Javier Guzm�n Mu�oz. Doble Grado en Ingenier�a Inform�tica - Matem�ticas.
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
/*Esta funci�n unicamente llama a la funcion de busqueda recursiva con los mismos parametros con los que se llama a ella
y eligiendo como inicio del vector el valor 0, y como fin su tama�o. As� se evita tener que modificar el codigo de la
practica 4, no siendo necesario tenr que a�adir dos parametros mas cada vez que se llama a la funcion de busqueda binaria*/
void insertarOrdenado(tIndicePalabras & idx, std::string const& palabra, std::string const& nombreArchivo);
/*Dada una palabra y un fichero en el que aparece se busca esa palabra en el indice. En caso de estar, se busca en la lista
de archivos en los que aparece el fihero dado. Si no esta, se inserta al final con el procedimiento insertar. En caso de no
estar la palabra se desplazan a la derecha las palabras del �ndice que ir�an despu�s de ella (por orden alfab�tico) 
y se inserta la palabra en su correspondiennte posici�n, insertando despues en la lista de archivos en los que aparece 
el nombre de fichero que pasamos a la funci�n*/
void desplazarDerecha(tIndicePalabras & idx, int pos);
/*Dada una posici�n desplaza una posici�n a la derecha todos los elementos del �ndice que est�n a la derecha de dicha posici�n
dejando un hueco libre en la posicion dada. Esta funci�n se usa para ayudar a abrir hueco en la funci�n InsertarOrdenado.
Aqu� se amplia la capacidad del indice si no hay mas posiciones libres a la derecha para abrir hueco.*/
void AmpliaIndice(tIndicePalabras & indice);
/*Esta funci�n ampl�a la capacidad del �ndice de palabras con la formula dada, ayudandose de una lista auxiliar para inicilizar
los valores en memoria din�mica*/
bool BusquedaRec(tIndicePalabras const&	l, std::string const& s, int ini, int fin, int & pos);
/*Implementacion del algoritmo de Busqueda Binaria en el modo recursivo visto en clase*/

#endif