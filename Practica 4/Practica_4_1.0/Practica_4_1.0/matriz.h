#include <iostream>
#ifndef matriz_h
#define matriz_h
const int MAX_TAM = 100;
struct tMatriz{
	double matriz[MAX_TAM][MAX_TAM];
	int tam;
};

struct tVector{
	double elementos[MAX_TAM];
	int tam;
};

tMatriz matrizConstante(double x, int n);
tVector operator*(tVector const & v, tMatriz const & m);
tVector operator*(double x, tVector const & m);
void normalizaL(tMatriz & L);
#endif