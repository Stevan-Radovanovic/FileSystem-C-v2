#ifndef STRUKTURE_H_
#define STRUKTURE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//Datoteke
FILE* datotekaProizvoda = NULL;
FILE* datotekaPromena = NULL;
FILE* trenutnoStanje = NULL;

//Strukture
typedef struct proizvod {
	int sifra;
	char naziv[20];
	double cena;
	char opis[40];
} proizvod;

typedef struct promena {
	int sifra;
	char tip; /*U za povecanje stanja (Ulaz), I za smanjenje stanja (Izlaz)*/
	int kolicina;
} promena;

typedef struct trenutnoStanje {
	int sifra;
	char naziv[20];
	int stanje;
} stanje;

#endif