#include<stdio.h>
#include<malloc.h>
typedef struct Telefon Telefon;
struct Telefon {
	int id;
	int RAM ;
	char* producator ;
	float pret ;
	char serie;
};
Telefon initializare(int id, int ram,const char* producator, float pret, char serie)
{
	Telefon t;
	t.id = id;
	t.RAM = ram;
	t.producator = (char*)malloc(sizeof(char)*(strlen(producator)+1));
	strcpy_s(t.producator, strlen(producator) + 1);
	t.pret = pret;
	t.serie = serie;
	return t;

}
void afisare(Telefon t)
{
	if (t.producator != NULL) {
				printf("%d. Telefonul %s seria %c are %d GB RAM si costa %5.2f RON.\n",
					t.id, t.producator, t.serie, t.RAM, t.pret);
			}
			else {
				printf("%d. Telefonul din seria %c are %d GB RAM si costa %5.2f RON.\n",
					t.id, t.serie, t.RAM, t.pret);
			}

}

void afisareVector(struct Telefon* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	for (int i = 0; i < nrElemente; i++)
		afisare(vector[i]);
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Telefon *vectorNou=NULL;
	vectorNou = (Telefon*)malloc(sizeof(Telefon) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		//shallow copy
		vectorNou[i] = vector[i];
		//deep copy - pentru a putea modifica doar vectorul nou
		vectorNou[i].producator = (char*)malloc(sizeof(char) * strlen(vector[i].producator) + 1);
		strcpy_s(vectorNou[i].producator, strlen(vector[i].producator) + 1,vector[i].producator);
	}

	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < (*nrElemente); i++)
	{
		if ((*vector[i]).producator != NULL)
		{
			free((*vector[i]).producator);
		}
		free(*vector);
		(*vector) = NULL;
		nrElemente = 0;

		}
}

void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret >= pretMinim)
		{
			(*dimensiune)++;
		}

	}
	if ((*vectorNou) != NULL)
	{
		free(*vectorNou);
	}
	*vectorNou = malloc(sizeof(Telefon) * (*dimensiune));
	int k = 0;//pozitia 
	for(int i=0;i<nrElemente;i++)
		if (vector[i].pret >= pretMinim)
		{
			(*vectorNou)[k] = vector[i];//*(vector+i),deferentierea se face prin index
			(*vectorNou)[k].producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy_s((*vectorNou)[k].producator, strlen(vector[i].producator) + 1, vector[i].producator);//destinatia,lungimea,sursa
			k++; 
		}

}

struct Telefon getPrimulTelefonByProducator(struct Telefon* vector, int nrElemente, const char* producator) {
	struct Telefon t;
	t.producator = NULL;
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].producator, producator) == 0) {
			t = vector[i];
			t.producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy_s(t.producator, strlen(vector[i].producator) + 1, vector[i].producator);
			return t;
		}
	}
	return t;
}


int main() {
	Telefon* telefoane=NULL;// vector de telefoane /pointer
	int nrTelefoane = 3;
	telefoane = (Telefon*)malloc(sizeof(Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Samsung", 799.99,  'S');
		telefoane[1]= initializare(2, 256, "Motorola", 999.99, 'S');
		telefoane[2]= initializare(3, 256, "Apple", 1799.99, 'P');
		afisareVector(telefoane, nrTelefoane);
		Telefon* primeleTelefoane = NULL;
		int nrPrimeleTelefoane = 2;
		primeleTelefoane = copiazaPrimeleNElemente(telefoane, nrTelefoane, nrPrimeleTelefoane);
		dezalocare(&primeleTelefoane,&nrPrimeleTelefoane);
		afisareVector(primeleTelefoane, nrPrimeleTelefoane);
		
		//copiaza telefoane scumpe
		Telefon* telefoaneScumpe = NULL;
		int nrTelefoaneScumpe = 0;
		copiazaTelefoaneScumpe(telefoane, nrTelefoane, 2000, &telefoaneScumpe, &nrTelefoaneScumpe);
		afisareVector(telefoaneScumpe, nrTelefoaneScumpe);
		dezalocare(&telefoaneScumpe, &nrTelefoaneScumpe);

			struct Telefon telefon = getPrimulTelefonByProducator(telefoane, nrTelefoane, "Apple");
	printf("\n\nTelefonul gasit:\n");
	afisare(telefon);
	if (telefon.producator != NULL) {
		free(telefon.producator);
		telefon.producator = NULL;
	}
	dezalocare(&telefoane, &nrTelefoane);

		return 0;
}