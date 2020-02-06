#ifndef MENI_H_
#define MENI_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Strukture.h"
#include "Prikazivanje.h"
#include "Greske.h"
#include "Pretrazivanje.h"
#include "TrenutnoStanje.h"

void glavniMeni3() {
	system("cls");
	int odabir;
	while (1 == 1) {

		printf("********************************\n");
		printf("*         Glavni meni          *\n");
		printf("* 1. Prikazi proizvode         *\n");
		printf("* 2. Pretrazi proizvode        *\n");
		printf("* 3. Pretrazi nove proizvode   *\n");
		printf("* 4. Pretrazi nove proizvode   *\n");
		printf("* 5. Prikazi promene stanja    *\n");
		printf("* 6. Pretrazi promene stanja   *\n");
		printf("* 7. Kreiraj trenutno stanje   *\n");
		printf("* 8. Prikazi trenutno stanje   *\n");
		printf("* 9. Prikazi greske            *\n");
		printf("* 10. Izlazak iz aplikacije    *\n");
		printf("********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
		case 1: prikaziDatotekuProizvoda("..\\PrviSlucaj\\Proizvod.dat"); break;

		case 2: pretraziDatotekuProizvoda("..\\PrviSlucaj\\Proizvod.dat"); break;

		case 3: prikaziDatotekuProizvoda("..\\PrviSlucaj\\NoviProizvod.dat"); break;

		case 4: pretraziDatotekuProizvoda("..\\PrviSlucaj\\NoviProizvod.dat"); break;

		case 5: prikaziDatotekuPromena(); break;

		case 6: pretraziDatotekuPromena(); break;

		case 7: kreirajTrenutnoStanje(3); break;

		case 8: prikaziTrenutnoStanje(); break;

		case 9: prikaziGreske(); break;

		case 10: {
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

void glavniMeni2() {
	system("cls");
	int odabir;
	while (1 == 1) {

		printf("********************************\n");
		printf("*         Glavni meni          *\n");
		printf("* 1. Prikazi proizvode         *\n");
		printf("* 2. Pretrazi proizvode        *\n");
		printf("* 3. Prikazi nove proizvode    *\n");
		printf("* 4. Pretrazi nove proizvode   *\n");
		printf("* 5. Prikazi promene stanja    *\n");
		printf("* 6. Pretrazi promene stanja   *\n");
		printf("* 7. Kreiraj trenutno stanje   *\n");
		printf("* 8. Prikazi trenutno stanje   *\n");
		printf("* 9. Izlazak iz aplikacije     *\n");
		printf("********************************\n");
		printf("Vas odabir? ");

		scanf("%d", &odabir);

		switch (odabir) {
		case 1: prikaziDatotekuProizvoda("..\\PrviSlucaj\\Proizvod.dat"); break;

		case 2: pretraziDatotekuProizvoda("..\\PrviSlucaj\\Proizvod.dat"); break;

		case 3: prikaziDatotekuProizvoda("..\\PrviSlucaj\\NoviProizvod.dat"); break;

		case 4: pretraziDatotekuProizvoda("..\\PrviSlucaj\\NoviProizvod.dat"); break;

		case 5: prikaziDatotekuPromena(); break;

		case 6: pretraziDatotekuPromena(); break;

		case 7: kreirajTrenutnoStanje(2); break;

		case 8: prikaziTrenutnoStanje(); break;

		case 9: {
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

void glavniMeni1() {
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
		case 1: prikaziDatotekuProizvoda("..\\PrviSlucaj\\Proizvod.dat"); break;

		case 2: pretraziDatotekuProizvoda("..\\PrviSlucaj\\Proizvod.dat"); break;

		case 3: prikaziDatotekuPromena(); break;

		case 4: pretraziDatotekuPromena(); break;

		case 5: kreirajTrenutnoStanje(1); break;

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