#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<locale.h>
#define LINESIZE 256
#define _CRT_SECURE_NO_WARNINGS
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
	setlocale(LC_NUMERIC, "C");
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
	printf("Token valoare: '%s'\n", token);
	fact_1.valoare = (float)atof(token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.strada = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(fact_1.adresa_client.strada, token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.numar =(float)atoi(token);

	token = strtok(NULL, sep_list);
	fact_1.adresa_client.cladire = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(fact_1.adresa_client.cladire, token);

	token = strtok(NULL, sep_list);
	if (token)
		printf("\nEroare preluare token");

	//incarcare date factura 2
	fgets(file_line_buf, sizeof(file_line_buf), f); //preluare continut linia 2 din fisierul Facturi.txt

	//avand in vedere ca avem pointer la tipul factura trebuie sa ii alocam memorie

	pfact_2 = (Factura*)malloc(sizeof(Factura));

	token = strtok(file_line_buf, sep_list);
	pfact_2->id_factura = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(pfact_2->id_factura, token);

	token = strtok(NULL, sep_list);
	pfact_2->id_client = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(pfact_2->id_client, token);
	
	token=strtok(NULL, sep_list);
	pfact_2->valoare =(float) atof(token);

	token = strtok(NULL, sep_list);
	pfact_2->adresa_client.strada = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(pfact_2->adresa_client.strada, token);
	
	token = strtok(NULL, sep_list);
	pfact_2->adresa_client.numar = atoi(token);

	token = strtok(NULL, sep_list);
	pfact_2->adresa_client.cladire = (char*)malloc(sizeof(char) * (strlen(token) + 1));
	strcpy(pfact_2->adresa_client.cladire, token);

	token = strtok(NULL, sep_list);
	if (token)
		printf("\nEroare la preluare token!");

	printf("///////////////////////////////////////////////////////////\n");
	printf("Detalii factura 1:\n");
	printf("ID factura: %s\n",fact_1.id_factura);
	printf("ID client: %s\n",fact_1.id_client);
	printf("Valoare factura: %f\n",fact_1.valoare);
	printf("Adresa client: %s, %u, %s\n", fact_1.adresa_client.strada, fact_1.adresa_client.numar, fact_1.adresa_client.cladire);// %d cu semn - + VS %u fara semn unsigned
	
	printf("///////////////////////////////////////////////////////////\n");
	printf("Detalii factura 2:\n");
	printf("ID factura: %s\n", pfact_2->id_factura);
	printf("ID client: %s\n", (*pfact_2).id_client);
	printf("Valoare factura: %f\n", pfact_2->valoare);
	printf("Adresa client: %s, %u, %s\n", pfact_2->adresa_client.strada, pfact_2->adresa_client.numar, pfact_2->adresa_client.cladire);// %d cu semn - + VS %u fara semn unsigned
	//dezalocare in main
	free(fact_1.id_client);
	free(fact_1.id_factura);
	free(fact_1.adresa_client.strada);
	free(fact_1.adresa_client.cladire);
	free(pfact_2->id_client);
	free(pfact_2->id_factura);
	free(pfact_2->adresa_client.strada);
	free(pfact_2->adresa_client.cladire);

	fclose(f);
	return 0;
}