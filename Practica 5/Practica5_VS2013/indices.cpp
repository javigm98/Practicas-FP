//indices.cpp
//Javier Guzmán Muñoz. Doble Grado en Ingeniería Informática - Matemáticas.
#include "indices.h"
#include "matriz.h"
#include "checkML.h"

void crearTabla(tIndicePalabras	& tabla, const std::string &archivoInicial, tListaCadenas<std::string> & Totales, 
	tMatriz & L, tVector & a){
	tListaCadenas<std::string> Visitados, NoVisitados;
	Visitados.capacidad = TAM_INI; 
	NoVisitados.capacidad = TAM_INI; //Inicilizo la capacidad de las lista a TAM_INI
	Visitados.vector = new std::string[Visitados.capacidad];
	NoVisitados.vector = new std::string[NoVisitados.capacidad]; //Creo TAM_INI variables dinamicas en el array dinamico
	a.tam = 0; //Inicializo 'a' a vector vacío.
	inicializaListaVacia(Visitados);
	inicializaListaVacia(NoVisitados);
	inicializaListaVacia(Totales); //Inicializo las tres listas de paginas a vacías (cont = 0).
	insertar(NoVisitados, archivoInicial);
	insertar(Totales, archivoInicial); //Inserto el archivo inicial en totales y noVisitados
	L = matrizConstante(0.0, 1); //Inicializo la matriz L a una matriz nula 1x1.
	while (NoVisitados.tamano > 0){
		int j;
		std::string nombrearchivo = NoVisitados.vector[NoVisitados.tamano - 1]; //Cojo el ultimo fichero que hay en noVisitados.
		bool busca = buscar(Totales, nombrearchivo, j); //Obtengo la posición de ese archivo en la lista de totales.
		insertar(Visitados, nombrearchivo); //Inserto ese archivo en visitados (pues ya lo voy a procesar)
		--NoVisitados.tamano; //Disminuyo en 1 el tamaño de visitados para borrara el archivo que estoy procesando.
		rellenaTabla(tabla, nombrearchivo, NoVisitados, Totales, L, j, a);
	}
	normalizaL(L); //Normalizo la matriz L una vez que he procesado todos los ficheros.
	delete[] Visitados.vector; 
	delete[] NoVisitados.vector; //Recupero la memoria dinamica utilizada
}

void inicializaIndiceVacio(tIndicePalabras & indice){
	indice.tamano = 0;
}

void rellenaTabla(tIndicePalabras & indice, std::string const& nombrearchivo, tListaCadenas<std::string> & NoVisistados, 
	tListaCadenas<std::string> & Totales, tMatriz & L, int j, tVector & a){
	std::string aux;
	std::ifstream archivo;
	archivo.open(nombrearchivo); 
	bool tieneEnlaces = false; 
	//Con este booleano compruebo si el fichero no enlaza con ningún otro para tenerlo en cuenta a la hora de crear 'a'.
	while (!archivo.eof()){
		int pos = 0;
		std::string palabra;
		getline(archivo, palabra); //Copio en un string una línea del fihero
		std::stringstream ss;
		ss << palabra; //Copio esa línea a un flujo stringstream.
		ss >> aux; //Voy sacando palabra a palabra del stringstream.
		while (ss){
			std::transform(aux.begin(), aux.end(), aux.begin(), std::tolower); //Sea la palabra que sea, la pongo en minuculas
			if (acabaEnPunt(aux)) aux.pop_back(); //Si acaba en signo de puntución elimino el ultimo caracter.
			if (!esEnlace(aux)){
				insertarOrdenado(indice, aux, nombrearchivo);
			}
			//Si no se trata de un enlace lo inserto ordenadamente en el indice.
			else{
				aux = elimina1erCaracter(aux);
				aux.pop_back(); //Elimino los signos que indican que lo que he leido es un enlace (< y >).
				if (aux != nombrearchivo){
					tieneEnlaces = true; //La pagina ya enlaza con alguna otra.
					int i = 0;
					if (buscar(Totales, aux, i)) L.matriz[j][i] = 1.0;
					/*Si el enlace está en totales pongo en uno en la matriz L en la fila del archivo del que estoy leyendo y
					la columna correspondiente a ese enlace en totales.*/
					else {
						insertar(NoVisistados, aux);
						insertar(Totales, aux); //Si el enlace no se había leído aun lo añado a totales y noVisitados
						AmpliaMatriz1(L); //Amplio la matriz L para que haya hueco para el nuevo enlace
						L.matriz[j][L.tam - 1] = 1.0;
						//En la fila correspondiente al fichero del que estoy leyendo y la ultima columna que he añadido pongo un 1
					}
				}
			}
			ss >> aux; //Itero el proceso hasta que haya leido todas las palabras de la linea.
		}
	}
	archivo.close();
	if (tieneEnlaces) a.elementos[j] = 0.0; 
	//Si el fichero procesado enlazaba a al menos otros, pongo un 0 en el vector a en su posición
	else a.elementos[j] = 1.0; //Si no enlazaba, pongo un 1.
	++a.tam;
}

bool esEnlace(std::string const& palabra){
	return (palabra[0] == '<' && palabra[palabra.size() - 1] == '>');
}

bool acabaEnPunt(std::string const & palabra){
	return (!std::isalnum(palabra[palabra.size() - 1]) && palabra[palabra.size() - 1] != '>');
}

std::string elimina1erCaracter(std::string const& palabra){
	std::string palabra2;
	for (int i = 0; i < palabra.size() - 1; ++i)
		palabra2.push_back(palabra[i + 1]);
	return palabra2;
}

bool CompArchivoINI(std::string const& nombrearchivo){
	std::ifstream archivo;
	archivo.open(nombrearchivo);
	if (archivo.is_open()){
		archivo.close();
		return true;
	}
	else return false;
}

void AmpliaMatriz1(tMatriz & L){
	++L.tam;
	for (int i = 0; i < L.tam; ++i){
		L.matriz[i][L.tam - 1] = 0.0;
		L.matriz[L.tam - 1][i] = 0.0;
	}
}

tVector CalculoPageRank(tVector const& a, tMatriz const& L) {
	tVector e, pageRank, pageRankIni;
	pageRankIni = vectorConstante(1.0, a.tam); //El primer PageRank es un vector de la forma (1.....1)
	e = vectorConstante(1.0, a.tam);// e es el vector unidad (1.....1)
	bool converge = false;
	int i = 0;
	while (!converge && i < MAX_ITERACIONES){
		pageRank = C * pageRankIni * L + (C * pageRankIni * a + 1 - C) * (1.0/a.tam) * e ;
		converge = HaConvergido(pageRankIni, pageRank);
		pageRankIni = pageRank;
		++i;
	}
	return pageRank;
}

bool PaginasdePalabra(const tIndicePalabras & indice, std::string palabra, const tVector & PageRank, 
	const tListaCadenas<std::string> & totales, tListaCadenas<tFichero> & paginas) {
	inicializaListaVacia(paginas); //Pongo el contador de paginas a 0
	int pos = 0;
	bool existe = true;
	std::string aux;
	if (busquedaBinaria(indice, palabra, pos)) { //Veo si la palabra buscada aparece en algún fichero.
		paginas.tamano = indice.array[pos].valor.tamano;
		paginas.capacidad = paginas.tamano;
		/*El tamaño y la capacidad de paginas sera el mismo que tenga la lista correspondiente a la clave de la cual estamos
		calculando su lista de paginas con pageRank, pues este sera el numero de paginas en el que aparezca la palabra*/
		paginas.vector = new tFichero[paginas.capacidad];
		//Creamos tantas variables dinamicas como paginas en las que aparezca la palabra tengamos.
		for (int i = 0; i < indice.array[pos].valor.tamano; ++i) {
			/*Voy sacando los ficheros en los que aparece dicha palabra (del array valor para la palabra) y los inserto
			 con su PageRank en la lista paginas.*/
			int j = 0;
			aux = indice.array[pos].valor.vector[i];
			if (buscar(totales, aux, j)){
				paginas.vector[i].nombre = aux;
				paginas.vector[i].pageRank = PageRank.elementos[j];
			}
		}
	}
	//La memoria dinamica empleada la recupero en el main, tras haber mostrado los elementos ordenados por su PR
	else existe = false;
	return existe;
}

void OrdenarPorPageRank(tListaCadenas<tFichero> & paginas) {
	for (int i = 1; i < paginas.tamano; ++i) {
		tFichero elemento = paginas.vector[i];
		int j = i;
		while (j > 0 && elemento > paginas.vector[j - 1]) {
			paginas.vector[j] = paginas.vector[j - 1];
			--j;
		}
		if (j != i) {
			paginas.vector[j] = elemento;
		}
	}
}

bool operator > (tFichero const& f1, tFichero const& f2){
	return f1.pageRank > f2.pageRank;
}

bool HaConvergido(tVector const& PageRankIni, tVector const& pageRank){
	bool converge = true;
	int i = 0;
	while (converge && i < pageRank.tam){
		float resta = PageRankIni.elementos[i] - pageRank.elementos[i];
		if (abs(resta) > DIF_MAXIMA) converge = false;
		++i;
	}
	return converge;
}