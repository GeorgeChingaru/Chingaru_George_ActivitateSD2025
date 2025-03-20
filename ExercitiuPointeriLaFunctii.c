#include<stdio.h>
double f(float x, float y)
{
	double s;
	s = x + y;
	return s;
}

double g(float x, float y)
{
	double d;
	d = x / y;
	return d;
}
double FP(float x, float y, double(*fp)(float, float))
{
	x = x + 1;
	y = (float)(y + 2.2);

	double op = fp(x, y);
	return op;
}

int main()
{
	float a = 1.2f, b = 4.7f;
	double c;

	//definire si utilizare pointer la functie

	double (*pFct)(float, float); //var loc functiei main();alocare la compilare in stack seg

	pFct = f; // "incercare" adresa inceput functie sumaValoare in pSumaVal

	printf("//////////////////////////////////////////////////\n");
	printf("Adresa ?i con?inut ini?ial variabila pointer la func?ie pFct:\n");
	printf("Adresa segment stack unde variabila pFct a fost alocatã la compilare = 0x%p\n", &pFct);
	printf("Adresa segment de cod con?inutã de variabila pFct = 0x%p\n", pFct);

	c = pFct((float)(a + 1), (float)(b + 2.2));
	printf("Rezultat apel func?ie f prin pointer la func?ie: %lf\n", c);

	c = FP(a, b, pFct);
	printf("\nRezultat #1 apel func?ie cu parametru pointer la func?ie: %lf\n", c);

	pFct = g; // "încãrcare" adresa început func?ie sumaValoare în pSumaVal

	printf("//////////////////////////////////////////////////\n");
	printf("Adresa ?i con?inut dupã modificare pentru variabila pointer la func?ie pFct:\n");
	printf("Adresa segment stack unde variabila pFct a fost alocatã la compilare = 0x%p\n", &pFct);
	printf("Adresa segment de cod con?inutã de variabila pFct = 0x%p\n", pFct);

	c = pFct((float)(a + 1), (float)(b + 2.2));
	printf("Rezultatul apel func?ie g prin pointer la func?ie: %lf\n", c);

	c = FP(a, b, pFct);
	printf("\nRezultatul #2 apel func?ie cu parametru pointer la func?ie: %lf\n", c);



	return 0;
}
