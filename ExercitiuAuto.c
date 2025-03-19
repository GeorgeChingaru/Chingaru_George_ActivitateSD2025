#include<stdio.h>
int main()
{
	//teoretic acest cod este gresit: la siruri trebuia char*,
	//auto are val implicita int
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

	return 0;
}