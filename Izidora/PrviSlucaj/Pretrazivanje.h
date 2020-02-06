#ifndef PRETRAZIVANJE_H_
#define PRETRAZIVANJE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Strukture.h"

void pretraziDatotekuPromena() {

	int i = 0;
	promena P;
	int unetaSifra;

	datotekaPromena = fopen("..\\PrviSlucaj\\Promena.dat", "rb");

	if (datotekaPromena == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	printf("Unesite sifru po kojoj pretrazujete: ");
	scanf("%d", &unetaSifra);

	printf("\nPromene sa datom sifrom:\n");

	while (fread(&P, sizeof(promena), 1, datotekaPromena) != 0) {
		if (P.sifra == unetaSifra)
		{
			printf("%2d|%2c|%3d|\n", P.sifra, P.tip, P.kolicina); i++;
		}
	}

	if (i == 0) printf("Ne postoje promene sa datom sifrom\n");

	fclose(datotekaPromena);
}

void pretraziDatotekuProizvoda(const char ime[]) {

	int i = 0;
	proizvod P;
	int unetaSifra;

	datotekaProizvoda = fopen(ime, "rb");

	if (datotekaProizvoda == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	printf("Unesite sifru po kojoj pretrazujete: ");
	scanf("%d", &unetaSifra);

	printf("\nProizvodi sa zadatom sifrom:\n");

	while (fread(&P, sizeof(proizvod), 1, datotekaProizvoda) != 0) {
		if (P.sifra == unetaSifra)
		{
			printf("%2d|%20s|%5.2lf|%30s|\n", P.sifra, P.naziv, P.cena, P.opis);
			i++;
		}
	}

	if (i == 0) printf("Ne postoji proizvod sa zadatom sifrom\n");

	fclose(datotekaProizvoda);
}

#endif

