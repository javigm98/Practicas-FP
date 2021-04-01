//matriz.h
//Javier Guzm�n Mu�oz. Doble Grado en Ingenier�a Inform�tica - Matem�ticas.
#include <iostream>
#ifndef matriz_h
#define matriz_h
const int MAX_TAM = 100; //Tama�o maximo de una matriz y un vector.
struct tMatriz{ //matriz cuadrada de tama�o variable, con un maximo de MAX_TAM
	float matriz[MAX_TAM][MAX_TAM];
	int tam;
};

struct tVector{ //vector de tama�o variable, con un maximo de MAX_TAM
	float elementos[MAX_TAM];
	int tam;
};

tMatriz matrizConstante(float x, int n);
//Crea una matriz cuadrada de tama�o n en la que todos sus elementos son el valor x, siempre y cuando n sea menor que MAX_TAM
tVector operator*(tVector const & v, tMatriz const & m);
//Sobrecaraga del operador * para que realice la operaci�n vector * matriz.
tVector operator*(float x, tVector const & m);
//Sobrecaraga del operador * para que multiplique todos los elementos de un vector por x.
void normalizaL(tMatriz & L);
/*Dada una matriz L devuleve sobre la misma matriz una matriz en la que los elementos de cada fila suman 1, 
excepto si la fila es nula, que la deja como est�. Esto se consigue diviendo cada elemento de la fila por el total,
ya que la matriz dada solo contendr� 0 y 1 como valores*/
float operator*(tVector const& v1, tVector const& v2);
/*sobrecaraga del operador * para que multiplique dos vectores vistos como matrices 1xn y nx1, 
obteniendose por tanto un valor real como resultado*/
tVector operator+(tVector const& m1, tVector const & m2);
//Sobrecaraga del operdaor + para que sume dos vectores dados.
tVector vectorConstante(float x, int n);
//Siempre y cuando n sea menor que MAX_TAM, crea un vector de tama�o n y en el que todos sus elementos son x.
#endif