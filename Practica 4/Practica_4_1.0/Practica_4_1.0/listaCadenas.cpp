#include "listaCadenas.h"

void insertar(tListaCadenas<std::string> & l, std::string const & s){
	if (l.tamano < MAX_ARRAY){
		l.array[l.tamano] = s;
		l.tamano++;
	}
}
bool buscar(tListaCadenas<std::string> const & l, std::string const	& s, int & pos){
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < l.tamano){
		if (s == l.array[i]){
			encontrado = true;
			pos = i;
		}
		else{
			++i;
		}
	}
	return encontrado;
}