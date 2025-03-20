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
///
	*px = x + 3;//modificarea indirecta a variabilei x
	printf("Adrese si continuturi initiale ale variabilelor x si px dupa modificarea continutului lui x:\n");
	printf("Adresa segment stack unde variabila px a fost alocata la compilare = 0x%p\n", &px);
	printf("Adresa segment stack continuta de variabila px=0x%p\n", px);
	printf("Continut existent la adresa din variabila px=%u\n", *px);
	printf("Adresa segment stack unde variabila x a fost alocata la compilare = 0x%p\n", &x);
	printf("Continut (valoare intreaga) variabila x=%u\n", x);
	//

	///pointer constant la int
	int vint = 13, j = 9;
	int* const pci = &vint; // obligatoriu, initializarea pci la mom declararii
	
	printf("///////////////////////////////////////\n");
	printf("Adrese si continuturi initiale ale variabilelor vint si pci:\n");
	printf("Adresa segment stack un variabila pointer ct pci a fost alocata la compilare = 0x%p\n", &pci);
	printf("Adresa segment stack continuta de variabila pci=0x%p\n", pci);
	printf("Continut existent la adresa din variabila pointer ct pci=%u\n", *pci);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);
	printf("Continut (valoare intreaga) variabila vint=%u\n", vint);
	//ideea este ca nu poti modifica adresa pointerului, ea ramane constanta
	//pci=&j //! eroare de compilare
	
	//pointer la int constant
	int const* pint;
	pint= &vint;

	printf("///////////////////////////////////////\n");
	printf("Adrese si continuturi initiale ale variabilelor vint si  pointerului pint:\n");
	printf("Adresa segment stack un variabila pointer la int const pint a fost alocata la compilare = 0x%p\n", &pint);
	printf("Adresa segment stack continuta de variabila pint=0x%p\n", pint);
	printf("Continut existent la adresa din variabila pointer  pint=%u\n", *pint);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);
	printf("Continut (valoare intreaga) variabila vint=%u\n", vint);
	//ideea este ca nu poti modifica valoarea catre care  pointeaza, ea ramane constanta
	//*pint=vint+5; //! eroare de compilare

	//pointer constant la int constant
	const int* const pint2 = &vint;

	printf("///////////////////////////////////////\n");
	printf("Adrese si continuturi initiale ale variabilelor vint si  pointerului pint2:\n");
	printf("Adresa segment stack un variabila pointer const la int const pint2 a fost alocata la compilare = 0x%p\n", &pint2);
	printf("Adresa segment stack continuta de variabila pint2=0x%p\n", pint2);
	printf("Continut existent la adresa din variabila pointer  pint2=%u\n", *pint);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);
	printf("Continut (valoare intreaga) variabila vint=%u\n", vint);
	//ideea este ca nu poti modifica valoarea catre care  pointeaza si nici adresa , ambele ramanand constanta
	//*pint2=vint+5; pint2=&j; //! eroare de compilare


		return 0;
}