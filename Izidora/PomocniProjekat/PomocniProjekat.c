#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "..\PrviSlucaj\Funkcije.h"

FILE* proizvodDat;
FILE* promeneDat;

void meni();
void ubaciProizvodUDatotekuProizvod();
void ubaciProizvodUDatotekuNoviProizvod();
void ubaciPromenu();

int main(void) {

	meni();
}

void meni() {

	system("cls");
	int odabir;
	while (1 == 1) {

		printf("****************************************\n");
		printf("*              Glavni meni             *\n");
		printf("* 1. Ubaci proizvod u Proizvod.dat     *\n");
		printf("* 2. Ubaci proizvod u NoviProizvod.dat *\n");
		printf("* 3. Ubaci promenu stanja              *\n");
		printf("* 4. Izlazak iz aplikacije             *\n");
		printf("****************************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
		case 1: ubaciProizvodUDatotekuProizvod(); break;

		case 2: ubaciProizvodUDatotekuNoviProizvod(); break;

		case 3: ubaciPromenu(); break;

		case 4: {
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

void ubaciProizvodUDatotekuProizvod() {
	proizvod p;
	datotekaProizvoda = fopen("..\\PrviSlucaj\\Proizvod.dat", "a+b");

	printf("Dodavanje novog proizvoda: \n");
	printf("Unesite sifru: ");
	scanf("%d", &p.sifra);
	getchar();
	printf("Unesite naziv: ");
	gets(p.naziv);
	printf("Unesite cenu: ");
	scanf(" %lf", &p.cena);
	getchar();
	printf("Unesite opis: ");
	gets(p.opis);

	printf("\nProizvod je uspesno unet u datoteku!\n");

	fwrite(&p, sizeof(proizvod), 1, datotekaProizvoda);
	fclose(datotekaProizvoda);
}

void ubaciProizvodUDatotekuNoviProizvod() {
	proizvod p;
	datotekaProizvoda = fopen("..\\PrviSlucaj\\NoviProizvod.dat", "a+b");

	printf("Dodavanje novog proizvoda: \n");
	printf("Unesite sifru: ");
	scanf("%d", &p.sifra);
	getchar();
	printf("Unesite naziv: ");
	gets(p.naziv);
	printf("Unesite cenu: ");
	scanf(" %lf", &p.cena);
	getchar();
	printf("Unesite opis: ");
	gets(p.opis);

	printf("\nProizvod je uspesno unet u datoteku!\n");

	fwrite(&p, sizeof(proizvod), 1, datotekaProizvoda);
	fclose(datotekaProizvoda);
}

void ubaciPromenu() {
	promena p;
	datotekaPromena = fopen("..\\PrviSlucaj\\Promena.dat", "a+b");

	printf("Dodavanje nove promene stanja: \n");
	printf("Unesite sifru: ");
	scanf("%d", &p.sifra);
	getchar();
	printf("Ukoliko dodajete kolicinu na stanje, ukucajte U. U suprotnom, ukucajte I: ");
	scanf(" %c", &p.tip);
	getchar();
	printf("Unesite kolicinu: ");
	scanf(" %d", &p.kolicina);
	getchar();

	printf("\Promena je uspesno uneta u datoteku!\n");

	fwrite(&p, sizeof(promena), 1, datotekaPromena);
	fclose(datotekaPromena);
}
