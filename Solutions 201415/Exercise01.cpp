// memtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "stdlib.h"	//malloc


/**
Rekursive Funktion mit Tiefen-Parameter
@param d Noch zu absolvierende Aufrufe. Keine weiteren Selbstaufrufe bei d<=1
*/
void f(int d)
{
	d--;
	int dummy;	//lokale Variable
	printf("tiefe %i: %p, %p\n", d, &d, &dummy);	//Ausgabe der Adressen vom Parameter d und der lokalen dummy-Variable
	if (d > 0)	//Abbruchbedingung
		f(d);	//Selbstaufruf
}

int global;	//globale Variable

int main(int argc, const char* argv[])
{
	printf("funktionen: %p, %p \n", &main, &f);	//Ausgabe der Adressen von Funktionen main und f
	printf("global: %p \n", &global);	//Ausgabe der Adresse der globalen (statischen) Variable

	for (int e = 0; e < 8; e++)	//Exponent-iteration
	{
		int size = 1 << e;		//tatsächliche Größe = 2^e
		unsigned char*last = NULL;	//letzte bekannte Adresse
		for (int i = 0; i < 5; i++)	//Instanz-Iteration
		{
			unsigned char * mem = (unsigned char*)malloc(size);	//Speicher-Allokation
			printf("mem(%i): %p (delta %i)\n", size, mem, last ? (mem - last) : 0);	//Ausgabe


			last = mem;	//Letzten Speicherbereich merken
		}
	
	
	}
	f(10);//Aufruf der Rekursiven Funktion f

	return 0;
}

