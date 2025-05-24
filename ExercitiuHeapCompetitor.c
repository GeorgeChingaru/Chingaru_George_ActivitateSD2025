#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
/*Definiți structura Competitor, care conține următoarele câmpuri:
 nume (char*), scor total (float), număr probe finalizate (int), naționalitate (char*).
Implementați o structură de heap max care organizează competitorii după scor total.
Implementați o funcție de inserare a unui competitor în heap.
Implementați o funcție care extrage TOP 3 competitori cu cele mai bune scoruri.
Implementați o funcție care afișează toți competitorii existenți în heap.
Eliberați toată memoria alocată.


*/
struct Competitor {
	char* nume;
	float scor;
	int numarProbe;
	char* nationalitate;
};
typedef struct Competitor Competitor;
struct Heap {
	int lungime;
	Competitor* v;
	int nrCompetitori;
};
typedef struct Heap Heap;
Heap initializareHeap(int lungime)
{
	Heap heap;
	heap.lungime = lungime;
	heap.v = (Competitor*)malloc(sizeof(Competitor) * lungime);
	heap.nrCompetitori = 0;
	return heap;
}
Competitor citireCompetitorDinFisier(FILE* f)
{
	Competitor c;
	char* token, buffer[100], sep[] = ",\n";
	
	fgets(buffer, 100, f);
	
	token = strtok(buffer, sep);
	c.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(c.nume, strlen(token) + 1, token);

	token = strtok(NULL, sep);
	c.scor = atof(token);

	token = strtok(NULL, sep);
	c.numarProbe = atoi(token);

	token = strtok(NULL, sep);
	c.nationalitate = (char*)malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(c.nationalitate, strlen(token) + 1, token);

	return c;

}
void afisareCompetitor(Competitor c)
{
	printf("NUME: %s\n", c.nume);
	printf("SCOR: %.2f\n", c.scor);
	printf("NUMAR PROBE: %d\n", c.numarProbe);
	printf("NATIONALITATE: %s\n", c.nationalitate);

}
void fitrareHeap(Heap heap, int pozitieNod)
{
	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;
	if (pozFiuSt<heap.nrCompetitori&&heap.v[pozMax].scor < heap.v[pozFiuSt].scor)
	{
		pozMax = pozFiuSt;
	}
	if (pozFiuDr<heap.nrCompetitori&&heap.v[pozMax].scor < heap.v[pozFiuDr].scor)
	{
		pozMax = pozFiuDr;
	}
	if (pozMax != pozitieNod)
	{
		Competitor aux = heap.v[pozMax];
		heap.v[pozMax] = heap.v[pozitieNod];
		heap.v[pozitieNod] = aux;
		if (pozMax <= (heap.nrCompetitori - 2) / 2)
		{
			fitrareHeap(heap, pozMax);
		}
	}
}
Heap citireHeapDeCompetitori(const char* numeFisier)
{
	FILE* f = fopen(numeFisier, "r");
	Heap heap= initializareHeap(7);
	while (!feof(f))
	{
		heap.v[heap.nrCompetitori++] = citireCompetitorDinFisier(f);
	}
	fclose(f);
	for (int i = (heap.nrCompetitori - 2) / 2; i >= 0; i--)
	{
		fitrareHeap(heap, i);
	}
	return heap;
}

Competitor extrageCompetitor(Heap* heap)
{
	if (heap->nrCompetitori > 0)
	{
		Competitor aux = heap->v[0];
		heap->v[0] = heap->v[heap->nrCompetitori - 1];
		heap->v[heap->nrCompetitori - 1] = aux;
		heap->nrCompetitori--;
		for (int i = (heap->nrCompetitori - 2) / 2; i >= 0; i--)
		{
			fitrareHeap(*heap, i);
		}
		return aux;
	}
}
void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.nrCompetitori; i++)
	{

		afisareCompetitor(heap.v[i]);
	}
}
void afisareHeapAscuns(Heap heap)
{
	for (int i = heap.nrCompetitori; i < heap.lungime; i++)
	{

		afisareCompetitor(heap.v[i]);
	}
}
void dezalocare(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++)
	{
		if (heap->v[i].nume != NULL)
			free(heap->v[i].nume);
		if (heap->v[i].nationalitate != NULL)
			free(heap->v[i].nationalitate);
	}
	free(heap->v);
	heap->lungime = 0;
	heap->nrCompetitori = 0;
	heap->v = NULL;
}
int main() {
	Heap heap = citireHeapDeCompetitori("competitori.txt");
	afisareHeap(heap);
	printf("-----------------------------------------\n");
	printf("Extrage Top 3 competitori in concurs:\n");
	printf("LOCUL 1:\n");
	afisareCompetitor(extrageCompetitor(&heap));
	printf("-----------------------------------------\n");
	printf("LOCUL 2:\n");
	afisareCompetitor(extrageCompetitor(&heap));
	printf("-----------------------------------------\n");
	printf("LOCUL 3:\n");
	afisareCompetitor(extrageCompetitor(&heap));
	printf("-----------------------------------------\n");
	printf("Afisare crescatoare a castigatorilor:\n");
	afisareHeapAscuns(heap);
	printf("------------------------------------------\n");
	printf("Dupa terminarea concursului nu au mai ramas competitori:\n");
	dezalocare(&heap);
	afisareHeap(heap);

	return 0;
}