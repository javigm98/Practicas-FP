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
const int DIR_DERECHA = 1;
const int DIR_IZQDA = -1;
typedef int tArray[MAX_PROD];


int menu();
void ejecutarOpc(int opc, tArray fila, int &tam, int &movimientos);
/* Esta función recibe un entero que indica la opción escogida en el menú 
y a través de un switch ejecuta el código asociado a dicha opción*/

void ejecutarLeerFichero(tArray fila, int &tam);
/* Esta función pide al usuario el nombre del fichero que desea abrir, lo abre y lo lee llamando a la funcion leerfilafcih */

void ejecutarGuardarfichero(const tArray fila, int tam);
/* Pide al usuario el nombre del archivo donde desea guardar la fila cargada, controlando que sea un archivo ".txt"
y escribe el contenido de la fila en él llamando a la funcion escribirfilafich */

void mostrarfila(const tArray fila, int tam);
/* Muestra la fila actual en el formato indicado en el enunciado de la practica*/

bool esPosValida(int tam, int pos);
/* Comprueba que una posicion está dentro del intervalo [0, tam) */

bool estaVacia(const tArray fila, int pos);
/* Comprueba que en una posicion de la fila no haya un cero */

void leerFilaFich(istream &fich, tArray fila, int &tam);
/* Lee valores enteros de un fichero ya abierto y los almacena en un array, mientras no se encuentre con el centinela 
o sobrepase el tamaño máximo del array */

void escribirFilaFich(ostream &fich, const tArray fila, int tam);
/* Escribe los valores almacenados en el array fila en un archivo de salida ya abierto, 
e introduce el centinela para que el mismo puede ser usado para entrada de datos */

// bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar);

bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar);
/* Esta función chequea que las posiciones introducidas para la grua están en rango válido (llamando a sonposicionesposibles)
y que no haya material en las posciones donde lo pretende soltar, controlando tanto solpamientos como que se suelte una posicion vacía */

bool perteneceABloqueLevantado(int pos, int posIni, int posFin);  // CREADA POR NOSOTROS
/*Controla si una de las posiciones sobre la que van a caer materiales pertenece al intervalo de las que se levantan 
(para controlar el solapamiento de la grua) y duevuelve un booleano informando sobre ello */

bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar);
/* Devuelve si el segmento a levantar no tiene su extremo derecho antes que el izquierdo 
y si todas las posiciones involucradas son válidas en la fila de tamaño tam. (Comprobandolo para los 4 extremos involucrados llamando a esPosValida) */

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar);
/* Recibe de la funcion esposiblegrua un booleano que indica si el movimiento es posible y en caso afirmativo lo realiza. 
Para ello utiliza un array auxiliar en el que se guardan los elementos levantados. Después se sustituyen por huecos vacíos
sus correspondientes posiciones en el array principal y por último se sustituyen en las posiciones de caida seleccionadas.*/

// bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar);

void ejecutarGrua(tArray fila, int tam, bool &movimientohecho);
/* Esta función pide al usuario los datos necesarios para el funcionamiento de la grua, 
y llama a la función que realiza el movimiento informando al usuario sobre si este se ha podido o no realizar */

// int posHuecoLibreDerecha(const tArray fila, int tam, int posIni);

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);
/* Devuelve la posición del primer hueco libre de la fila desde la posición y hacia la dirección indicadas.
En caso de no encontrar ninguno, devuelve tam como posición.*/

bool alMenosUnMovimientoExcavadora(int primerhuecolibre, int tam);  // CREADA POR NOSOTROS
/* Esta función nos permite diferenciarle al usuario entre que se haya podido hacer algún movimiento, pero no todos, 
o que directamente no se haya realizado ninguno. Recibe como parámetro el entero que indica el primer hueco libre en la direccion seleccionada 
y siempre que sea distinto de tamaño indica que al menos se realizará un movimiento.*/

// bool excavadora1Derecha(tArray fila, int tam, int posIni);

bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion);
// Desplaza los movimientos comprendidos entre la poscion introducida y el primer hueco libre una posicion en la dirección indicada, si es posible.

void ejecutarExcavadora(tArray fila, int tam, bool &movimientohecho);
/* Esta función pide alusuario los datos necesarios para la excavadora, llama a las funciones booleanas anteriores
(realizando los correspondientes movimientos) e indica al usuario si se han podido realizar algunos, todos o ninguno. */

bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion); 
/* Esta función llama a la función que ejecuta los movimientos (de uno en uno) siempre y cuando el anterior se haya podido realiza y no se excedan
el numero de despalzamientos introducidos por el usuario. Asimismo, devuelve si se han podido hacer todos los movimientos introducidos. */

bool filaOrdenada(const tArray fila, int tam);
// Con esta función comprobamos si los elementos no nulos de la fila están en orden ascendente.

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
		// Pensar como inicializar lo de movimientos
		switch (opc)
		{
		case 1: {
			ejecutarLeerFichero(fila, tam);
			movimientos = 0;
			cout << "hahha"
			if (tam != 0){
				mostrarfila(fila, tam);
			}
		}
				break;
		case 2: {
			ejecutarGuardarfichero(fila, tam);
			mostrarfila(fila, tam);
		}
				break;
		case 3: {
			if (tam != 0){
				ejecutarGrua(fila, tam, movimientohecho);
				mostrarfila(fila, tam);
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
				mostrarfila(fila, tam);
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
			archivo.close();
	}
	else { 
		cout << endl;
		cout << "El archivo no se pudo abrir" << endl;
		tam = 0;
		cout << "La fila ha sido reinicializada como vacía." << endl;
	}

}


void ejecutarGuardarfichero(const tArray fila, int tam){
	string ficherosalida;
	bool acabaentxt;
	ofstream archivo2;
	cout << "Introduzca el nombre del fichero donde desea guardar la fila, acabado en '.txt': ";
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
	}
	else {
		cout << endl;
		cout << "No se ha podido abrir el archivo y por tanto la fila no se guardó." << endl; }   // Preguntar si tiene algun sentido esto en un archivo de salida
																// Preguntar si no tendría más sentido controlar que el nobre introducido acabe en '.txt'

}

void leerFilaFich(istream &fich, tArray fila, int &tam){
	int elem, cont;
	cont = 0;
	fich >> elem;
	while (elem != CENTINELA && cont < MAX_PROD){   
		fila[cont] = elem;
		cont++;
		fich >> elem;
	}
	tam = cont;

}

void escribirFilaFich(ostream &fich, const tArray fila, int tam){
	int i;
	for (i = 0; i < tam; i++){
		fich << fila[i] << " ";
	}
	fich << CENTINELA;
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
	bool gruarealizable, pertenecealintervalo, posvalidas;
	distanciasegmento = posFin - posIni;
	gruarealizable = true;
	i = 0;
	posvalidas = sonPosicionesPosiblesGrua(tam, posIni, posFin, posSoltar);
	if (posvalidas){
		while (i <= distanciasegmento && gruarealizable){
			pertenecealintervalo = perteneceABloqueLevantado((posSoltar + i), posIni, posFin);     // Pensar en si se puede optimizar
			if (!estaVacia(fila, posIni + i) && !pertenecealintervalo && !estaVacia(fila, posSoltar + i)){

				// No pertenece al intervalo para tener en cuenta que las que he levantado ahora son vacias
				gruarealizable = false;                                     // Tambien tengo en cuenta si lo que va a caer sobre donde hay matrial es posicion en blanco
			}
			i++;
		}
	}
	else { gruarealizable = false; }

	return gruarealizable;

}

bool perteneceABloqueLevantado(int pos, int posIni, int posFin){ /* AÑADIDA POR NOSOTROS. Nos dice si una posición pertenece a las levantadas con la grúa 
																	utilizandose para comprobar que el segmento levantado no solape consigo mismo */
	bool pertenecealintervalo;
	if (pos >= posIni && pos <= posFin){ pertenecealintervalo = true; }
	else { pertenecealintervalo = false; }


	return pertenecealintervalo;
}

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar){
	bool movimientohecho, gruarealizable;
	tArray array;                       
	int i, aux;
	aux = 0;
	gruarealizable = esPosibleGrua(fila, tam, posIni, posFin, posSoltar);
	if (gruarealizable) {
		for (i = posIni; i <= posFin; i++){
			array[aux] = fila[i];
			fila[i] = PROD_NULO;					// Los copio en un array auxiliar y pongo un hueco en la correspondiente posicion
			aux++;
		}
		for (i = 0; i < aux; i++){
			if (!(estaVacia(array, i))){
				fila[posSoltar + i] = array[i];	 // Suelto los elementos en las posiciones correspondientes, solo si son distintos de 0
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

	movimientohecho = grua(fila, tam, posIni, posFin, posSoltar);

		if (movimientohecho){
			cout << "Las posiciones son válidas y se ha hecho el movimiento" << endl;
			cout << "La fila queda del siguiente modo: " << endl;
		}
		else { 
		cout << "Las posiciones introducidas no son válidas." << endl << "Alguna fuera de rango, la inicial es mayor que la final o hay material donde desea soltar" << endl; 
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
	if (!encontrado){ primerhuecolibre = tam; } // Devolvemos 'tam' siempre que no haya ningún hueco libre en la direccion introducida

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

bool alMenosUnMovimientoExcavadora(int primerhuecolibre, int tam){
	bool algunmovimiento;
	if (primerhuecolibre != tam){ algunmovimiento = true; }
	else { algunmovimiento = false; }                             // No hace movimientos. Tan solo me indica si se va a poder hacer al menos uno
	return algunmovimiento;
}

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
		desplazamientohecho = desplazamientoposible;
	}
	else { desplazamientohecho = desplazamientoposible; }
	return desplazamientohecho;
}

bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion){  
	bool todosdesplazamientoshechos, desplazamientoposible;
	int i;
	i = 0;
	do {
		desplazamientoposible = excavadora1Dir(fila, tam, posIni + (direccion * i), direccion); /* Esta función a la que llamo, ya me comprueba
																								si se puedo hacer el movimiento y lo hace en caso afirmativo */
		i++;
	} while (i < numDespla && desplazamientoposible);
	if (desplazamientoposible){ todosdesplazamientoshechos = true; }     /* Si una vez sale del bucle este booleano es true, es porque i = numDespla
																			y se han hecho todos los desplazamientos */
	else{ todosdesplazamientoshechos = false; }

	return todosdesplazamientoshechos;
}


void ejecutarExcavadora(tArray fila, int tam, bool &movimientohecho){
	int posIni, direccion, numDespla, primerhuecolibre;
	bool todolosdesplazamientoshechos, esposvalida, algunmovimiento;

	cout << "Introduzca la posición desde donde empujará la excavadora: ";
	cin >> posIni;
		while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";
			cin >> posIni;
		}
		cin.sync();

	cout << "Introduzca la dirección (" << DIR_DERECHA << " para la derecha, " << DIR_IZQDA << " para la izquierda): ";
	cin >> direccion;     

	while (direccion != DIR_DERECHA && direccion != DIR_IZQDA){       // Meto un bucle dentro de otro para que si mete un numero no valido y luego algo que no sea un entero, nose vuelva loco
	
		cout << "La opción introducida no es válida, por favor introduzca una dirección correcta (" << DIR_DERECHA << " o " << DIR_IZQDA << "): ";
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
	esposvalida = esPosValida(tam, posIni);
	primerhuecolibre = posHuecoLibreDir(fila, tam, posIni, direccion);
	algunmovimiento = alMenosUnMovimientoExcavadora(primerhuecolibre, tam);
	movimientohecho = algunmovimiento;  /* Llamamos a todas estas funciones para diferenciar entre hacer solo algún movimiento, hacerlos todos,
										ninguno debido a la posición inicial, o ninguno debido a toparse con el muro */
	todolosdesplazamientoshechos = excavadora(fila, tam, posIni, numDespla, direccion);



	if (!esposvalida){
		cout << endl;
		cout << "La posición introducida para empezar a empujar no es válida" << endl;
		mostrarfila(fila, tam);
	}
	else if (todolosdesplazamientoshechos){
		cout << endl;
		cout << "Se han realizado todos los movimientos." << endl;
		cout << "La fila ha quedado del siguiente modo: " << endl;
	}
	else if (algunmovimiento){
		cout << endl;
		cout << "No se han podido hacer todos los desplazamientos, pero sí alguno." << endl << "Revise el número de movimientos introducidos" << endl;
		cout << "La fila ha quedado del siguiente modo: " << endl;
	}
	else { 
		cout << endl;
		cout << "No se ha podido realizar ningún desplazamiento. No se pueden empujar materiales contra la pared." << endl;
	}

}


bool filaOrdenada(const tArray fila, int tam){
	int i, elem; 
	tArray aux;                            // Preguntar si se puede hacer sin el array auxiliar (Es necesario obviar los ceros)
										// Lo declaramos con tipo tArray, ya que podría haber hasta 25 materiales en la fila
	bool ordenada;
	elem = 0;
	i = 0;
	ordenada = true;
	while (ordenada && i < tam){
		if (!estaVacia(fila, i)){
			if (fila[i] > elem) {
				elem = fila[i];
			}
			else {
				ordenada = false;
			}
		}
		i++;
	}

	return ordenada;
}