//indices.h
//Javier Guzm�n Mu�oz. Doble Grado en Ingenier�a Inform�tica - Matem�ticas.
#include "clavevalor.h"
#include "matriz.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <cmath>
#ifndef indices_h
#define indices_h

const int MAX_ITERACIONES = 100; //Maximo de iteraciones para calcular el PageRank si no converge antes.
const float DIF_MAXIMA = 0.00001F; // Error que se tiene en cuenta para decidir si el calculo del PR converge.
const float C = 0.85F; //Constante de aleatoriedad del PageRank.
struct tFichero{ //Par nombre-PageRank que nos permitir� ordenar las paginas en las que aparece una palabra por su PR
	std::string nombre;
	float pageRank;
};

void crearTabla(tIndicePalabras	& tabla, const std::string &archivoInicial, tListaCadenas<std::string> & Totales, 
	tMatriz & L, tVector & a);
/*Crea el indice de palabras a partir de un archivo inicial, devolviendo la lista totales en la que parecen todos los
archivos a los que se enlaza al menos una vez y la matriz L normalizada que recoge los enlaces entre distintos ficheros.
Adem�s se crea el vector a que muestra que paginas no enlazan a ninguna otra. En la implementaci�n de la funci�n se explica
m�s detalladamente su funcionamiento*/

void inicializaIndiceVacio(tIndicePalabras & indice);
//Pone el contador del indice a 0, creando as� un �ndice vac�o.

void rellenaTabla(tIndicePalabras & indice, std::string const & nombrearchivo,tListaCadenas<std::string> & NoVisistados,
	tListaCadenas<std::string> & Totales, tMatriz & L, int j, tVector & a);
/*Esta funci�n procesa un archivo de la lista NoVisitados, extrayendo de el todas las palabras y nlaces y clasificandolos
correspondientemente. Adem�s, con las sucesivas llamadas a esta funci�n se va creando la matriz L y el vector a, adem�s
de ir rellenando con el orden correspondiente la tabla clave-valor. En la implementaci�n se explica m�s detalladamente su
funcionamiento*/

bool esEnlace(std::string const& palabra);
/*Dado un string leido de un fichero comprueba si tiene formato de enlace, es decir, si su primer caracter es '<' y el
�ltimo es '>'.*/

bool acabaEnPunt(std::string const& palabra);
/*Dado un string leido de un fichero devuelve true si su �ltimo caracter no es alfanum�rico o el caracter indicativo de
enlace '>'.*/

std::string elimina1erCaracter(std::string const& palabra);
/*Dado un string devuelve en otro string el primero habiendo eliminado su primer caracter. Se usa para eliminar el '<' de
las direcciones de enlaces.*/

bool CompArchivoINI(std::string const& nombrearchivo);
//Comprueba que exista el archivo ra�z para las b�squedas.

void AmpliaMatriz1(tMatriz & L);
//Dada una matriz la amplia con una fila y una columna de 0.

tVector CalculoPageRank(tVector const& a, tMatriz const& L);
/*Dada la matriz L y el vector a calcula el PageRank de los ficheros que se han procesado, iterando un maximo de 100 veces
si el proceso no converge antes(con un error de 0.00001)*/

bool PaginasdePalabra(const tIndicePalabras & indice, std::string palabra, const tVector & PageRank, 
	const tListaCadenas<std::string> & totales, tListaCadenas<tFichero> & paginas);
/*Esta funci�n devolver� un vector con los ficheros en los que aparece una palabra dada, cada uno con su correspondiente
PageRank. As�, se crea para cada fichero un tPagina que recoge su nombre( que sale del array valor del indice de la palabra
dada y estos pares los va insertando en un tListaCadenas de tFichero.*/

void OrdenarPorPageRank(tListaCadenas<tFichero> & paginas);
/*Aqu� se implementa el algoritmo de ordenaci�n por inserci�n para un tListaCadenas de tFichero, ordenando las paginas 
por su PageRank de mayor a menor.*/

bool operator > (tFichero const& f1, tFichero const& f2);
//Sobrecarga del operador '<' para que compare dos elementos del tipo tFichero, comparando en realidad el PR de cada uno.

bool HaConvergido(tVector const& PageRankIni, tVector const& pageRank);
/*Esta funci�n decide si el calculo del PageRank ha finalizado porque las iteraciones no var�an significativamente el valor de
las importancias de los ficheros (controlado por la constante MAX_DIFERENCIA). As� se dice que el proceso ha convergido 
cuando la difernecia(en valor absoluto) entre el PageRank que se acaba de calcular y el que se calcul� una iteraci�n antes
es menor o igual a 0.0001 para todos los ficheros.*/
#endif