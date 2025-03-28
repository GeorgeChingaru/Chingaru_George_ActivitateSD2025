#include<stdlib.h>
#include<stdio.h>
typedef struct Telefon Telefon;
struct Telefon {
	int id;
	int RAM;
		char* producator;
		float pret;
		char serie; // Samsung S/A...
};

Telefon initializare(int id, int ram,const char* producator, float pret, char serie)
{
	Telefon t;
	t.id = id;
	t.RAM = ram;
	t.producator = (char*)malloc(sizeof(char)*(strlen(producator)+1));
	strcpy_s(t.producator, strlen(producator) + 1);
	t.pret = pret;
	t.serie = serie;
	return t;

}
void afisare(Telefon t)
{
	printf("$d. Telefonul %s are seria %d Gb RAM si costa costa %5.2f RON\n", t.id, t.producator, t.serie, t.pret);

}
void modificaPret(Telefon* t, float noulPret) {
	if (noulPret > 0)
	{
		t->pret = noulPret;
	}
}
void dezalocare(Telefon* t)
{
	if (t->producator != NULL) {
		free(t->producator);
		t->producator = NULL;
	}
}

int main()
{
	Telefon t;
	t = initializare(1, 256, "Samsung", 2000.5,'A');
	afisare(t);
	modificaPret(&t, 1000);
	afisare(t);
	dezalocare(&t);
	afisare(t);

	return 0;
}