#include <iostream>
#include <vector>
using namespace std;

bool buscarBinariaREC(vector<int> v, int buscado, int ini, int fin, int & pos);
bool BusquedaBinaria(vector<int> v, int buscado, int & pos);
void OrdenarInsercion(vector<int> & v);

int main() {
	
	int tam, elem, buscado, pos = 0;
	cout << "Tamano: ";
	cin >> tam;
	while (tam != -1) {
		vector<int> v;
		for (int i = 0; i < tam; ++i) {
			cin >> elem;
			v.push_back(elem);
		}
		OrdenarInsercion(v);
		cout << "Vector ordenado: ";
		for (int i = 0; i < v.size(); ++i)
			cout << v[i] << " ";
		cout << '\n';
		cout << "Buscado: ";
		cin >> buscado;
		if (BusquedaBinaria(v, buscado, pos)) cout << "Encontrado en la posicion " << pos << '\n';
		else cout << "No encontrado\n";
		cout << "Tamano: ";
		cin >> tam;
	}
	return 0;
}


bool buscarBinariaREC(vector<int> v, int buscado, int ini, int fin, int & pos) {
		bool enc;
		if (ini == fin) {
			pos = ini;
			enc = false;
		}
		else {
			int mitad = (ini + fin - 1) / 2;
			if (buscado < v[mitad])
				enc = buscarBinariaREC (v, buscado, ini, mitad, pos);
			else if (v[mitad] < buscado)
				enc = buscarBinariaREC(v, buscado, mitad + 1, fin, pos);
			else {
				pos = mitad;
				enc = true;
			}
		}
		return enc;
	}

bool BusquedaBinaria(vector<int> v, int buscado, int & pos) {
	return buscarBinariaREC(v, buscado, 0, v.size(), pos);
}

void OrdenarInsercion(vector<int> & v) {
	for (int i = 1; i < v.size(); ++i) {
		int elemento = v[i];
		int j = i;
		while (j > 0 && elemento < v[j - 1]) {
			v[j] = v[j - 1];
			--j;
		}
		if (j != i) {
			v[j] = elemento;
		}
	}
}