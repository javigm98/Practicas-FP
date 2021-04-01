#include "clavevalor.h"
#include "matriz.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#ifndef indices_h
#define indices_h


void crearTabla(tIndicePalabras	& tabla, const std::string &archivoInicial);
//void LeerArchivo(std::ifstream & archivo, std::stringstream & ss);
void inicializaIndiceVacio(tIndicePalabras & indice);
void rellenaTabla(tIndicePalabras & indice, std::string nombrearchivo, tListaCadenas<std::string> & visitados, tListaCadenas<std::string> & NoVisistados, tListaCadenas<std::string> & Totales, tMatriz & L, int j);
bool esEnlace(std::string palabra);
bool acabaEnPunt(std::string palabra);
std::string elimina1erCaracter(std::string palabra);
bool CompArchivoINI(std::string nombrearchivo);
void AmpliaMatriz1(tMatriz & L);

#endif