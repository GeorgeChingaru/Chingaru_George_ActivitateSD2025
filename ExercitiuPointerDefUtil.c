#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define VECTOR_SIZE 10
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

	// adresa variabila tip vector

	unsigned char vx[VECTOR_SIZE]; //Variabila de tip vector; Vector_size elemente alocate; avand lungimea 1 byte
	px = vx;// scriere adresa de segment stack a lui vx in px
	for (unsigned char i = 0; i < sizeof(vx); i++)
		px[i] = x + i; // px[i]<-->*(px+i)

	printf("///////////////////////////////////////\n");
	printf("Adrese si continuturi initiale ale variabilelor vx si  pointerului px dupa init elem:\n");
	printf("Adresa segment stack un variabila px a fost alocata la compilare = 0x%p\n", &px);
	printf("Adresa segment stack continuta de variabila px=0x%p\n", px);
	printf("Adresa segment stack unde variabila vx a fost alocata la compilare = 0x%p\n", &vx);

	for (unsigned char i = 0; i < sizeof(vx); i++)
	{
		printf("Element vx[%u]: Adresa segment stack = 0x%p, Continut (val intreaga) =%u\n", i + 1, px + i, px[i]);
	}
	//

	///utilizare string-uri
	char str[] = "Aplicatie in C";
	
	unsigned char* ppc = (unsigned char*)str;

	printf("///////////////////////////////////////\n");
	printf("Adrese si continuturi initiale ale variabilelor str si ppc dupa init elem:\n");
	printf("Adresa segment stack un variabila ppc a fost alocata la compilare = 0x%p\n", &ppc);
	printf("Adresa segment stack continuta de variabila ppc=0x%p\n", ppc);
	printf("Adresa segment stack unde variabila str a fost alocata la compilare = 0x%p\n", &str);
	printf("Dimensiune vector=%u elemente, Lungime sir caract = %d caract/simb, Continut (string ascii)variabila str/ppc =%s\n", sizeof(str), strlen(str), str);
	
	printf("Continut (format hexa) elemente vector str/ppc\n");
	for (unsigned char i = 0; i < sizeof(str); i++)
	{
		printf("Element str[%u]: 0x%02X\n",i+1,ppc[i]);

	}

	str[strlen(str)] = 1;

	printf("Adrese si continuturi initiale ale variabilelor str si ppc dupa rescrierea terminatorului sir de caract:\n");
	printf("Adresa segment stack un variabila ppc a fost alocata la compilare = 0x%p\n", &ppc);
	printf("Adresa segment stack continuta de variabila ppc=0x%p\n", ppc);
	printf("Adresa segment stack unde variabila str a fost alocata la compilare = 0x%p\n", &str);
	printf("Dimensiune vector=%u elemente, Lungime sir caract = %d caract/simb, Continut (string ascii)variabila str/ppc =%s\n", sizeof(str), strlen(str), str);

	printf("Continut (format hexa) elemente vector str/ppc\n");
	for (unsigned char i = 0; i < sizeof(str); i++)
	{
		printf("Element str[%u]: 0x%02X\n", i + 1, ppc[i]);

	}
	///

	//utilizare vector de pointeri
	int* vpi[VECTOR_SIZE];
	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	{
		vpi[i] = &vint;
	}

	printf("//////////////////////////////////////////////////\n");
	printf("Adrese si continuturi ale variabilelor vint si vpi dupa initializarea elementelor din vpi:\n");

	printf("Adresa segment stack unde variabila vector vpi a fost alocata la compilare = 0x%p\n", &vpi);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);

	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	{
		printf("Element vpi[%u]: Adresa segment stack = 0x%p, Continut (adresa segment stack variabila vint) = 0x%p\n",
			i, vpi + i, vpi[i]);
	}

	vpi[1] = vpi[0] + 1; // aritmetica de pointeri aplicata pentru int (&vint + 1)

	printf("Adrese si continuturi ale variabilelor vint si vpi dupa modificarea elementului vpi[1]:\n");

	printf("Adresa segment stack unde variabila vector vpi a fost alocata la compilare = 0x%p\n", &vpi);
	printf("Adresa segment stack unde variabila vint a fost alocata la compilare = 0x%p\n", &vint);

	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	{
		printf("Element vpi[%u]: Adresa segment stack = 0x%p, Continut (adresa segment stack) = 0x%p\n",
			i, vpi + i, vpi[i]);
	}

	// ///
	 
	 //// alocarea vector la run-time
	unsigned char n = (unsigned char)(strlen(str) - 2); // lungime determinata de existenta unui byte cu valoarea 0

	px = (unsigned char*)malloc(n * sizeof(unsigned char));

	for (char i = 0; i < n; i++)
	{
		px[i] = ppc[i] + i;
	}

	printf("//////////////////////////////////////////////////\n");
	printf("Adrese si continuturi ale variabilelor px si n dupa alocare si initializare memorie heap:\n");

	printf("Adresa segment stack unde variabila px a fost alocata la compilare = 0x%p\n", &px);
	printf("Adresa segment heap continuta de variabila px = 0x%p\n", px);
	printf("Continut n (dimensiune vector) = %u elemente\n", n);

	for (char i = 0; i < n; i++)
	{
		printf("Element px[%u]: %u\n", i + 1, px[i]);
	}

	// dezalocare mem heap
	free(px);

	////////// mapare pointer peste o variabila existenta la nivel de byte
	int z = 0x7511DD80;
	unsigned char* pz = NULL;

	pz = (unsigned char*)&z;

	printf("//////////////////////////////////////////////////\n");
	printf("Adrese si continuturi initiale ale variabilelor z si pz:\n");
	printf("Adresa segment stack unde variabila pz a fost alocata la compilare = 0x%p\n", &pz);
	printf("Adresa segment stack continuta de variabila pz = 0x%p\n", pz);
	printf("Adresa segment stack unde variabila z a fost alocata la compilare = 0x%p\n", &z);
	printf("Continut (valoare intreaga) variabila z = %d\n", z);
	printf("Continut (format hexa BIG-ENDIAN) variabila z = 0x");

	// parsare byte cu byte a grupului (int = 4 bytes) alocat pentru variabila 
	// z la nivel fizic (reprezentare BIG ENDIAN)
	for (char i = 0; i < sizeof(int); i++)
		printf("%02X", pz[i]);

	printf("\n");

	// parsare byte cu byte a grupului (int = 4 bytes) alocat pentru variabila 
	// z la nivel logic (reprezentare LITTLE ENDIAN)
	printf("Continut (format hexa LITTLE-ENDIAN) variabila z = 0x");

	for (char i = sizeof(int) - 1; i >= 0; i--)
		printf("%02X", pz[i]);

	printf("\n");

	pz[2] = 0x89; // modificare byte cu offset 2 la nivel fizic (continutul anterior este 0x11, byte-ul 2 din initializarea lui z)
	// deoarece stocarea datelor la nivel fizic este conform LITTLE ENDIAN

	printf("Adrese si continuturi dupa modificare ale variabilelor z si pz:\n");
	printf("Adresa segment stack unde variabila pz a fost alocata la compilare = 0x%p\n", &pz);
	printf("Adresa segment stack continuta de variabila pz = 0x%p\n", pz);
	printf("Adresa segment stack unde variabila z a fost alocata la compilare = 0x%p\n", &z);
	printf("Continut (valoare intreaga) variabila z = %d\n", z);
	printf("Continut (format hexa BIG-ENDIAN) variabila z = 0x");

	for (char i = 0; i < sizeof(int); i++)
		printf("%02X", pz[i]);

	printf("\n");

	printf("Continut (format hexa LITTLE-ENDIAN) variabila z = 0x");

	for (char i = sizeof(int) - 1; i >= 0; i--)
		printf("%02X", pz[i]);

	printf("\n");





		return 0;
}