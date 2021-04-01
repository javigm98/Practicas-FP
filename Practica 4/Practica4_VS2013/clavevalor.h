//clavevalor.h
//Javier Guzm�n Mu�oz. Doble Grado en Ingenier�a Inform�tica - Matem�ticas.
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
/*Algoritmo de busqueda binaria de un string s en un indice, devolviendo la posicion del indice en el que se encuentra.
En este caso el string ser� la palabra buscada por el ususario y en caso de existir en la table calve-valor se devolver� su
posici�n para poder obtener posteriormenet los ficheros en los que aparece*/
void insertarOrdenado(tIndicePalabras & idx, std::string const& palabra, std::string const& nombreArchivo);
/*Dada una palabra y un fichero en el que aparece se busca esa palabra en el indice. En caso de estar, se busca en la lista
de archivos en los que aparece el fihero dado. Si no esta, se inserta al final con el procedimiento insertar. En caso de no
estar la palabra se desplazan a la derecha las palabras del �ndice que ir�an despu�s de ella (por orden alfab�tico) 
y se inserta la palabra en su correspondiennte posici�n, insertando despues en la lista de archivos en los que aparece 
el nombre de fichero que pasamos a la funci�n*/
void desplazarDerecha(tIndicePalabras & idx, int pos);
/*Dada una posici�n desplaza una posici�n a la derecha todos los elementos del �ndice que est�n a la derecha de dicha posici�n
dejando un hueco libre en la posicion dada. Esta funci�n se usa para ayudar a abrir hueco en la funci�n InsertarOrdenado*/

#endif