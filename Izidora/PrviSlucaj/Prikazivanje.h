#ifndef PRIKAZIVANJE_H_
#define PRIKAZIVANJE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Strukture.h"

void prikaziDatotekuPromena() {

	int i = 0;
	promena P;

	datotekaPromena = fopen("..\\PrviSlucaj\\Promena.dat", "rb");

	if (datotekaPromena == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	printf("Prikaz promena:\n");

	while (fread(&P, sizeof(promena), 1, datotekaPromena) != 0) {
		printf("%2d|%2c|%3d|\n", P.sifra, P.tip, P.kolicina); i++;
	}

	if (i == 0) printf("Datoteka je prazna\n");

	fclose(datotekaPromena);
}

void prikaziDatotekuProizvoda(const char* ime) {

	int i = 0;
	proizvod P;



	datotekaProizvoda = fopen(ime, "rb");

	if (datotekaProizvoda == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	printf("Prikaz proizvoda:\n");

	while (fread(&P, sizeof(proizvod), 1, datotekaProizvoda) != 0) {
		printf("%2d|%20s|%5.2lf|%30s|\n", P.sifra, P.naziv, P.cena, P.opis); i++;
	}

	if (i == 0) printf("Datoteka je prazna\n");

	fclose(datotekaProizvoda);
}

#endif
