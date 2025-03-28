#include<stdio.h>
#include<malloc.h>
#define LINESIZE 256
typedef struct adresa {
	char* strada;
	unsigned short int numar;
	char* cladire;
}Adresa;

typedef struct factura {
	char* id_factura;
	char* id_client;
	float valoare;
	Adresa adresa_client;
}Factura;

double valoare_facturi(Factura*, unsigned char);
double valoare_pfacturi(Factura**, unsigned char);
int main()
{
	struct factura fact_1;
	Factura* pfact_2;

	FILE* f;
	//fisierul Facturi.txt contine o factura pe fiecare linie
	f = fopen("Facturi.txt", "r");
	char* token, file_line_buf[LINESIZE], sep_list[] = ",\n";
	fgets(file_line_buf, sizeof(file_line_buf), f);//preluarea continutului de pe linia 1

	token = strtok(file_line_buf, sep_list);
	fact_1.id_factura = malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(fact_1.id_factura, token);
	
	token = strtok(NULL, sep_list);
	fact_1.id_client = malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(fact_1.id_client, token);

	token = strtok(NULL, sep_list);
	fact_1.valoare = atof(token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.strada = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(fact_1.adresa_client.strada, token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.numar =atoi(token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.cladire = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(fact_1.adresa_client.cladire, token);

	token = strtok(NULL, sep_list);
	if (token)
		printf("\nEroare preluare token");

	

	return 0;
}