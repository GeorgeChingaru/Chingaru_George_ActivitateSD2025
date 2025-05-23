#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
enum Stare {
	FARA_URGENTA,USOARA, MEDIE, GRAVA, EXTREMA // 0,1,2,3,4
};
typedef enum Stare Stare;
struct Pacient {
	int id;
	char* nume;
	int varsta;
	char sex;
   Stare stare;
};
typedef struct Pacient Pacient;
struct Heap {
	int lungime;
	Pacient* v;
	int nrPacienti;
};
typedef struct Heap Heap;

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrPacienti = 0;
	heap.v =(Pacient*)malloc(sizeof(Pacient)*lungime);
	return heap;
}
void filtrareHeap(Heap heap, int pozitieNod)
{
	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;
	if (pozFiuSt<heap.nrPacienti&&heap.v[pozMax].stare < heap.v[pozFiuSt].stare)
	{
		pozMax = pozFiuSt;
	}
	if (pozFiuDr<heap.nrPacienti&&heap.v[pozMax].stare < heap.v[pozFiuDr].stare)
	{
		pozMax = pozFiuDr;
	}
	if (pozMax != pozitieNod)
	{
		Pacient aux = heap.v[pozMax];
		heap.v[pozMax] = heap.v[pozitieNod];
		heap.v[pozitieNod] = aux;
		if (pozMax <= (heap.nrPacienti - 2) / 2)
		{
			filtrareHeap(heap, pozMax);
		}
		
	}

}
Pacient citirePacient(FILE* f)
{
	Pacient p;
	char* token, buffer[256], sep[] = ",\n";
	fgets(buffer, 256, f);

	token = strtok(buffer, sep);
	p.id = atoi(token);

	token = strtok(NULL, sep);
	p.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(p.nume, strlen(token) + 1, token);

	token = strtok(NULL, sep);
	p.varsta = atoi(token);

	token = strtok(NULL, sep);
	p.sex = token[0];

	token = strtok(NULL, sep);
	p.stare = (Stare)atoi(token);

	return p;
 }
void afisarePacient(Pacient p)
{
	printf("Nume pacient: %s\n", p.nume);
	printf("Varsta: %d\n", p.varsta);
	printf("Sex: %c\n", p.sex);
	printf("Stare: %d\n", p.stare);
}
Heap citireHeapDePacienti(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializareHeap(7);
	while (!feof(f))
	{
		heap.v[heap.nrPacienti++] = citirePacient(f);
		
	}
	fclose(f);
	for (int i = (heap.nrPacienti - 2) / 2; i >= 0; i--)
	{
		filtrareHeap(heap, i);
	}
	return heap;

}
void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.nrPacienti; i++)
	{
		afisarePacient(heap.v[i]);
	}
}
void afisareHeapAscuns(Heap heap)
{
	for (int i = heap.nrPacienti; i < heap.lungime; i++)
	{
		afisarePacient(heap.v[i]);
	}
}
Pacient extragePacient(Heap* heap)
{
	if (heap->nrPacienti > 0)
	{
		Pacient aux = heap->v[0];
		heap->v[0] = heap->v[heap->nrPacienti - 1];
		heap->v[heap->nrPacienti - 1] = aux;
		heap->nrPacienti--;
		for (int i = (heap->nrPacienti - 2) / 2; i >= 0; i--)
		{
			filtrareHeap(*heap, i);
		}
		return aux;
	}
}
void dezalocare(Heap* heap)
{
	for (int i = 0; i < heap->lungime; i++)
	{
		free(heap->v[i].nume);
	}
	free(heap->v);
	heap->lungime = 0;
	heap->nrPacienti = 0;
	heap->v = NULL;
}
int main()
{
	Heap heap = citireHeapDePacienti("pacienti.txt");
	printf("Afisare pacienti:\n");
	afisareHeap(heap);

	printf("Afisare pacient extras:\n");
	afisarePacient(extragePacient(&heap));
	afisarePacient(extragePacient(&heap));
	printf("Afisare pacienti ascuns:\n");
	afisareHeapAscuns(heap);
	printf("Afisare pacienti dezalocati:\n");
	dezalocare(&heap);
	return 0;
}