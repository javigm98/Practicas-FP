//matriz.h
//Javier Guzmán Muñoz. Doble Grado en Ingeniería Informática - Matemáticas.
#include <iostream>
#ifndef matriz_h
#define matriz_h
const int MAX_TAM = 100; //Tamaño maximo de una matriz y un vector.
struct tMatriz{ //matriz cuadrada de tamaño variable, con un maximo de MAX_TAM
	float matriz[MAX_TAM][MAX_TAM];
	int tam;
};

struct tVector{ //vector de tamaño variable, con un maximo de MAX_TAM
	float elementos[MAX_TAM];
	int tam;
};

tMatriz matrizConstante(float x, int n);
//Crea una matriz cuadrada de tamaño n en la que todos sus elementos son el valor x, siempre y cuando n sea menor que MAX_TAM
tVector operator*(tVector const & v, tMatriz const & m);
//Sobrecaraga del operador * para que realice la operación vector * matriz.
tVector operator*(float x, tVector const & m);
//Sobrecaraga del operador * para que multiplique todos los elementos de un vector por x.
void normalizaL(tMatriz & L);
/*Dada una matriz L devuleve sobre la misma matriz una matriz en la que los elementos de cada fila suman 1, 
excepto si la fila es nula, que la deja como está. Esto se consigue diviendo cada elemento de la fila por el total,
ya que la matriz dada solo contendrá 0 y 1 como valores*/
float operator*(tVector const& v1, tVector const& v2);
/*sobrecaraga del operador * para que multiplique dos vectores vistos como matrices 1xn y nx1, 
obteniendose por tanto un valor real como resultado*/
tVector operator+(tVector const& m1, tVector const & m2);
//Sobrecaraga del operdaor + para que sume dos vectores dados.
tVector vectorConstante(float x, int n);
//Siempre y cuando n sea menor que MAX_TAM, crea un vector de tamaño n y en el que todos sus elementos son x.
#endif