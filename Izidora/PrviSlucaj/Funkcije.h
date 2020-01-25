#ifndef FUNKCIJE_H_
#define FUNKCIJE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//Datoteke
FILE* datotekaProizvoda = NULL;
FILE* datotekaPromena = NULL;
FILE* trenutnoStanje = NULL;

//Strukture
typedef struct proizvod {
	int sifra;
	char naziv[20];
	double cena;
	int stanje;
} proizvod;

typedef struct promena {
	int sifra;
	char tip; /*U za povecanje stanja (Ulaz), I za smanjenje stanja (Izlaz)*/
	int kolicina;
} promena;

//Pocetna funkcija
void poveziPokazivace() {
	datotekaProizvoda = fopen("Proizvod.dat","rb");
	datotekaPromena = fopen("Promena.dat", "rb");
	fclose(datotekaProizvoda);
	fclose(datotekaPromena);
}

//Funkcije za Promena.dat
void pretraziDatotekuPromena() {

	int i = 0;
	promena P;
	int unetaSifra;

	if (datotekaPromena == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	datotekaProizvoda = fopen("Promena.dat", "rb");

	printf("Unesite sifru po kojoj pretrazujete: ");
	scanf("%d", &unetaSifra);

	printf("\nPromene sa datom sifrom:\n");

	while (fread(&P, sizeof(promena), 1, datotekaPromena) != 0) {
		if (P.sifra == unetaSifra)
		{
			printf("%2d|%2c|%3d\n", P.sifra, P.tip, P.kolicina); i++;
		}
	}

	if (i == 0) printf("Ne postoje promene sa datom sifrom\n");

	fclose(datotekaPromena);
}

void prikaziDatotekuPromena() {

	int i = 0;
	promena P;

	if (datotekaPromena == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	datotekaPromena = fopen("Promena.dat", "rb");

	printf("Prikaz promena:\n");

	while (fread(&P, sizeof(promena), 1, datotekaPromena) != 0) {
		printf("%2d|%2c|%3d\n", P.sifra, P.tip, P.kolicina); i++;
	}

	if (i == 0) printf("Datoteka je prazna\n");

	fclose(datotekaPromena);
}

//Funkcije za Proizvod.dat
void prikaziDatotekuProizvoda() {

	int i = 0;
	proizvod P;

	if (datotekaProizvoda == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	printf("Prikaz proizvoda:\n");

	datotekaProizvoda = fopen("Proizvod.dat", "rb");

	while (fread(&P, sizeof(proizvod), 1, datotekaProizvoda) != 0) {
		printf("%2d|%20s|%5.2lf|%4d\n", P.sifra, P.naziv, P.cena, P.stanje); i++;
	}

	if (i == 0) printf("Datoteka je prazna\n");

	fclose(datotekaProizvoda);
}

void pretraziDatotekuProizvoda() {

	int i = 0;
	proizvod P;
	int unetaSifra;

	if (datotekaProizvoda == NULL) {
		printf("Datoteka nije kreirana\n");
		return;
	}

	printf("Unesite sifru po kojoj pretrazujete: ");
	scanf("%d", &unetaSifra);

	printf("\nProizvodi sa zadatom sifrom:\n");

	datotekaProizvoda = fopen("Proizvod.dat", "rb");

	while (fread(&P, sizeof(proizvod), 1, datotekaProizvoda) != 0) {
		if (P.sifra == unetaSifra)
		{
			printf("%2d|%20s|%5.2lf|%4d\n", P.sifra, P.naziv, P.cena, P.stanje);
			i++;
		}
	}

	if (i == 0) printf("Ne postoji proizvod sa zadatom sifrom\n");

	fclose(datotekaProizvoda);
}

//Funkcije za TrenutnoStanje.txt
void kreirajTrenutnoStanje() {

	//Azuriranje promena
	int i = 0;
	promena P;

	FILE* azuriranePromene = fopen("AzuriranePromene.dat", "w+b");
	datotekaPromena = fopen("Promena.dat", "rb");

	int brojac = 1;
	int nizGotovih[100]; int brN = 0;
	int read;

	while (1 == 1) {

		fseek(datotekaPromena, 0, SEEK_SET);

		for (int i = 1; i <= brojac; i++)
			read = fread(&P, sizeof(promena), 1, datotekaPromena);

		if (read == 0) {
			fclose(datotekaPromena);
			fclose(azuriranePromene);
			break;
		}

		brojac++;
		int signal = 1;
		for (int i = 0; i < brN; i++) {
			if (P.sifra == nizGotovih[i]) signal = 0;
		}

		if (signal == 0) continue;

		nizGotovih[brN++] = P.sifra;
		promena glavna;
		glavna.sifra = P.sifra;
		glavna.kolicina = P.kolicina;
		glavna.tip = P.tip;

		if (glavna.tip == 'U' || glavna.tip == 'u') glavna.kolicina = P.kolicina;
		else glavna.kolicina = -P.kolicina;


		while (fread(&P, sizeof(promena), 1, datotekaPromena) != 0) {
			if (glavna.sifra == P.sifra) {
				if (P.tip == 'U' || P.tip == 'u') glavna.kolicina += P.kolicina;
				else glavna.kolicina -= P.kolicina;
			}
		}

		if (glavna.kolicina > 0)
			glavna.tip = 'u';
		else {
			glavna.tip = 'i';
			glavna.kolicina = -glavna.kolicina;
		}

		fwrite(&glavna, sizeof(promena), 1, azuriranePromene);
	}

	//Azuriranje proizvoda
	i = 0;
	proizvod pr;

	FILE* azuriraniProizvodi = fopen("AzuriraniProizvodi.dat", "w+b");
	datotekaProizvoda = fopen("Proizvod.dat", "r+b");
	azuriranePromene = fopen("AzuriranePromene.dat", "r+b");

	while (fread(&P, sizeof(promena), 1, azuriranePromene)) {

		int uspesno = 0;

		while (fread(&pr, sizeof(proizvod), 1, datotekaProizvoda)) {

			if (pr.sifra == P.sifra) {
				proizvod glavni;
				glavni.sifra = pr.sifra;
				glavni.stanje = pr.stanje;
				glavni.cena = pr.cena;
				strcpy(glavni.naziv, pr.naziv);

				if (P.tip == 'u' || P.tip == 'U') {
					glavni.stanje += P.kolicina;
				}
				else {
				glavni.stanje -= P.kolicina;
				}

				if (glavni.stanje >= 0) {
					fwrite(&glavni, sizeof(proizvod), 1, azuriraniProizvodi);
					uspesno = 1;
				}
				else {
					fwrite(&pr, sizeof(proizvod), 1, azuriraniProizvodi);
				}
			}
		}

		fseek(datotekaProizvoda, 0, SEEK_SET);
	}

	fclose(azuriranePromene);
	fclose(datotekaProizvoda);
	fclose(azuriraniProizvodi);
	
	//Pravljenje trenutnog stanja
	trenutnoStanje = fopen("TrenutnoStanje.txt", "w+");
	azuriraniProizvodi = fopen("AzuriraniProizvodi.dat", "rb");

	brojac = 0;

	while (fread(&pr, sizeof(proizvod), 1, azuriraniProizvodi)) {
		fprintf(trenutnoStanje, "%2d|%20s|%5.2lf|%4d\n", pr.sifra, pr.naziv, pr.cena, pr.stanje); brojac++;
	}

	fclose(trenutnoStanje);
	fclose(azuriraniProizvodi);

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