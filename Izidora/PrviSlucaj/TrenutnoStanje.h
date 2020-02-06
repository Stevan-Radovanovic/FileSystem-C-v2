#ifndef TRENUTNOSTANJE_H_
#define TRENUTNOSTANJE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Strukture.h"
#include "Greske.h"

int postojiUNizuStanja(stanje nizStanja[], int brojac, promena prom) {

	for (int i = 0; i < brojac; i++) {
		if (prom.sifra == nizStanja[i].sifra) return i;
	}

	return -1; //signal da ne postoji u nizu stanja proizvod sa datom sifrom
}

void promeniStanje(stanje niz[], int indeks, promena prom) {
	if (prom.tip == 'U' || prom.tip == 'u')
		niz[indeks].stanje = niz[indeks].stanje + prom.kolicina;
	else
		niz[indeks].stanje = niz[indeks].stanje - prom.kolicina;
}

void upisiGresku(promena prom) {
	FILE* greske = fopen("..\\PrviSlucaj\\Greske.txt", "a");
	fprintf(greske, "Doslo je do greske pri sledecem unosu: %d %c %d\n", prom.sifra, prom.tip, prom.kolicina);
	fclose(greske);
}

int pronadjiProizvod(const char* ime, promena prom, stanje nizStanja[], int *brojac) {

	FILE* datotekaProizvoda = fopen(ime, "r+b");
	proizvod pr;

	while (fread(&pr, sizeof(proizvod), 1, datotekaProizvoda)) {

		if (prom.sifra == pr.sifra) {
			stanje s;
			s.sifra = pr.sifra;
			strcpy(s.naziv, pr.naziv);
			if (prom.tip == 'U' || prom.tip == 'u') s.stanje = prom.kolicina;
			else s.stanje = -prom.kolicina;
			nizStanja[(*brojac)++] = s;
			fclose(datotekaProizvoda);
			return 1;
		}

	}

	fclose(datotekaProizvoda);
	return 0;

}

void dodajUNizStanja(stanje nizStanja[], int *brojac, promena prom, int slucaj) {

	

	int rez = pronadjiProizvod("..\\PrviSlucaj\\Proizvod.dat", prom, nizStanja, brojac);
	
	if (rez == 1) return;

	if (slucaj == 1) return;

	rez = pronadjiProizvod("..\\PrviSlucaj\\NoviProizvod.dat", prom, nizStanja, brojac);

	if (rez == 1) return;
	
	if (slucaj == 2) return;

	upisiGresku(prom);




}

void napuniDatotekuStanjima(stanje nizStanja[], int brojac) {
	trenutnoStanje = fopen("..\\PrviSlucaj\\TrenutnoStanje.txt", "w");
	char str1[] = "Sifra";
	char str2[] = "Naziv";
	char str3[] = "Kolicina";
	fprintf(trenutnoStanje, "%6s|%12s|%10s|\n", str1, str2, str3);
	for (int i = 0; i < brojac; i++) {
		if (nizStanja[i].stanje < 0) nizStanja[i].stanje = 0;
		fprintf(trenutnoStanje, "%6d|%12s|%10d|\n", nizStanja[i].sifra, nizStanja[i].naziv, nizStanja[i].stanje);
	}
	fclose(trenutnoStanje);
}

void kreirajTrenutnoStanje(int slucaj) {

	stanje nizStanja[100];
	int brojac = 0;

	resetujGreske(); //za brisanje gresaka

	FILE* datotekaPromena = fopen("..\\PrviSlucaj\\Promena.dat", "r+b");
	promena prom;

	while (fread(&prom, sizeof(promena), 1, datotekaPromena)) {
		int indeks;
		if ((indeks = postojiUNizuStanja(nizStanja, brojac, prom)) != -1) {
			promeniStanje(nizStanja, indeks, prom);
		}
		else {
			dodajUNizStanja(nizStanja, &brojac, prom, slucaj);
		}
	}

	napuniDatotekuStanjima(nizStanja,brojac);
	
	printf("Datoteka trenutnog stanja je kreirana\n");

}

void prikaziTrenutnoStanje() {

	trenutnoStanje = fopen("..\\PrviSlucaj\\TrenutnoStanje.txt", "r");
	char c;

	printf("Prikaz datoteke trenutnog stanja: \n");
	int signal = 0;
	while ((c = fgetc(trenutnoStanje)) != EOF) {
		printf("%c", c); signal = 1;
	}

	if (signal == 0) printf("Datoteka je prazna\n");

}

#endif
