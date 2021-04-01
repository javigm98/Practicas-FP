#include "matriz.h"
tMatriz matrizConstante(double x, int n){
	tMatriz matriz;
	matriz.tam = n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			matriz.matriz[i][j] = x;
	return matriz;
}

tVector operator*(tVector const & v, tMatriz const & m){
	tVector resultado;
	resultado.tam = v.tam;
	for (int i = 0; i < v.tam; ++i){
		double suma = 0.0;
		for (int j = 0; j < v.tam; ++j){
			suma = suma + (v.elementos[j] * m.matriz[j][i]);
		}
		resultado.elementos[i] = suma;
	}
	return resultado;
}

tVector operator*(double x, tVector const & m){
	tVector resultado;
	resultado.tam = m.tam;
	for (int i = 0; i < m.tam; ++i)
		resultado.elementos[i] = x * m.elementos[i];
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
		double norma = 0.0;
		for (int j = 0; j < L.tam; ++j){
			norma = norma + L.matriz[i][j];
		}
		if (norma != 0.0){
			for (int j = 0; j < L.tam; ++j) L.matriz[i][j] = L.matriz[i][j] / norma;
		}
	}
}

