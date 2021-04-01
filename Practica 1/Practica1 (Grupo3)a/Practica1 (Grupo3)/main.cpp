/*
Grupo 03 - Doble Grado en Ingeniería Informática y Matemáticas
	 Integrantes del grupo: 
		- Javier Guzmán Muñoz
		- Jorge Villarrubia Elvira
*/

#include <iostream>
#include <cmath>     // Declaramos las bibliotecas
#include <string>
#include <fstream>
#include <iomanip>
#include <locale>
using namespace std;
int menu();
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
string diaDeLaSemana(int dia, int mes, int anyo);
int primerDomingoMes(int mes, int anyo);
string NombreMes(int mes);
int domingosAnyo(int anyo);
bool puentes();
const int AnyoInicial = 1900;
const int Enero = 1;
const int Diciembre = 12;
const int NumDiasSemana = 7;
const int DiasAnyoBisiesto = 366;
const int DiasAnyoNoBisiesto = 365;

int main(){
	setlocale(LC_ALL, "spanish");
	system("chcp 1252");
	int opcion;
	opcion = menu();
	while (opcion != 0){

		/* Si el return del menú es distinto de 0, se entra en este bucle while donde, mediante un switch,
		se asignan distintas funciones a la opción elegida. Con la función menu(), ya nos hemos asegurado de que 
		los únicos casos posibles están en el intervalo [0,4] */

		switch (opcion) {
		case 1: {
			cout << "Ha elegido calcular el día de la semana para una fecha dada." << endl;
			int m, a, d, diames, contadorbisiestos, diasesteanyo, representaciondia;
			long int diastotales;
			string nombredia, diadelasemana, nombremes;
			bool bisiesto;
			a = solicitaAnyo();
			m = solicitaMes();
			bisiesto = esBisiesto(a);   // Llamamos a las funciones y establecemos relaciones entre ellas
			diames = diasMes(m, a);
			d = solicitaDia(m, a);
			contadorbisiestos = contarBisiestos(AnyoInicial, a);
			diasesteanyo = diasEsteAnyo(d, m, a);
			diasAnyosCompletos(a);
			diastotales = diasTranscurridos(d, m, a);
			representaciondia = diaSemana(diastotales);
			nombredia = nombreDia(representaciondia);
			nombremes = NombreMes(m);
			diadelasemana = diaDeLaSemana(d, m, a);
		}
				break;
		case 2: {
			cout << "Ha elegido obtener la fecha correspondiente al primer domingo de un año." << endl;
			int a, primerdomingoanyo;
			a = solicitaAnyo();
			primerdomingoanyo = primerDomingoMes(Enero, a);
			cout << "El primer domingo del año " << a << " es el día: " << primerdomingoanyo << " de enero." << endl;
		}
				break;
		case 3: {
			cout << "Ha elegido obtener todos los domingos de un año." << endl;
			int a = solicitaAnyo();
			int domingosanyo = domingosAnyo(a);
		}
				break;
		case 4: {
			cout << "Ha elegido obtener los posibles puentes de un año." << endl;
			bool diaspuentes = puentes();
		}
		}
		opcion = menu();
	}
						// Si la opción elegida en el menú es 0,  se sale del programa.
	return 0;
}
int solicitaAnyo(){   // Esta función solicita y valida un año posterior a 1900
	int anyo;
	cout << "Introduzca un año igual o posterior a 1900: ";
	cin >> anyo;
	while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
	{
		cin.clear();
		cin.sync();
		cout << "Dame un entero: ";
		cin >> anyo;
	}
	cin.sync();
	while (anyo < AnyoInicial){   // En el caso de que el usuario introduzca un año inferior al pedido, entra en juego este bucle
		cout << "Por favor, introduzca un año correcto, que sea mayor o igual que 1900: ";
		cin >> anyo;

	}
	if (anyo >= AnyoInicial) {   // En el caso de que el usuario introduzca un año correcto, se devuelve un mensaje que lo corrobora
		cout << "El anyo " << anyo << " que ha introducido es correcto. " << endl;
	}
	return anyo;
}
int solicitaMes(){
	int mes;
	cout << "Introduzca el número correspondiente al mes del año: ";
	cin >> mes;
	while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
	{
		cin.clear();
		cin.sync();
		cout << "Dame un entero: ";
		cin >> mes;
	}
	cin.sync();
	while (mes < Enero || mes > Diciembre){    /* En el caso de que el usuario introduzca un mes
									fuera del rango correcto (1-12), se entra en este bucle */

		cout << "Por favor, introduzca un mes correcto, entre 1 y 12: ";
		cin >> mes;
	}

	if (mes >= Enero && mes <= Diciembre) {   // En el caso de que el usuario introduzca un mes correcto, se devuelve un mensaje que lo corrobora

		cout << "El mes " << mes << " que ha introducido es correcto. " << endl;
	}
	return mes;
}
int solicitaDia(int mes, int anyo){
	int dia, diasdelmes;
	diasdelmes = diasMes(mes, anyo);
	cout << "Introduzca el día del mes: ";
	cin >> dia;

	while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
	{
		cin.clear();
		cin.sync();
		cout << "Dame un entero: ";
		cin >> dia;
	}
	cin.sync();


	while ((dia > diasdelmes) || (dia <= 0)){ 
		// Se coteja el entero con la función diasMes y si es incorrecto , se entra en este bucle
		cout << "Por favor, introduzca un día correcto: ";
		cin >> dia;
	}
	if ((dia <= diasdelmes) && (dia > 0)) { cout << "El día " << dia << " es correcto"<< endl; }
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
	case 2: { if (bisiesto){ diasmes = 29; } /* En el caso de febrero, además cotejamos con la función esBisiesto,
															para concretar si tiene 28 o 29 días */
			else { diasmes = 28; } }
	}
	return diasmes;
}


	bool esBisiesto(int anyo){  /* En esta función introducimos las condiciones necesarias para que un año sea bisiesto
								para que devuelva si el introducido por el usuario lo es o no */
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
		for (i = AnyoInicial; i <= anyoFinal; i++){ if (esBisiesto(i)) { contador++; } }/* Este bucle 'for' permite pasearse desde el año inicial (1900),
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
		for (i = 1; i < mes; i++){  // Este bucle 'for' permite pasearse por los meses desde el primero hasta el que precede al mes introducido
			if (mes != Enero) {
				diasmesesenteros = diasmesesenteros + diasMes(i, anyo); /* Se inicializa diasmesesenteros en 0, para que cuando se repita el bucle, se puedan sumar
																		   los días del nuevo mes a los ya acumuladores de manera recursiva */
				diasesteanyo = diasmesesenteros + dia;}
		}
		if (mes == Enero) { diasesteanyo = dia; }       // En el caso del mes de enero solo hay que tener en cuenta el día introducido 
		return diasesteanyo;
	}



	long int diasAnyosCompletos(int anyo){
		/* Esta función calcula el número de días totales entre los años 1900 (incluido) y el actual (sin incluir)
		llamando a la función contarBisiestos, para así tener en cuenta cuantos no tienen 365 sino 366 días */

		long int diasanyoscompletos;
		int numerodebisiestos, nobisiestos, periododeanyos;
		if (esBisiesto(anyo)) { numerodebisiestos = contarBisiestos(AnyoInicial, anyo) - 1; }

		/* Puesto que en la función contarBisiestos se incluyó el año introducido por el usuario en el rango a evaluar, si el último año es bisiesto
		vamos a descartarlo, pues únicamente nos interesan los bisietos completos y por tanto no el último año.
		En el caso de que el usuario introduzca un día posterior al 29 de febrero, la función diasEsteAnyo llamando a diasMes que a su vez depende
		de esBisiesto, ya tiene en cuenta este día adicional y se sumará por tanto en el total de diasTranscurridos */

		else { numerodebisiestos = contarBisiestos(AnyoInicial, anyo); }
		periododeanyos = anyo - AnyoInicial;
		nobisiestos = periododeanyos - numerodebisiestos;

		diasanyoscompletos = (numerodebisiestos * DiasAnyoBisiesto) + (nobisiestos * DiasAnyoNoBisiesto);
		return diasanyoscompletos;
	}

	long int diasTranscurridos(int dia, int mes, int anyo){
		
		/* Esta función simplemente tiene la finalidad de devolver el total de días transcurridos entre el 1 de enero de 1900
		y el día introducido por el usuario, llamando a las funciones diasAnyosCompletos y diasEsteAnyo y sumando los enteros que devuelven. */
		
		long int diastranscurridos, diasesteanyo, diasanyoscompletos;
		diasesteanyo = diasEsteAnyo(dia, mes, anyo);
		diasanyoscompletos = diasAnyosCompletos(anyo);

		diastranscurridos = diasesteanyo + diasanyoscompletos - 1;
		
		/* Puesto que se tiene en cuenta en el total de días transcurridos tanto el día final como el inicial, restamos uno para calcular la representación
		del día de la semana. De esta forma entre el lunes (1/01/1900) y otro lunes habrán transcurrido un numero de días múltiplo de 7 y un resto 0 al dividir
		por 7 este numero de días, será la señal inequevica de que el día introducido es un lunes. */

		return diastranscurridos;
	}

	int diaSemana(long int numDias){
		int diasemana;
		diasemana = (numDias) % NumDiasSemana;
		/* Puesto que tiene en cuenta en el numero de días transcurridos,
		tanto el día final como el inicial, restamos uno para calcular la representación 
		del día de la semana*/
		return diasemana;
	}

	string nombreDia(int representacionDia){
		/* De manera obvia, se deduce que si un valor 0 de vuelta en la función diaSemana equivalía a un lunes,
		el valor 1 equivale a un martes, el valor 2 a un miércoles y así de manera sucesiva. Asociamos estas representaciones enteras a la cadena correspondiente
		mediante un switch que considere los posibles casos (restos del 0 al 6). */
		string nombredia;
		switch (representacionDia)
		{
		case 0: {nombredia = "lunes"; }
				break;
		case 1: {nombredia = "martes"; }
				break;
		case 2: {nombredia = "miércoles"; }
				break;
		case 3: {nombredia = "jueves"; }
				break;
		case 4: {nombredia = "viernes"; }
				break;
		case 5: {nombredia = "sábado"; }
				break;
		case 6: {nombredia = "domingo"; }
		}
		return nombredia;
	}
	int menu() {
		/* Se muestran en la pantalla las distintas opciones y mediante 2 bucles while se asegura que el usuario introduzca 
		un entero y que este entero se encuentre entre 0 y 4, respectivamente */
		int op;
		cout << " " << endl;
		cout << "1.- Calcular el día de la semana para una fecha dada." << endl;
		cout << "2.- Obtener la fecha correspondiente al primer domingo de un año." << endl;
		cout << "3.- Obtener los domingos de un año." << endl;
		cout << "4.- Obtener los posibles puentes de un año." << endl;
		cout << "0.- Salir." << endl;
		cout << "Introduzca la opción deseada: ";
		cin >> op;
		cout << endl;
		while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
		{
			cin.clear();
			cin.sync();
			cout << "Dame un entero: ";
			cin >> op;
		}
		cin.sync();
		while (op < 0 || op > 4) {
			cout << "La opción introducida no es válida, por favor introduzca una correcta: ";
			cin >> op;

			while (cin.fail())  // En el caso de que el usuario no introduzca un entero, se entra en este bucle
			{
				cin.clear();
				cin.sync();
				cout << "Dame un entero: ";
				cin >> op;
			}
			cin.sync();
		}
		return op;
	}
	string diaDeLaSemana(int dia, int mes, int anyo) {

		/* Esta función devuelve exactamente lo mismo que la función diaSemana(), de manera que a la variable 'diadelasemana'
		que devuelve esta función le asignamos lo que devuelve dicha función anterior. Además incluimos un cout que muestra 
		la fecha introducida por el usuario (asignando al nº de mes su nombre correspondiente) y su correspondiente 
		día de la semana. */

		int a = anyo;
		int m = mes;
		int d = dia;
		long  int numdias = diasTranscurridos(d, m, a);
		int diasemana = diaSemana(numdias);
		
		string nombremes = NombreMes(m);
		string nombredia = nombreDia(diasemana);
		string diadelasemana = nombredia;
		cout << "El " << dia << " de " << nombremes << " de " << anyo << " es " << diadelasemana << endl;
		return diadelasemana;

	}
	string NombreMes(int mes) {
		string nombremes;
		switch (mes){
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
		case 6: {nombremes = "junio"; }		 // Asociamos a cada número de mes el string correspondiente a su nombre
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
	int primerDomingoMes(int mes, int anyo) {

		// Devuelve el día delmes que corresponde al primer domingo del mes/anyo dados.

		long int dias1900hasta1mes;
		int diasemana1mes, primerdomingo;
		dias1900hasta1mes = diasTranscurridos(Enero, mes, anyo);
		diasemana1mes = diaSemana(dias1900hasta1mes);
		primerdomingo = NumDiasSemana - diasemana1mes;
		return primerdomingo;
	}
	int domingosAnyo(int anyo) {

		/* Mediante un bucle for se van calculando y mostrando por pantalla todos los domingos 
		de un año introducido por el usuario y contando el número total de ellos para mostrarlos también por pantalla.*/

		int mes1 = Enero;
		int contador = 0;
		cout << "Domingos de " << anyo << endl;
		for (mes1; mes1 <= Diciembre; mes1++){
			int primerdomingomes = primerDomingoMes(mes1, anyo);
			int diasmes0 = diasMes(mes1, anyo);
			string nombremes0 = NombreMes(mes1);
			for (primerdomingomes; primerdomingomes <= diasmes0; primerdomingomes = primerdomingomes + NumDiasSemana){
				cout << primerdomingomes << " de " << nombremes0 << endl;
				contador++;
			}
		}
			cout << "Número total de domingos: " << contador << endl;
			return contador;
	}
	bool puentes() {
		bool espuente;
		int dia, mes, anyo, representacion;
		long int diastranscurridos;
		string nombredia;
		ifstream archivo;      // Declaramos 2 archivos de texto, uno de entrada y otro de salida
		ofstream archivo2;
		archivo.open("fiestas.txt");     // Abrimos el archivo de entrada
		if (archivo.is_open()){
			archivo2.open("puentes.txt");   // Si se ha podido abrir el archivo de entrada, abrimos el de salida
			archivo >> anyo;                // Leemos la primera linea del archivo de entrada, correspondiente al año
			archivo2 << anyo << endl;    // Escribimos ese año en el archivo de salida
			archivo >> dia >> mes;		 // Leemos de la segunda linea 2 enteros correspondientes a un día y el mes
			while (dia != 0){          // Si el día es distinto de 0 (centinela), procesamos los datos

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

				/* Para el día y el mes que se han leído del archivo de entrada, se comprueba si caen en martes (1) o jueves (3)
				y en caso afirmativo, puesto que genera un puente, se asigna a un booleano que indica si la fecha leída es 
				puente el valor true y la copia en el archivo de salida	*/
			}
			archivo2 << "0 0 XXX" << endl; 

			/* Cuando lee el centinela en el archivo de entrada, escribe otro centinela en el de salida */

			archivo.close();					 // Por último cerramos los dos archivos
			archivo2.close();
			cout << "Se ha creado un archivo con el nombre puentes.txt" << endl;
		}
		else {
			cout << "Error: no se ha podido abrir el archivo" << endl;   
			// En caso de que no se haya podido abrir el archivo mostramos un error y asignamos un valor arbitrario al booleano
			espuente = false;
		}

		return espuente;
	}
	
		


	

