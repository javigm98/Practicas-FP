//matriz.cpp
//Javier Guzmán Muñoz. Doble Grado en Ingeniería Informática - Matemáticas.
#include "matriz.h"
tMatriz matrizConstante(float x, int n){
	tMatriz matriz;
	if (n <= MAX_TAM){
		matriz.tam = n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				matriz.matriz[i][j] = x;
	}
	else matriz.tam = 0; //Si se sobrepasa el tamaño maximo devolvemos una matriz vacia.
	return matriz;
}

tVector operator*(tVector const & v, tMatriz const & m){
	tVector resultado;
	resultado.tam = v.tam;
	for (int i = 0; i < v.tam; ++i){
		float suma = 0.0;
		for (int j = 0; j < v.tam; ++j){
			suma = suma + (v.elementos[j] * m.matriz[j][i]);
		}
		resultado.elementos[i] = suma;
	}
	return resultado;
}

tVector operator*(float x, tVector const & m){
	tVector resultado;
	resultado.tam = m.tam;
	for (int i = 0; i < m.tam; ++i)
		resultado.elementos[i] = x * m.elementos[i];
	return resultado;
}

float operator*(tVector const& v1, tVector const& v2) {
	float resultado = 0.0;
	for (int i = 0; i < v1.tam; ++i) 
		resultado = resultado + (v1.elementos[i] * v2.elementos[i]);
	return resultado;
}

tVector operator+(tVector const& m1, tVector const & m2){
	tVector resultado;
	resultado.tam = m1.tam;
	for (int i = 0; i < m1.tam; ++i)
		resultado.elementos[i] = m1.elementos[i] + m2.elementos[i];
	return resultado;
}

void normalizaL(tMatriz & L){
	for (int i = 0; i < L.tam; ++i){
		float norma = 0.0;
		for (int j = 0; j < L.tam; ++j){
			norma = norma + L.matriz[i][j];
		}
		if (norma != 0.0){
			for (int j = 0; j < L.tam; ++j) L.matriz[i][j] = L.matriz[i][j] / norma;
		}
	}
}

tVector vectorConstante(float x, int n) {
	tVector v;
	if (n <= MAX_TAM){
		v.tam = n;
		for (int i = 0; i < v.tam; ++i) v.elementos[i] = x;
	}
	else v.tam = 0; //Si se sobrepasa el tamaño maximo devolvemos una matriz vacía
	return v;
}

