/* 

Grupo 3:
Jorge Villarrubia Elvira
Javier Guzmán Muñoz

*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <locale> // Para escribir acentos y ñ
using namespace std;

const int MAX_PROD = 25;
const int PROD_NULO = 0;
const int CENTINELA = -1;
typedef int tArray[MAX_PROD];


int menu();
void ejecutarOpc(int opc, tArray fila, int &tam, int &movimientos);
void ejecutarLeerFichero(tArray fila, int &tam);
void ejecutarGuardarfichero(const tArray fila, int tam);
void mostrarfila(const tArray fila, int tam);
bool esPosValida(int tam, int pos);
bool estaVacia(const tArray fila, int pos);
void leerFilaFich(istream &fich, tArray fila, int &tam);
void escribirFilaFich(ostream &fich, const tArray fila, int tam);
// bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar);
bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar);
bool perteneceABloqueLevantado(int pos, int posIni, int posFin);  // CREADA POR MÍ
bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar);
bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar);
// bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar);
void ejecutarGrua(tArray fila, int tam, bool &movimientohecho);   //Afectada por lo de devolver si hay movimiento 
// int posHuecoLibreDerecha(const tArray fila, int tam, int posIni);
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);
bool alMenosUnMovimientoExcavadora(int primerhuecolibre, int tam);  // CREADA POR MÍ
// bool excavadora1Derecha(tArray fila, int tam, int posIni);
bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion);
void ejecutarExcavadora(tArray fila, int tam, bool &movimientohecho);      //Afectada por lo de devolver si hay movimiento 
bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion); 
bool filaOrdenada(const tArray fila, int tam);

int main(){
	setlocale(LC_ALL, "spanish");
	system("chcp 1252");

	int opcion, tam, movimientos;
	tArray fila;
	movimientos = 0;     // Decirle lo que he hecho con movimientos devolviendolo por referencia
	tam = 0;            // Una manera de inicializar la fila como vacía		
	opcion = menu();
	while (opcion != 0){
		ejecutarOpc(opcion, fila, tam, movimientos);
		opcion = menu();
	}
	return 0;
}


int menu(){
	int opc;
	cout << endl;
	cout << "1.- Cargar fila de fichero" << endl;
	cout << "2.- Guarda fila en fichero" << endl;
	cout << "3.- Usar grúa" << endl;
	cout << "4.- Usar excavadora" << endl;
	cout << "0.- Salir" << endl;
	cout << endl;
	cout << "Introduzca la opción deseada: ";
	cin >> opc;

	while (opc < 0 || opc > 4){    // Preguntar si esto no se declara como constantes
		cout << "La opción introducida no es válida, por favor introduzca una correcta. ";
		cin >> opc;

		while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";
			cin >> opc;
		}
		cin.sync();
	}


	return opc;
}

void ejecutarOpc(int opc, tArray fila, int &tam, int &movimientos){ // Acabarla
	bool movimientohecho, filaordenada;
		//Pensar como inicializar lo de movimientos
		switch (opc)
		{
		case 1: {
			ejecutarLeerFichero(fila, tam);
			movimientos = 0;
		}
				break;
		case 2: {
			ejecutarGuardarfichero(fila, tam);
		}
				break;
		case 3: {
			if (tam != 0){
				ejecutarGrua(fila, tam, movimientohecho);
				filaordenada = filaOrdenada(fila, tam);
				if (movimientohecho){ movimientos++; }
				cout << endl;
				cout << "Usted lleva hechos " << movimientos << " movimientos" << endl;
				if (filaordenada) { cout << "Y la fila ya se encuentra ordenada" << endl; }
				else { cout << "Y la fila NO se encuentra ordenada" << endl; }
			}
			else {
				cout << endl;
				cout << "La fila está vacía. Por favor, cargue una fila antes de ejecutar esta opción." << endl;
			}
		}
				break;
		case 4: {
			if (tam != 0){
				ejecutarExcavadora(fila, tam, movimientohecho);
				filaordenada = filaOrdenada(fila, tam);
				if (movimientohecho){ movimientos++; }
				cout << endl;
				cout << "Usted lleva hechos " << movimientos << " movimientos" << endl;
				if (filaordenada) { cout << "Y la fila ya se encuentra ordenada" << endl; }
				else { cout << "Y la fila NO se encuentra ordenada" << endl; }
			}
			else {
				cout << endl;
				cout << "La fila está vacía. Por favor, cargue una fila antes de ejecutar esta opción." << endl; 
			}     
		}
	}

}
void ejecutarLeerFichero(tArray fila, int &tam){
	string ficheroentrada;
	ifstream archivo;
	cout << "Introduzca el nombre del fichero que desea abrir: ";
	cin >> ficheroentrada;
	archivo.open(ficheroentrada);
	if (archivo.is_open()){
		leerFilaFich(archivo, fila, tam);
			cout << endl;
			cout << "Se ha cargado la fila con éxito" << endl;
			cout << "La fila leída es la siguiente: " << endl;
			mostrarfila(fila, tam);
			archivo.close();
	}
	else { 
		cout << endl;
		cout << "El archivo no se pudo abrir" << endl;
		cout << "La fila sigue inicializada como vacía" << endl;
	}

}


void ejecutarGuardarfichero(const tArray fila, int tam){
	string ficherosalida;
	bool acabaentxt;
	ofstream archivo2;
	cout << "Introduzca el nombre del fichero donde desea guardar la fila: ";
	cin >> ficherosalida;
	if (ficherosalida.size() < 4){ acabaentxt = false; }
	else if (ficherosalida.rfind(".txt") == (ficherosalida.size() - 4)){ acabaentxt = true; }
	else { acabaentxt = false; }

	while (!acabaentxt){
		cout << "Por favor, introduzca un nombre para el archivo acabado en '.txt': ";
		cin >> ficherosalida;
		if (ficherosalida.size() < 4){ acabaentxt = false; }
		else if (ficherosalida.rfind(".txt") == (ficherosalida.size() - 4)){
			acabaentxt = true; }
		else { acabaentxt = false; }
	}
	archivo2.open(ficherosalida);
	if (archivo2.is_open()){
		escribirFilaFich(archivo2, fila, tam);
		archivo2.close();
		cout << endl;
		cout << "La fila se ha guardado en el archivo con éxito" << endl;
		cout << "La fila guardada es la siguiente: " << endl;
		mostrarfila(fila, tam);
	}
	else {
		cout << endl;
		cout << "No se ha podido abrir el archivo" << endl; }   // Preguntar si tiene algun sentido esto en un archivo de salida
																// Preguntar si no tendría más sentido controlar que el nobre introducido acabe en '.txt'

}

void leerFilaFich(istream &fich, tArray fila, int &tam){
	int elem, cont;
	cont = 0;
	fich >> elem;
	while (elem != CENTINELA && cont < MAX_PROD){    // Probar si coge solo 25 elementos
		fila[cont] = elem;
		cont++;
		fich >> elem;
	}
	tam = cont;

}

void escribirFilaFich(ostream &fich, const tArray fila, int tam){
	int i;
	for (i = 0; i < tam; i++){
		if (i < tam - 1){ fich << fila[i] << " "; }  // Pongo el espacio solo si no es el último elemento a escribir
		else { fich << fila[i]; }
	}

}

void mostrarfila(const tArray fila, int tam){
	int i;
	cout << endl;
	for (i = 0; i < tam; i++){
		cout << "|";
		if (fila[i] == PROD_NULO){ cout << setw(2) << " "; }  
		else { cout << setw(2) << fila[i]; }
	}
	cout << "|" << endl;

	for (i = 0; i < (3 * tam + 1); i++){
		cout << "-";
	}
	cout << endl;

	for (i = 0; i < tam; i++){
		cout << "|";          // Para que debajo de la fila me aparezcan las posiciones
		cout << setw(2) << i;
	}
	cout << "|" << endl;
}


bool esPosValida(int tam, int pos){
	bool posesvalida;

	if (pos >= 0 && pos < tam) { posesvalida = true; }
	else { posesvalida = false; }


	return posesvalida;
}

bool estaVacia(const tArray fila, int pos){
	bool estavacia;

	if (fila[pos] == PROD_NULO) { estavacia = true; }
	else { estavacia = false; }

	return estavacia;
}


/*bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar){
	bool esposiblegrua, inivalida, soltarvalida, soltarvacia;

	inivalida = esPosValida(tam, posIni);
	soltarvalida = esPosValida(tam, posSoltar);
	soltarvacia = estaVacia(fila, posSoltar);
	if (inivalida && soltarvalida && soltarvacia) {
		esposiblegrua = true;
	}
	else { esposiblegrua = false; }

	return esposiblegrua;
}
*/

bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar){
	int distanciasegmento, posfinsoltar;
	bool esposiblegrua, inivalida, finvalida, soltarvalida, soltarfinvalida, finalmayorqueinicial;
	distanciasegmento = posFin - posIni;
	if (distanciasegmento < 0) { finalmayorqueinicial = false; }  // Para comprobar que PosFin >= PosIni digo que si distanciasegmento < 0, entonces no se cumple
	else { finalmayorqueinicial = true; }                         // En cambio si distanciasegmento >= 0, PosFin >= PosIni
	posfinsoltar = posSoltar + distanciasegmento;
	inivalida = esPosValida(tam, posIni);
	finvalida = esPosValida(tam, posFin);
	soltarvalida = esPosValida(tam, posSoltar);
	soltarfinvalida = esPosValida(tam, posfinsoltar);

	if (inivalida && finvalida && soltarvalida && soltarfinvalida && finalmayorqueinicial){
		esposiblegrua = true;
	}
	else { esposiblegrua = false; }

	return esposiblegrua;
}


bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar){
	int distanciasegmento, i;
	bool nohaymaterial, pertenecealintervalo;
	distanciasegmento = posFin - posIni;
	nohaymaterial = true;
	i = 0;
	while (i <= distanciasegmento && nohaymaterial){
		pertenecealintervalo = perteneceABloqueLevantado((posSoltar + i), posIni, posFin);     // Pensar en si se puede optimizar
		if (!estaVacia(fila, posIni + i) && !pertenecealintervalo && !estaVacia(fila, posSoltar + i)){ 

																	// No pertenece al intervalo para tener en cuenta que las que he levantado ahora son vacias
			nohaymaterial = false;                                     // Tambien tengo en cuenta si lo que va a caer sobre donde hay matrial es posicion en blanco
		}
		i++;
	}

	return nohaymaterial;

}

bool perteneceABloqueLevantado(int pos, int posIni, int posFin){
	bool pertenecealintervalo;
	if (pos >= posIni && pos <= posFin){ pertenecealintervalo = true; }
	else { pertenecealintervalo = false; }


	return pertenecealintervalo;
}

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar){
	bool movimientohecho, nohaymaterial;
	tArray array;                       
	int i, aux;
	aux = 0;
	nohaymaterial = esPosibleGrua(fila, tam, posIni, posFin, posSoltar);
	if (nohaymaterial) {
		for (i = posIni; i <= posFin; i++){
			array[aux] = fila[i];
			fila[i] = PROD_NULO;					// Los copio en un array auxiliar y pongo un hueco en la correspondiente posicion
			aux++;
		}
		for (i = 0; i < aux; i++){
			if (array[i] != PROD_NULO){
				fila[posSoltar + i] = array[i];	 // Suelto los elementos en las posiciones correspondientes, solo sí son distintos de 0
			}
		}
		movimientohecho = true;
	}
	else { movimientohecho = false; }

	return movimientohecho;
}


/* bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar){
	bool movimientohecho, esposiblegrua;
	esposiblegrua = esPosibleGrua1Entre(fila, tam, posIni, posSoltar);
	if (esposiblegrua){
		fila[posSoltar] = fila[posIni];
		fila[posIni] = PROD_NULO;
		movimientohecho = true;
	}
	else { movimientohecho = false; }
	return movimientohecho;
}
*/

void ejecutarGrua(tArray fila, int tam, bool &movimientohecho){
	int posIni, posFin, posSoltar;
	bool sonposicionesposibles;
	cout << "Indique la posición inicial del bloque de material que quiere levantar: ";
	cin >> posIni;

		while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";
			cin >> posIni;
		}
		cin.sync();


	cout << "Indique la posición final del bloque de material que quiere levantar: ";
	cin >> posFin;

	while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
	{
		cin.clear();
		cin.sync();
		cout << "Dame un entero: ";
		cin >> posFin;
	}
	cin.sync();

	cout << "Indique la posición inicial donde desea soltar el bloque: ";
	cin >> posSoltar;

	while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
	{
		cin.clear();
		cin.sync();
		cout << "Dame un entero: ";
		cin >> posSoltar;
	}
	cin.sync();
	sonposicionesposibles = sonPosicionesPosiblesGrua(tam, posIni, posFin, posSoltar);
	movimientohecho = grua(fila, tam, posIni, posFin, posSoltar);
	if (sonposicionesposibles) {
		cout << "Las posiciones son válidas ";
		if (movimientohecho){
			cout << "y se ha hecho el movimiento" << endl;
			cout << "La fila queda del siguiente modo: " << endl;
			mostrarfila(fila, tam);
		}
		else { 
			cout << "pero no se pudo hacer el movimiento porque hay material donde pretende soltar" << endl; 
			mostrarfila(fila, tam);
		}  // Preguntar si tiene algun sentido este else
	}
	else { 
		cout << "Las posiciones introducidas no son válidas. Alguna está fuera de rango o la inicial es mayor que la final" << endl; 
		mostrarfila(fila, tam);
	}

}

/* int posHuecoLibreDerecha(const tArray fila, int tam, int posIni){
	bool encontrado;
	int i, huecoaladerecha;
	encontrado = false;
	i = posIni;
	while (i < tam && !encontrado){
		if (fila[i] == PROD_NULO) { 
			encontrado = true;
			huecoaladerecha = i;
		}
		i++;
	}
	if (!encontrado){ huecoaladerecha = tam; }
	return huecoaladerecha;
}
*/

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion){
	int i, primerhuecolibre;
	bool encontrado;
	encontrado = false;
	i = posIni;
	while (i < tam && i >= 0 && !encontrado){
		if (estaVacia(fila, i)) {
			encontrado = true;
			primerhuecolibre = i;
		}
		i = i + direccion;
	}
	if (!encontrado){ primerhuecolibre = tam; }

	return primerhuecolibre;
}

/*
bool excavadora1Derecha(tArray fila, int tam, int posIni){
	int i, huecoaladerecha;
	bool desplazamientohecho;
	huecoaladerecha = posHuecoLibreDerecha(fila, tam, posIni);
	if (huecoaladerecha != tam){
		for (i = huecoaladerecha; i > posIni; i--){
			fila[i] = fila[i - 1];
		}
		fila[posIni] = PROD_NULO;
		desplazamientohecho = true;
	}
	else { desplazamientohecho = false; }

	return desplazamientohecho;
}
*/

bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion){   //	Devuelve si se ha hecho al menos un desplazamiento
	int i, primerhuecolibre;
	bool desplazamientohecho, desplazamientoposible;
	primerhuecolibre = posHuecoLibreDir(fila, tam, posIni, direccion);
	i = primerhuecolibre;
	desplazamientoposible = alMenosUnMovimientoExcavadora(primerhuecolibre, tam);
	if (desplazamientoposible){
		while (i != posIni){
			fila[i] = fila[i - direccion];
			i = i - direccion;
		}
		fila[posIni] = PROD_NULO;
		desplazamientohecho = true;
	}
	else { desplazamientohecho = false; }
	return desplazamientohecho;
}


void ejecutarExcavadora(tArray fila, int tam, bool &movimientohecho){
	int posIni, direccion, numDespla, primerhuecolibre;
	bool todolosdesplazamientoshechos, esposvalida, algunmovimiento;

	cout << "Introduzca la posición desde donde empujará la excavadora: ";
	cin >> posIni;
	esposvalida = esPosValida(tam, posIni);
	while (!esposvalida){
		cout << "Introduce una posición que pertenezca a las de la fila. " << "Entre 0 y " << (tam-1) << ": ";
		cin >> posIni;
		esposvalida = esPosValida(tam, posIni);
		while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";
			cin >> posIni;
		}
		cin.sync();
	}

	cout << "Introduzca la dirección (1 para la derecha, -1 para la izquierda): ";
	cin >> direccion;     

	while (direccion != 1 && direccion != -1){       // Meto un bucle dentro de otro para que si mete un numero no valido y luego algo que no sea un entero, nose vuelva loco
	
		cout << "La opción introducida no es válida, por favor introduzca una dirección correcta (1 o -1): ";
		cin >> direccion;
		while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";
			cin >> direccion;
		}
		cin.sync();
	}

	cout << "Introduzca el nº de desplazamientos a realizar: ";
	cin >> numDespla;      
	while (numDespla <= 0){

		cout << "Por favor, introduzca un número estrictamente positivo de desplazamientos: ";
		cin >> numDespla;

		while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";     // Preguntar si tanto bucle es muy ineficiente
			cin >> numDespla;
		}
		cin.sync();
	}
	primerhuecolibre = posHuecoLibreDir(fila, tam, posIni, direccion);
	algunmovimiento = alMenosUnMovimientoExcavadora(primerhuecolibre, tam);
	movimientohecho = algunmovimiento;
	todolosdesplazamientoshechos = excavadora(fila, tam, posIni, numDespla, direccion);

	if (todolosdesplazamientoshechos){
		cout << endl;
		cout << "Se han realizado todos los movimientos." << endl;
		cout << "La fila ha quedado del siguiente modo: " << endl;
		mostrarfila(fila, tam);
	}
	else if (algunmovimiento){
		cout << endl;
		cout << "No se han podido hacer todos los desplazamientos, pero sí alguno." << endl << "Revise la posición inicial y el número de movimientos introducidos" << endl;
		cout << "La fila ha quedado del siguiente modo: " << endl;
		mostrarfila(fila, tam);
	}
	else { 
		cout << endl;
		cout << "No se ha podido realizar ningún desplazamiento. No se pueden empujar materiales contra la pared." << endl;
		mostrarfila(fila, tam);
	}

}
bool alMenosUnMovimientoExcavadora(int primerhuecolibre, int tam){
	bool algunmovimiento;
	if (primerhuecolibre != tam){ algunmovimiento = true; }
	else { algunmovimiento = false; }                             // No hace movimientos. Tan solo me indica si se va a poder hacer al menos uno
	return algunmovimiento;
}

bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion){  // Preguntar lo de este parámetro por referencia
	bool todosdesplazamientoshechos, desplazamientoposible;
	int i;
	i = 0;
	do { 
		desplazamientoposible = excavadora1Dir(fila, tam, posIni + (direccion * i), direccion); 
		i++;     
	} 
	while (i < numDespla && desplazamientoposible);
	if (desplazamientoposible){ todosdesplazamientoshechos = true; }
	else{ todosdesplazamientoshechos = false; }

	return todosdesplazamientoshechos;    // Preguntar que es exactamente lo que tiene que devolver
}


bool filaOrdenada(const tArray fila, int tam){
	int i, m; 
	tArray aux;                            // Preguntar si se puede hacer sin el array auxiliar (Es necesario obviar los ceros)
										// Lo declaramos con tipo tArray, ya que podría haber hasta 25 materiales en la fila
	bool ordenada;
	i = 0;
	m = 0;
	ordenada = true;
	for (i = 0; i < tam; i++){
		if (!estaVacia(fila, i)){
			aux[m] = fila[i];
			m++;
		}
	}
	i = 1;
	while (i < m && ordenada){
		if (aux[i] < aux[i - 1]){ ordenada = false; }
		i++;
	}

	return ordenada;
}