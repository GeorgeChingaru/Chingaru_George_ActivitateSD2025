#include<headers.h>
#include<stdio.h>
//-------------STATIC------------//
int f() {
	static int x = 0;
	x++;
	return x;
}
//---------------------------------//
//pt extern
int i;
//------
int main()
{ 
	//AUTO//
	//teoretic acest cod este gresit: la siruri trebuia char*,
	//auto are  val implicita int
	auto optPunct = 8.321;
	int noua = 9;
	auto double c;
	c = 8.321;
	
	double suma = optPunct + noua;
	printf("Suma unei variabile auto si int = %f\n", suma);
	suma = c + noua;
	printf("Suma unei variabile auto double si int = %f\n", suma);

	auto ps = "sir_1";
	auto int psi = "sir_2";
	auto char* psc = "sir_3";

	printf("ps = %s\n",ps );
	printf("psi = %s\n",psi );
	printf("psc = %s\n",psc );

	ps = psc;
	printf("\nps = %s\n", ps);

	noua = psi;
	printf("noua = %s\n", noua);
	//----------------------------
	//STATIC - evidentiaza persistenta pe toata durata de executie a aplicatiei (x=1..2..3..10, nu se reseteaza la 0)
	int j;
	for (j = 0; j < 10; j++)
	{
		printf("Rezultat apel functie: %d\n", f());
	}
	//----------------------
	// *mai este si EXTERN!
//REGISTER - acces direct la locatiile de memorie, lucreaza cu registrii, trebuie folosit compilator X32 ca sa mearga
	register int vreg;
	int d;
	d = 0x18; // d are valoarea 24 in baza 10
	vreg = d;
	printf("vreg= 0x%08X (%d)\n", vreg, vreg);

	__asm// introd secv scrisa in cod limbaj asamblare
	{
		mov eax, vreg //incarc registrul eax cu 0x18/24 al d
		mov vreg, ecx // rescrie var vreg cu continutul reg ECX
	};

	printf("vreg= 0x%08X (%d)\n",vreg, vreg);

	// EXTERN

	 i=3;

	 f();
	 printf("%d\n", i);

	return 0;
}