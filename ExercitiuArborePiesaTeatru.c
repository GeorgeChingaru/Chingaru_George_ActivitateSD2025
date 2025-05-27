#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
/*
* Definiți structura PiesaTeatru, care conține următoarele câmpuri:
 titlu (char*), durată în minute (int), anul premierei (int), popularitate (float – scor între 0 și 10).

Implementați o funcție de inserare într-un arbore binar de căutare, sortând piesele alfabetic după titlu.

Implementați o funcție de parcurgere în inordine și afișare a pieselor (titlu, durată, an, popularitate).

Implementați o funcție care returnează piesa cu cea mai mare popularitate, folosind deep copy.

Implementați o funcție care caută o piesă după titlu și o returnează (deep copy).

Eliberați toată memoria alocată dinamic în arbore.

*/
struct PiesaTeatru {
	char* titlu;
	int durata;
	int anulPremierei;
	float popularitate;
};
typedef struct PiesaTeatru Piesa;
typedef struct Nod Nod;
struct Nod {
	Piesa info;
	Nod* st;
	Nod* dr;
};
Piesa citirePiesaDinFisier(FILE* f)
{
	Piesa p;
	char* token, buffer[256], sep[] = ",\n";
	fgets(buffer, 256, f);

	token=strtok(buffer, sep);
	p.titlu = (char*)malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(p.titlu, strlen(token) + 1, token);

	token = strtok(NULL, sep);
	p.durata = atoi(token);

	token = strtok(NULL, sep);
	p.anulPremierei = atoi(token);

	token = strtok(NULL, sep);
	p.popularitate = atof(token);
	
	return p;
}
void afisarePiesa(Piesa p)
{
	printf("Titlul piesei este: %s\n", p.titlu);
	printf("Durata piesei este de %d minute\n", p.durata);
	printf("Anul premierei a fost in %d\n", p.anulPremierei);
	printf("Popularitatea este de %.2f\n\n", p.popularitate);
}
void adaugaPiesaInArbore(Nod** arbore, Piesa piesaNoua)
{
	if (!(*arbore))
	{
		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
		nodNou->info = piesaNoua;
		nodNou->st = NULL;
		nodNou->dr = NULL;
		(*arbore) = nodNou;
	}
	else
	{
		if (strcmp((*arbore)->info.titlu, piesaNoua.titlu) > 0)
		{
			adaugaPiesaInArbore(&(*arbore)->st, piesaNoua);
		}
		else
			if (strcmp((*arbore)->info.titlu, piesaNoua.titlu) < 0)
		{
				adaugaPiesaInArbore(&(*arbore)->dr, piesaNoua);
		}
	}
}
Nod* citireArboreDePiese(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(f))
	{
		Piesa p = citirePiesaDinFisier(f);
		adaugaPiesaInArbore(&radacina, p);
	}
	fclose(f);
	return radacina;
}

void afisareInOrdine(Nod* arbore)
{
	if (arbore)
	{
		afisareInOrdine(arbore->st);
		afisarePiesa(arbore->info);
		afisareInOrdine(arbore->dr);
	}
}
void dezalocare(Nod** arbore)
{
	if ((*arbore))
	{
		dezalocare((*arbore)->st);
		dezalocare((*arbore)->dr);
		free((*arbore)->info.titlu);
		free((*arbore));
		(*arbore) = NULL;
	}
	

}
int main()
{
	Nod* radacina = NULL;
	radacina = citireArboreDePiese("piese.txt");
	afisareInOrdine(radacina);
	
	return 0;
}