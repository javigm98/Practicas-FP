#include <iostream>
#include <cmath>     // Declaramos las bibliotecas
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int solicitaAnyo();
int solicitaMes();
int solicitaDia(int mes, int anyo);
int diasMes(int mes, int anyo);
bool esBisiesto(int anyo);
int contarBisiestos(int anyoInicio, int anyoFinal);   // Prototipamos las funciones
int diasEsteAnyo(int dia, int mes, int anyo);
long int diasTranscurridos(int dia, int mes, int anyo);
long int diasAnyosCompletos(int anyo);
int diaSemana(long int numDias);
string nombreDia(int representacionDia);
int Menu();
int primerDomingoMes(int mes, int anyo);
int primerDomingoanyo(int anyo);
int domingosAnyo(int anyo);
bool puentes();

int main(){
	int m, a, d, diames, contadorbisiestos, diasesteanyo, representaciondia, menu;
	long int diastotales;
	string nombredia;
	bool bisiesto, diaspuente;
	menu = Menu();
	while (menu != 0){
		switch (menu)
		{
		case 1: {
			a = solicitaAnyo();
			m = solicitaMes();
			bisiesto = esBisiesto(a);   // Llamamos a las funciones y establecemos relaciones entre ellas
			diames = diasMes(m, a);
			d = solicitaDia(m, a);
			contadorbisiestos = contarBisiestos(1900, a);
			diasesteanyo = diasEsteAnyo(d, m, a);
			diasAnyosCompletos(a);
			diastotales = diasTranscurridos(d, m, a);
			representaciondia = diaSemana(diastotales);
			nombredia = nombreDia(representaciondia);
		}
				break;

		case 2: {
			a = solicitaAnyo();
			primerDomingoanyo(a);

		}
				break;

		case 3:	{
			a = solicitaAnyo();
			domingosAnyo(a);
		}
				break;
		case 4: {diaspuente = puentes(); }

		}
		menu = Menu();
	}
	

	
	

	return 0;
}

int Menu(){
	int opcion;
	opcion = -1;

	while (opcion < 0 || opcion > 4){
		cout << endl;
		cout << "Por favor, escoja una de las siguientes opciones: " << endl;
		cout << "1 - Calcular el dia de la semana para una fecha dada" << endl;
		cout << "2 - Obtener la fecha correspondiente al primer domingo de un anyo" << endl;
		cout << "3 - Obtener los domingos de un anyo" << endl;
		cout << "4 - Obtener los posibles puentes de un anyo" << endl;
		cout << "0 - Salir" << endl;
		cin >> opcion;

		while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";
			cin >> opcion;
		}
		cin.sync();
		if (opcion < 0 || opcion > 4) { cout << "Opcion no valida" << endl; }
	}

	return opcion;
}


int solicitaAnyo(){   // Esta función solicita y valida un año posterior a 1900
	int anyo;
	cout << "Introduzca un anyo igual o posterior a 1900: ";
	cin >> anyo;
	while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
	{
		cin.clear();
		cin.sync();
		cout << "Dame un entero: ";
		cin >> anyo;
	}
	cin.sync();
	while (anyo < 1900){   // En el caso de que el usuario introduzca un año inferior al pedido, entra en juego este bucle
		cout << "Por favor, introduzca un anyo correcto, que sea mayor o igual que 1900: ";
		cin >> anyo;

	}
	if (anyo >= 1900) {   // En el caso de que el usuario introduzca un año correcto, se devuelve un mensaje que lo corrobora
		cout << "El anyo " << anyo << " que ha introducido es correcto. " << endl;
	}
	return anyo;
}


int solicitaMes(){
	int mes;
	cout << "Introduzca el numero correspondiente al mes del anyo: ";
	cin >> mes;
	while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
	{
		cin.clear();
		cin.sync();
		cout << "Dame un entero: ";
		cin >> mes;
	}
	cin.sync();
	while (mes < 1 || mes > 12){    /* En el caso de que el usuario introduzca un mes 
									fuera del rango correcto (1-12), se entra en este bucle */

		cout << "Por favor, introduzca un mes correcto, entre 1 y 12: ";
		cin >> mes;
	}

	if (mes >= 1 && mes <= 12) {   // En el caso de que el usuario introduzca un mes correcto, se devuelve un mensaje que lo corrobora

		cout << "El mes " << mes << " que ha introducido es correcto. " << endl;
	}
	return mes;
}
int solicitaDia(int mes, int anyo){
	int dia, diasdelmes;
	diasdelmes = diasMes(mes, anyo);
	cout << "Introduce el dia del mes: ";
	cin >> dia;
	while (cin.fail())    // En el caso de que el usuario no introduzca un entero, se entra en este bucle
	{
		cin.clear();
		cin.sync();
		cout << "Dame un entero: ";
		cin >> dia;
	}
	cin.sync();

	while ((dia > diasdelmes) || (dia <= 0)){ 
		// Se coteja el entero con la función diasMes y si es incorrecto , se entra en este bucle
		cout << "Por favor, introduzca un dia correcto: ";
		cin >> dia;
	}
	if ((dia <= diasdelmes) && (dia > 0)) { cout << "El dia " << dia << " es correcto"<< endl; }
		// Se coteja el entero con la función diasMes y si es correcto , se devuelve un mensaje que lo corrobora
	return dia;
}

int diasMes(int mes, int anyo){
	int diasmes;
	bool bisiesto;
	bisiesto = esBisiesto(anyo);
	switch (mes) {   // Dependiendo del mes introducido asignamos el valor correspondiente a sus días
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: {diasmes = 31; }
			 break;
	case 4:
	case 6:
	case 9:
	case 11: {diasmes = 30; }
			 break;
	case 2: { if (bisiesto){ diasmes = 29; }	/* En el caso de febrero, además cotejamos con la función esBisiesto,
															para concretar si tiene 28 o 29 días */
			else { diasmes = 28; } }
	}
	return diasmes;
}


	bool esBisiesto(int anyo){		/* En esta función introducimos las condiciones necesarias para que un año sea bisiesto
									con la ayuda de un if y se devuelva entonces si el introducido por el usuario lo es o no */
		bool esbisiesto;
		if (((anyo % 4 == 0) && (anyo % 100 != 0)) || (anyo % 400 == 0)) { esbisiesto = true; }
		else { esbisiesto = false; }
		return esbisiesto;
	}

	int contarBisiestos(int anyoInicio, int anyoFinal){

		/* Esta función evalua las condiciones necesarias para que un año sea bisiesto, 
		llamando a la función esBisiesto, año por año desde el 1900 hasta el introducido por el usuario */

		int i, contador;
		contador = 0;
		for (i = 1900; i <= anyoFinal; i++){if (esBisiesto(i)) { contador++; }}  /* Este bucle 'for' permite pasearse desde el año inicial (1900), 
																				hasta el introducido por el usuario, de manera que si es bisieto lo refleje
																				aumentando en uno a una variable contador inicializada en 0 */

																                  /* Aunque se incluye el propio año final, puesto que el enunciado indica un 
																				intervalo cerrado  de años, en el caso de que este sea bisitesto, el día 
																				adicional lo sumará la función diasEsteAnyo que tiene en cuenta el mes,
																				y no esta función, que servirá para contabilizar los días adicionales de los
																				años bisiestos anteriores.*/
		return contador;
	}
	
	int diasEsteAnyo(int dia, int mes, int anyo){

		/* Esta función devuelve el numero de dias transcurridos desde el 1 de enero del año introducido,
		llamando a la función diasMes, para así tener en cuenta si los meses que preceden tienen 30 o 31 días
		y en el caso de febrero también si es bisiesto o no (en diasMes se llamaba a esBisiesto) */

		int diasesteanyo, i, diasmesesenteros;
		diasmesesenteros = 0;
		for (i = 1; i < mes; i++){            // Este bucle 'for' permite pasearse por los meses desde el primero hasta el que precede al mes introducido
			if (mes != 1) { 
				diasmesesenteros = diasmesesenteros + diasMes(i, anyo);    /* Se inicializa diasmesesenteros en 0, para que cuando se repita el bucle, se puedan sumar
																		   los días del nuevo mes a los ya acumuladores de manera recursiva */
				diasesteanyo = diasmesesenteros + dia;}
		}
			if (mes == 1) { diasesteanyo = dia; }		// En el caso del mes de enero solo hay que tener en cuenta el día introducido
		
		return diasesteanyo;
	}



	long int diasAnyosCompletos(int anyo){

		/* Esta función calcula el número de días totales entre los años 1900 (incluido) y el actual (sin incluir)
		llamando a la función contarBisiestos, para así tener en cuenta cuantos no tienen 365 sino 366 días */

		long int diasanyoscompletos;
		int numerodebisiestos, nobisiestos, periododeanyos;
		if (esBisiesto(anyo)) { numerodebisiestos = contarBisiestos(1900, anyo) - 1 ; }

		/* Puesto que en la función contarBisiestos se incluyó el año introducido por el usuario en el rango a evaluar, si el último año es bisiesto
		vamos a descartarlo, pues únicamente nos interesan los bisietos completos y por tanto no el último año.
		En el caso de que el usuario introduzca un día posterior al 29 de febrero, la función diasEsteAnyo llamando a diasMes que a su vez depende
		de esBisiesto, ya tiene en cuenta este día adicional y se sumará por tanto en el total de diasTranscurridos */

		else { numerodebisiestos = contarBisiestos(1900, anyo); }
		periododeanyos = anyo - 1900;
		nobisiestos = periododeanyos - numerodebisiestos;
	
		diasanyoscompletos = (numerodebisiestos * 366) + (nobisiestos * 365);
		return diasanyoscompletos;
	}

	long int diasTranscurridos(int dia, int mes, int anyo){

		/* Esta función simplemente tiene la finalidad de devolver el total de días transcurridos entre el 1 de enero de 1900 
		y el día introducido por el usuario, llamando a las funciones diasAnyosCompletos y diasEsteAnyo y sumando los enteros que devuelven. */

		long int diastranscurridos, diasesteanyo, diasanyoscompletos;
		diasesteanyo = diasEsteAnyo(dia, mes, anyo);
		diasanyoscompletos = diasAnyosCompletos(anyo);

		diastranscurridos = diasesteanyo + diasanyoscompletos -1;

		/* Puesto que se tiene en cuenta en el total de días transcurridos tanto el día final como el inicial, restamos uno para calcular la representación
		del día de la semana. De esta forma entre el lunes (1/01/1900) y otro lunes habrán transcurrido un numero de días múltiplo de 7 y un resto 0 al dividir
		por 7 este numero de días, será la señal inequevica de que el día introducido es un lunes. */

		return diastranscurridos;
	}

	int diaSemana(long int numDias){
		int diasemana;
		diasemana = (numDias) % 7;
		return diasemana;
	}

	string nombreDia(int representacionDia){

		/* De manera obvia, se deduce que si un valor 0 de vuelta en la función diaSemana equivalía a un lunes, 
		el valor 1 equivale a un martes, el valor 2 a un miércoles y así de manera sucesiva. Asociamos estas representaciones enteras a la cadena correspondiente
		mediante un switch que considere los posibles casos (restos del 0 al 6). */

		string nombredia;
		switch (representacionDia)
		{
		case 0: {nombredia = "Lunes"; }
				break;
		case 1: {nombredia = "Martes"; }
				break;
		case 2: {nombredia = "Miercoles"; }
				break;
		case 3: {nombredia = "Jueves"; }
				break;
		case 4: {nombredia = "Viernes"; }
				break;
		case 5: {nombredia = "Sabado"; }
				break;
		case 6: {nombredia = "Domingo"; }
		}
		cout << nombredia << endl;
		return nombredia;
	}

	
	int primerDomingoMes(int mes, int anyo){
		long int dias1900hasta1mes;
		int representacion1mes, primerdomingomes;
		dias1900hasta1mes = diasTranscurridos(1, mes, anyo);
		representacion1mes = diaSemana(dias1900hasta1mes);
		primerdomingomes = 7 - representacion1mes;

		return primerdomingomes;
	}

	int primerDomingoanyo(int anyo){
		int primerdomingoanyo;

		primerdomingoanyo = primerDomingoMes(1, anyo);
		cout << "El primer domingo del anyo 2017 es el dia: " << primerdomingoanyo << " de enero" << endl;

		return primerdomingoanyo;

	}

	string nombreMes(int mes){

		string nombremes;
		switch (mes)
		{
		case 1: {nombremes = "enero"; }
				break;
		case 2: {nombremes = "febrero"; }
				break;
		case 3: {nombremes = "marzo"; }
				break;
		case 4: {nombremes = "abril"; }
				break;
		case 5: {nombremes = "mayo"; }
				break;
		case 6: {nombremes = "junio"; }
				break;
		case 7: {nombremes = "julio"; }
				break;
		case 8: {nombremes = "agosto"; }
				break;
		case 9: {nombremes = "septiembre"; }
				break;
		case 10: {nombremes = "octubre"; }
				 break;
		case 11: {nombremes = "noviembre"; }
				 break;
		case 12: {nombremes = "diciembre"; }

	
		}
		return nombremes;
	}


	int domingosAnyo(int anyo){
		int i, primerdomingomes, cont;
		cont = 0;
		cout << "Domingos de " << anyo << endl;
		for (i = 1; i <= 12; i++){
			primerdomingomes = primerDomingoMes(i, anyo);
			for (primerdomingomes; primerdomingomes <= diasMes(i, anyo); primerdomingomes = primerdomingomes + 7){
				cout << primerdomingomes << " de " << nombreMes(i) << endl;
				cont++;
			}
		}
		cout << "Numero total de domingos: " << cont << endl;

		return primerdomingomes;
	}
	bool puentes() {
		bool espuente;
		int dia, mes, anyo, representacion;
		long int diastranscurridos;
		string nombredia;
		ifstream archivo;
		ofstream archivo2;
		archivo.open("fiestas.txt");
		if (archivo.is_open()){
			archivo2.open("puentes.txt");
			archivo >> anyo;
			archivo2 << anyo << endl;
			archivo >> dia >> mes;
			while (dia != 0){
				diastranscurridos = diasTranscurridos(dia, mes, anyo);
				representacion = diaSemana(diastranscurridos);
				nombredia = nombreDia(representacion);
				if (representacion == 1 || representacion == 3){
					espuente = true;
				}
				else { espuente = false; }
				if (espuente){
					archivo2 << dia << " " << mes << " " << nombredia << endl;;
				}
				archivo >> dia >> mes;
			}
			archivo2 << "0 0 XXX" << endl;
			archivo.close();
			archivo2.close();
		}
		else {
			cout << "Error: no se ha podido abrir el archivo" << endl;
		}
		cout << "Se ha creado un archivo con el nombre puentes.txt" << endl;

		return espuente;
	}




	

