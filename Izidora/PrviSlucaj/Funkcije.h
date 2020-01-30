#ifndef FUNKCIJE_H_
#define FUNKCIJE_H_

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

//Funkcije za Promena.dat
void pretraziDatotekuPromena() {

	int i = 0;
	promena P;
	int unetaSifra;

	datotekaPromena = fopen("Promena.dat", "rb");

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

void prikaziDatotekuPromena() {

	int i = 0;
	promena P;

	datotekaPromena = fopen("Promena.dat", "rb");

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

//Funkcije za Proizvod.dat
void prikaziDatotekuProizvoda() {

	int i = 0;
	proizvod P;

	

	datotekaProizvoda = fopen("Proizvod.dat", "rb");

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

void pretraziDatotekuProizvoda() {

	int i = 0;
	proizvod P;
	int unetaSifra;

	datotekaProizvoda = fopen("Proizvod.dat", "rb");

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

//Funkcije za TrenutnoStanje.txt
int postojiUNizuStanja(stanje nizStanja[], int brojac, promena prom) {

	for (int i = 0; i < brojac; i++) {
		if (prom.sifra == nizStanja[i].sifra) return i;
	}

	return -1;
}

void promeniStanje(stanje niz[],int indeks, promena prom) {
	if (prom.tip == 'U' || prom.tip == 'u') 
		niz[indeks].stanje = niz[indeks].stanje + prom.kolicina;
	else
		niz[indeks].stanje = niz[indeks].stanje - prom.kolicina;
}

void dodajUNizStanja(stanje nizStanja[], int *brojac, promena prom) {

	FILE* datotekaProizvoda = fopen("Proizvod.dat", "r+b");
	proizvod pr;
	while (fread(&pr, sizeof(proizvod), 1, datotekaProizvoda)) {

		if (prom.sifra == pr.sifra) {
			stanje s;
			s.sifra = pr.sifra;
			strcpy(s.naziv, pr.naziv);
			if (prom.tip == 'U' || prom.tip == 'u') s.stanje = prom.kolicina;
			else s.stanje = -prom.kolicina;
			nizStanja[(*brojac)++] = s;
			return;
		}

	}
	fclose(datotekaProizvoda);

}

void kreirajTrenutnoStanje() {

	stanje nizStanja[100];
	int brojac = 0;

	FILE* datotekaPromena = fopen("Promena.dat", "r+b");
	promena prom;

	while (fread(&prom, sizeof(promena), 1, datotekaPromena)) {
		int indeks;
		if((indeks=postojiUNizuStanja(nizStanja, brojac, prom)) !=-1) {
				promeniStanje(nizStanja,indeks, prom);
		}
		else {
				dodajUNizStanja(nizStanja, &brojac, prom);
		}
	}

	trenutnoStanje = fopen("TrenutnoStanje.txt", "w");
	char str1[] = "Sifra";
	char str2[] = "Naziv";
	char str3[] = "Kolicina";
	fprintf(trenutnoStanje, "%6s|%12s|%10s|\n", str1, str2, str3);
	for (int i = 0; i < brojac; i++) {
		if (nizStanja[i].stanje < 0) nizStanja[i].stanje = 0;
		fprintf(trenutnoStanje, "%6d|%12s|%10d|\n", nizStanja[i].sifra, nizStanja[i].naziv, nizStanja[i].stanje);
	}
	fclose(trenutnoStanje);

	printf("Datoteka trenutnog stanja je kreirana\n");

}

void prikaziTrenutnoStanje() {

	trenutnoStanje = fopen("TrenutnoStanje.txt", "r");
	char c;

	printf("Prikaz datoteke trenutnog stanja: \n");
	int signal = 0;
	while ((c = fgetc(trenutnoStanje)) != EOF) {
		printf("%c", c); signal = 1;
	}

	if (signal == 0) printf("Datoteka je prazna\n");

}

//Funkcija za prikaz
void glavniMeni() {
	system("cls");
	int odabir;
	while (1 == 1) {

		printf("********************************\n");
		printf("*         Glavni meni          *\n");
		printf("* 1. Prikazi proizvode         *\n");
		printf("* 2. Pretrazi proizvode        *\n");
		printf("* 3. Prikazi promene stanja    *\n");
		printf("* 4. Pretrazi promene stanja   *\n");
		printf("* 5. Kreiraj trenutno stanje   *\n");
		printf("* 6. Prikazi trenutno stanje   *\n");
		printf("* 7. Izlazak iz aplikacije     *\n");
		printf("********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
		case 1: prikaziDatotekuProizvoda(); break;

		case 2: pretraziDatotekuProizvoda(); break;

		case 3: prikaziDatotekuPromena(); break;

		case 4: pretraziDatotekuPromena(); break;

		case 5: kreirajTrenutnoStanje(); break;

		case 6: prikaziTrenutnoStanje(); break;

		case 7: {
			printf("Dovidjenja!\n");
			system("pause");
			return;
		}

		default: {
			printf("Uneli ste nepostojecu vrednost, pokusajte ponovo.\n");
			break;
		}
		}

		system("pause");
		system("cls");
	}
}

#endif