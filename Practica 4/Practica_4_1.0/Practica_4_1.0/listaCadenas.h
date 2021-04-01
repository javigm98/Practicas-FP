#include <iostream>
#include <string>

#ifndef listaCadenas_h
#define listaCadenas_h

const int MAX_ARRAY = 100;

template<typename T>
struct tListaCadenas{
	int tamano;
	T array[MAX_ARRAY];
};
void insertar(tListaCadenas<std::string> & l, std::string const & s);
bool buscar(tListaCadenas<std::string> const & l, std::string const	& s, int & pos);


#endif