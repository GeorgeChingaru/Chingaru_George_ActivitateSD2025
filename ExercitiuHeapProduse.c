#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <stdlib.h>

/*✅ ENUNȚ TEMĂ – GESTIONAREA UNUI HEAP DE PRODUSE
Scrie un program C care să gestioneze un heap de produse stocate într-un fișier text. Un produs are următoarele câmpuri:
int id – identificator numeric,
char* denumire – denumirea produsului,
float pret – prețul produsului,
int stoc – numărul de unități disponibile.
🔧 Cerințe:
Creează o structură Produs și o structură Heap care să conțină:
un vector dinamic de produse (Produs* vector),
un câmp nrProduse – câte produse reale sunt în heap,
un câmp capacitate – câtă memorie este alocată.
Heap-ul va fi un MAX-HEAP în funcție de prețul produsului (pret).
Implementează următoarele funcții:
Produs citireProdusDinFisier(FILE* f) – citește un produs de pe o linie.
Heap citireHeapDinFisier(const char* numeFisier) – citește toate produsle și creează un heap.
void filtreazaHeap(Heap heap, int poz) – reface proprietatea de heap pentru poziția poz.
Produs extrageProdus(Heap* heap) – extrage produsul cu prețul cel mai mare.
void afisareProdus(Produs p) și void afisareHeap(Heap h) – afișează conținutul.
După citirea din fișier, afișează heap-ul, apoi extrage 5 produse și afișează-le.
La final, eliberează toată memoria alocată.
*/

struct Produse {
	int id;
	char* denumire;
	float pret;
	int stoc;
};
typedef struct Produse Produse;

struct Heap {
	int lungime;
	Produse* v;
	int nrProduse;
};
typedef struct Heap Heap;

Produse citireProdusDinFisier(FILE* f)
{
	Produse p;
	char* token, buffer[256], sep[] =",\n";
	fgets(buffer, 256, f);
	
		token = strtok(buffer, sep);
		p.id = atoi(token);
		
		token = strtok(NULL, sep);
		p.denumire = (char*)malloc(sizeof(char) * strlen(token)+1);
		strcpy_s(p.denumire, strlen(token) + 1, token);

		token = strtok(NULL, sep);
		p.pret = atof(token);

		token = strtok(NULL, sep);
		p.stoc = atoi(token);
		
		return p;
}
void afisareProduse(Produse p)
{
	printf("ID: %d\n", p.id);
	printf("Denumire: %s\n",p.denumire);
	printf("Pret: %.2f\n", p.pret);
	printf("Stoc: %d\n", p.stoc);
}
Heap initializareHeap(int lungime)
{
	Heap heap;
	heap.lungime = lungime;
	heap.v = (Produse*)malloc(sizeof(Produse) * lungime);
	heap.nrProduse = 0;
	return heap;
}
void filtreazaHeap(Heap heap, int pozitieNod)
{
	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;
	if (pozFiuSt<heap.nrProduse&&heap.v[pozMax].pret<heap.v[pozFiuSt].pret) {
		pozMax = pozFiuSt;

	}
	if (pozFiuDr<heap.nrProduse&&heap.v[pozMax].pret < heap.v[pozFiuDr].pret) {
		pozMax = pozFiuDr;

	}
	if (pozMax != pozitieNod)
	{
		Produse aux=heap.v[pozMax];
		heap.v[pozMax] = heap.v[pozitieNod];
		heap.v[pozitieNod] = aux;
		//ultimul parinte
		if (pozMax <= (heap.nrProduse - 2) / 2)
		{
			filtreazaHeap(heap, pozMax);
		}
	}


}
Heap citireHeapDeProduseDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(4);
	while (!feof(file))
	{
		heap.v[heap.nrProduse++]=citireProdusDinFisier(file);
	}
	fclose(file);
	//plecam de la ultimul parinte catre radacina
	for (int i = (heap.nrProduse - 2) / 2; i >= 0; i--)
	{
		filtreazaHeap(heap, i);
	}
	return heap;
}
void afisareProduseHeap(Heap heap)
{//doar cele vizibile
	for(int i=0;i<heap.nrProduse;i++)
	{
		afisareProduse(heap.v[i]);
	}
}
Produse extrageProdus(Heap* heap)
{
	if ((*heap).nrProduse>0)
	{
		Produse aux = heap->v[0];
		heap->v[0] = heap->v[heap->nrProduse - 1];
		heap->v[heap->nrProduse - 1]=aux;
		heap->nrProduse--;
		for (int i = (heap->nrProduse - 2) / 2; i >= 0; i--)
		{
			filtreazaHeap(*heap, i);
		}
		return aux;
	}
	
}
void afiseazaHeapAscuns(Heap heap)
{
	for (int i = heap.nrProduse; i < heap.lungime; i++)
			{
				afisareProduse(heap.v[i]);
			}
}
void DezalocareHeap(Heap* heap)
{
	for (int i = 0; i < heap->lungime; i++) {
				free(heap->v[i].denumire);
				
			}
			free(heap->v);
			heap->v = NULL;
			heap->lungime = 0;
			heap->nrProduse = 0;
		}


int main()
{
	Heap heap = citireHeapDeProduseDinFisier("produse.txt");
	afisareProduseHeap(heap);
	
	afisareProduse(extrageProdus(&heap));
	
	printf("Heap ascuns:\n");
	afiseazaHeapAscuns(heap);

	DezalocareHeap(&heap);
	return 0;
}