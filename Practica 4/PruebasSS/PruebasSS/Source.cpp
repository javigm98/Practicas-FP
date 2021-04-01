#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <algorithm>
#include <cctype>
using namespace std;

/*bool esEnlace(std::string palabra);
bool acabaEnPunt(std::string palabra);
std::string elimina1erCaracter(std::string palabra);

const int MAX = 100;
struct tLista{
	int cont;
	string array[MAX];
};

int main(){
	ifstream archivo;
	tLista lista;
	lista.cont = 0;
	string palabra;
	stringstream ss;
	string aux;
	archivo.open("prueba.txt");
	while (!archivo.eof()){
		getline(archivo, palabra);
		ss << palabra << " ";
	}
	while (ss){
		ss >> aux;
		std::transform(aux.begin(), aux.end(), aux.begin(), std::tolower);
		lista.array[lista.cont] = aux;
		++lista.cont;
	}
	for (int i = 0; i < lista.cont - 1; ++i){
		if (esEnlace(lista.array[i])){
			lista.array[i] = elimina1erCaracter(lista.array[i]);
			lista.array[i].pop_back();
			cout << "  ENLACE";
		}
		if (acabaEnPunt(lista.array[i])) cout << "  PUNTUACION";
		cout << "  " << lista.array[i];
		cout << endl;
	}
	system("pause");
	return 0;
}

bool esEnlace(std::string palabra){
	if (palabra[0] == '<' && palabra[palabra.size() - 1] == '>')
		return true;
	else return false;
}
bool acabaEnPunt(std::string palabra){
	if (palabra[palabra.size() - 1] == ',' || palabra[palabra.size() - 1] == '.') return true;
	else return false;
}
std::string elimina1erCaracter(std::string palabra){
	std::string palabra2;
	for (int i = 0; i < palabra.size() - 1; ++i)
		palabra2.push_back(palabra[i + 1]);
	return palabra2;
}*/

const int MAX_TAM = 100;

struct tMatriz{
	double matriz[MAX_TAM][MAX_TAM];
	int tam;
};

struct tVector{
	double elementos[MAX_TAM];
	int tam;
};
tVector operator*(tVector const & v, tMatriz const & m);
tVector operator*(double x, tVector const & m);
double operator*(tVector const& v1, tVector const& v2);
tVector operator+(tVector const& m1, tVector const & m2);
void normalizaL(tMatriz & L);
tVector vectorConstante(double x, int n);

int main(){
	tVector vector, producto, vector2, e;
	tMatriz matriz;
	double res;
	cin >> vector.tam;
	while (vector.tam != 0){
		matriz.tam = vector.tam;
		vector2.tam = vector.tam;
		e.tam = vector.tam;
		for (int i = 0; i < vector.tam; ++i) cin >> vector.elementos[i];
		for (int i = 0; i < vector2.tam; ++i) cin >> vector2.elementos[i];
		for (int i = 0; i < e.tam; ++i) cin >> e.elementos[i];
		for (int i = 0; i < matriz.tam; ++i)
			for (int j = 0; j < matriz.tam; ++j)
				cin >> matriz.matriz[i][j];
		producto = 0.85 * vector * matriz + (0.85 * vector * vector2 + 1 - 0.85) * (1.0 / vector.tam) * e;
		//res = 0.85 * vector  * vector2 + 1 - 0.85;
		//producto = (1 / e.tam)*e;
		for (int i = 0; i < producto.tam; ++i) cout << producto.elementos[i] << " ";
		//res = 1.0 / e.tam;
		//cout << res;
		cout << '\n';
		cin >> vector.tam;
	}
	return 0;
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

tVector operator*(double x, tVector const & m) {
	tVector resultado;
	resultado.tam = m.tam;
	for (int i = 0; i < m.tam; ++i)
		resultado.elementos[i] = x * m.elementos[i];
	return resultado;
}

double operator*(tVector const& v1, tVector const& v2) {
	double resultado = 0.0;
	for (int i = 0; i < v1.tam; ++i)
		resultado = resultado + (v1.elementos[i] * v2.elementos[i]);
	return resultado;
}

tVector operator+(tVector const& m1, tVector const & m2) {
	tVector resultado;
	resultado.tam = m1.tam;
	for (int i = 0; i < m1.tam; ++i)
		resultado.elementos[i] = m1.elementos[i] + m2.elementos[i];
	return resultado;
}

void normalizaL(tMatriz & L) {
	for (int i = 0; i < L.tam; ++i) {
		double norma = 0.0;
		for (int j = 0; j < L.tam; ++j) {
			norma = norma + L.matriz[i][j];
		}
		if (norma != 0.0) {
			for (int j = 0; j < L.tam; ++j) L.matriz[i][j] = L.matriz[i][j] / norma;
		}
	}
}

tVector vectorConstante(double x, int n) {
	tVector v;
	v.tam = n;
	for (int i = 0; i < v.tam; ++i) v.elementos[i] = x;
	return v;
}