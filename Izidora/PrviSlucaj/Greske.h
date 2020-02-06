#ifndef GRESKE_H_
#define GRESKE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Strukture.h"

void prikaziGreske() {

	FILE* greske = fopen("..\\PrviSlucaj\\Greske.txt", "r");
	char c;



	printf("Prikaz datoteke gresaka: \n");

	if (greske == NULL) {
		printf("Datoteka je prazna\n");
		return;
	}

	int signal = 0;
	while ((c = fgetc(greske)) != EOF) {
		printf("%c", c); signal = 1;
	}

	if (signal == 0) printf("Datoteka je prazna\n");

}

void resetujGreske() {
	FILE* greske = fopen("..\\PrviSlucaj\\Greske.txt", "w");
	fclose(greske);
}

#endif
