#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int solicitaAnyo();
int solicitaMes();
int solicitaDia(int mes, int anyo);
int diasMes(int mes, int anyo);
bool esBisiesto(int anyo);
long int diasTranscurridos(int dia, int mes, int anyo);
int diaSemana(long int numDias);
string nombreDia(int representacionDia);
long int diasAnyosCompletos(int anyo);
int contarBisiestos(int anyoInicio, int anyoFinal);
int diasEsteAnyo(int dia, int mes, int anyo);


int main(){
	int mes1, anyo1, dia1, diaSemana1, contarbisiestos1, diasesteanyo1;
	long int diasTranscurridos1;
	string nombredia1;
	anyo1 = solicitaAnyo();
	mes1 = solicitaMes();
	dia1 = solicitaDia(mes1, anyo1);
	diasTranscurridos1 = diasTranscurridos(dia1, mes1, anyo1);
	diaSemana1 = diaSemana (diasTranscurridos1);
	nombredia1 = nombreDia(diaSemana1);
	contarbisiestos1 = contarBisiestos(1900, anyo1);
	diasesteanyo1 = diasEsteAnyo(dia1, mes1, anyo1);

	

	system("pause");

	return 0;
}
int solicitaAnyo(){
	int anyo;
	cout << "Introduzca un anyo igual o posterior a 1900: ";
	cin >> anyo;
	while (anyo < 1900){
		cout << "Por favor, introduzca un anyo correcto, que sea mayor o igual que 1900: ";
		cin >> anyo;
	}
	if (anyo >= 1900) {
		cout << "El anyo " << anyo << " que ha introducido es correcto. " << endl;
	}
	return anyo;
}
int solicitaMes(){
	int mes;
	cout << "Introduzca el numero correspondiente al mes del anyo: ";
	cin >> mes;
	while (mes < 1 || mes > 12){
		cout << "Por favor, introduzca un mes correcto, entre 1 y 12: ";
		cin >> mes;
	}
	if (mes >= 1 && mes <= 12) {
		cout << "El mes " << mes << " que ha introducido es correcto. " << endl;
	}
	return mes;
}
int solicitaDia(int mes, int anyo){
	int dia, diasmes1;
	diasmes1 = diasMes(mes, anyo);
	cout << "Por favor, introduzca un dia del mes: ";
	cin >> dia;
	while (dia > diasmes1 || dia <= 0) {
		cout << "El dia introducido no es correcto para el mes y el anyo seleccionados, introduzca otro: ";
		cin >> dia;
	}
		cout << "El dia " << dia << " que ha introducido es correcto" << endl;
		return dia;
}
long int diasTranscurridos(int dia, int mes, int anyo) {
	long int numDias, diasesteanyo, diasanyoscompletos;
	diasesteanyo = diasEsteAnyo(dia, mes, anyo);
	diasanyoscompletos = diasAnyosCompletos(anyo);
	numDias = diasesteanyo + diasanyoscompletos;
	cout << "Desde el 1 / 1 / 1900 hasta el " << dia << " / " << mes << " / " << anyo << " han transcurrido " << numDias << " dias." << endl;
	return numDias;
}

int diasMes(int mes, int anyo){
	int diasmes;
	bool bisiesto1;
	bisiesto1 = esBisiesto(anyo);
	switch (mes) {
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
	case 2: {if (bisiesto1 == 1) { diasmes = 29; }
			else { diasmes = 28; } }
	}
	return diasmes;
}

			
bool esBisiesto(int anyo) {
	bool esbisiesto;
	if (((anyo % 4 == 0) && (anyo % 100 != 0)) || (anyo % 400 == 0)) {
		esbisiesto = true;
	}
	else {
		esbisiesto = false;
	}
	return esbisiesto;
}
int diaSemana(long int numDias) {
	int representacionDia;
	representacionDia = ((numDias - 1) % 7);
	cout << representacionDia << endl;
	return representacionDia;
}
string nombreDia(int representacionDia) {
	string nombredia;
	switch (representacionDia) {
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
			break;
	}
	cout  << nombredia << endl;
	return nombredia;
}
long int diasAnyosCompletos(int anyo) {
	long int diasanyoscompletos;
	int bisiestosintermedios, periodoanyos, nobisiestos;
	bisiestosintermedios = contarBisiestos(1900, anyo);
	periodoanyos = anyo - 1900;
	nobisiestos = periodoanyos - bisiestosintermedios;
	diasanyoscompletos = (366 * bisiestosintermedios) + (365 * nobisiestos);
	return diasanyoscompletos;
}
int diasEsteAnyo(int dia, int mes, int anyo){
	int diasesteanyo, i, diasmesesenteros;
	diasmesesenteros = 0;
	for (i = 1; i < mes; i++) {
		if (mes != 1) {
			diasmesesenteros = diasmesesenteros + diasMes(i, anyo);
			diasesteanyo = diasmesesenteros + dia;
		}
	}
		if (mes == 1) {
			diasesteanyo = dia;
		}
	cout << "Dias en este anyo: " << diasesteanyo << endl;
	return diasesteanyo;
}

int contarBisiestos(int anyoInicio, int anyoFinal) {
	int i, numbisiestos;
	numbisiestos = 0;
	for (i = 1900; i < anyoFinal; i++) { if (esBisiesto(i)) {numbisiestos++;} }
	cout << "Numero de anyos bisiestos " << numbisiestos << endl;
	return numbisiestos;
}



