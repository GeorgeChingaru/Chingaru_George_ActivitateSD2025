#include< string.h>
#include< stdio.h>
#include< malloc.h>
#include< stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
/*Se dă o structură Carte, care conține următoarele câmpuri :

char* titlu – titlul cărții

char* autor – numele autorului

int anPublicare – anul publicării

float pret – prețul cărții*/

struct Carte {
	char* titlu;
	char* autor;
	int anPublicare;
	float pret;
};
typedef struct Carte Carte;
typedef struct Nod Nod;
struct Nod {
	Carte info;
	Nod* st; 
	Nod* dr;
};
/*Construiți un arbore binar de căutare(ABC) în care cărțile sunt organizate alfabetic după titlu.

Implementați o funcție de inserare a unei cărți în arbore.

Implementați o funcție care parcurge arborele în inordine și afișează toate cărțile.

Scrieți o funcție care returnează cartea cu prețul cel mai mare(deep copy).

Scrieți o funcție care caută o carte după titlu și returnează datele ei(deep copy).

Eliberați toată memoria alocată dinamic în arbore.*/
Carte citireCarteDinFisier(FILE* f)
{
	Carte c;
	char* token, buffer[256], sep[] = ",\n";
	fgets(buffer, 256, f);

	token = strtok(buffer, sep);
	c.titlu = (char*)malloc(sizeof(char)*strlen(token)+1);
	strcpy_s(c.titlu, strlen(token) + 1, token);

	token = strtok(NULL, sep);
	c.autor = (char*)malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(c.autor, strlen(token) + 1, token);

	token = strtok(NULL, sep);
	c.anPublicare = atoi(token);

	token = strtok(NULL, sep);
	c.pret = atof(token);
	
	return c;
}
int calculeazaInaltimea(Nod* arbore)
{
	if (arbore)
	{
		int inalSt = calculeazaInaltimea(arbore->st);
		int inalDr = calculeazaInaltimea(arbore->dr);
		return 1 + (inalSt > inalDr ? inalSt : inalDr);
	}
	else
	{
		return 0;
	}
}
int gradEchilibru(Nod* arbore)
{
	if (arbore)
	{
		return calculeazaInaltimea(arbore->st) - calculeazaInaltimea(arbore->dr);
	}
	else {
		return 0;
	}
}
void rotireLaDreapta(Nod** arbore)
{
	Nod* aux = (*arbore)->st;
	(*arbore)->st = (*arbore)->dr;
	(*arbore)->dr = aux;
}
void rotireLaStanga(Nod** arbore)
{
	Nod* aux = (*arbore)->dr;
	(*arbore)->dr = (*arbore)->st;
	(*arbore)->st = aux;
}
 void adaugareCarteInArbore(Nod** arbore, Carte carteNoua)
{
	 if (!(*arbore))
	 {
		 Nod* nodNou = (Nod*)malloc(sizeof(Nod));
		 nodNou->info = carteNoua;
		 nodNou->st = NULL;
		 nodNou->dr = NULL;
		 (*arbore) = nodNou;
	 }
	 else
	 {
		 if (strcmp((*arbore)->info.titlu , carteNoua.titlu)>0)
		 {
			 adaugareCarteInArbore(&(*arbore)->st, carteNoua);
		 }
		 else
              if (strcmp((*arbore)->info.titlu, carteNoua.titlu) < 0)
			 {
				 adaugareCarteInArbore(&(*arbore)->dr, carteNoua);
			 }
		 // transformam in avl
		 int grad = gradEchilibru(*arbore);
		 if (grad == 2)
		 {
			 if (gradEchilibru((*arbore)->st) >= 0)
			 {
				 rotireLaDreapta(arbore);
			 }
			 else
			 {
				 rotireLaStanga(&(*arbore)->st);
				 rotireLaDreapta(arbore);
			 }
		 }
		 else
			 if (grad == -2)
			 {
				 if (gradEchilibru((*arbore)->dr) <= 0)
				 {
					 rotireLaStanga(arbore);
				 }
				 else
				 {
					 rotireLaDreapta(&(*arbore)->dr);
					 rotireLaStanga(arbore);
				 }
			 }
		 
	 }
}
 Nod* citireArboreDeCarti(const char* numeFisier)
 {
	 FILE* f = fopen(numeFisier, "r");
	 Nod* arbore = NULL;
	 while (!feof(f))
	 {
		 Carte c = citireCarteDinFisier(f);
		 adaugareCarteInArbore(&arbore, c);
	 }
	 fclose(f);
	 return arbore;
 }
 void afisareCarte(Carte c)
 {
	 printf("Nume: %s\n", c.titlu);
	 printf("Autor:%s\n", c.autor);
	 printf("An publicare: %d\n", c.anPublicare);
	 printf("Pret: %.2f\n", c.pret);
 }
 void afisareInordine(Nod* arbore)
 {
	 if(arbore)
	 {
		 afisareInordine(arbore->st);
		 afisareCarte(arbore->info);
		 afisareInordine(arbore->dr);
	 }
 }
/* Scrieți o funcție care returnează cartea cu prețul cel mai mare(deep copy).*/
 Carte copiazaCarte(Carte original)
 {
	 Carte copie;
	 copie.autor = malloc(sizeof(char) * strlen(original.autor) + 1);
	 strcpy(copie.autor, original.autor);
	 copie.titlu = malloc(sizeof(char) * strlen(original.titlu) + 1);
	 strcpy(copie.titlu, original.titlu);
	 copie.pret = original.pret;
	 copie.anPublicare = original.anPublicare;
	 return copie;

 }
 Carte getCarteaCuPretMax(Nod* arbore)
 {
	 if (arbore == NULL) {
		 Carte c;
		 c.titlu = NULL;
		 c.autor = NULL;
		 c.anPublicare = -1;
		 c.pret = -1.0f;
		 return c;
	 }
	 else
	 {
		 Carte carteMax = arbore->info;
		 Carte st = getCarteaCuPretMax(arbore->st);
		 Carte dr = getCarteaCuPretMax(arbore->dr);
		 if (st.pret > carteMax.pret)
			 carteMax = st;
		 if (dr.pret > carteMax.pret)
			 carteMax = dr;

		 return copiazaCarte(carteMax);
	 }
 }
 void dezalocare(Nod** arbore)
 {
	 if ((*arbore))
	 {
		 dezalocare(&(*arbore)->st);
		 dezalocare(&(*arbore)->dr);
		 free((*arbore)->info.autor);
		 free((*arbore)->info.titlu);
		 free((*arbore));
		 (*arbore) = NULL;
	 }
 }
 int main()
 {
	 Nod* arbore = NULL;
	 arbore = citireArboreDeCarti("carti.txt");
	 afisareInordine(arbore);

	 Carte gcpm = getCarteaCuPretMax(arbore);
	 printf("Cartea cu pretul maxim este:\n");
	 afisareCarte(gcpm);

	 dezalocare(&arbore);
	 return 0;
 }