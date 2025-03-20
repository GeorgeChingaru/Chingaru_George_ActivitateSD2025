#include<stdio.h>
#include<malloc.h>
#include<string.h>
int main() {
	unsigned char x = 103;// variabila date tip primar, zona memorie 1 byte ([0,255])

	unsigned char* px = NULL;//var pointer ; se aloca la compilare, sizeof(px) bytes=4bytes

	//Utilizare adresa variabila tip de date primar
	px = &x; // adresa de stack seg a lui x scrisa in variabila px
	printf("///////////////////////////////////////\n");
	printf("Adrese si continuturi initiale ale variabilelor x si px:\n");
	printf("Adresa segment stack continuta de variabila px a fost alocata la compilare = 0x%p\n", &px);
	printf("Adresa segment stack continuta de variabila px=0x%p\n", px);
	printf("Continut existent la adresa din variabila px=%u\n", *px);
	printf("Adresa segment stack unde variabila x a fost alocata la compilare = 0x%p\n", &x);
	printf("Continut (valoare intreaga) variabila x=%u\n", x);



	return 0;
}