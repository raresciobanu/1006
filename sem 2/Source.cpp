#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996) //pentru a dezactiva _CRT_SECURE_NO_WARNINGS

enum CULORI
{
	ALB,
	NEGRU = 10,
	VERDE = 20,
	ROSU,
	ROZ
};

const char* transformaEnumInSirDeCaractere(CULORI culore) {
	switch (culore)
	{
	case ALB:
		return "alb";
	case NEGRU:
		return "negru";
	case VERDE:
		return "verde";
	case ROSU:
		return "rosu";
	default:
		return "culoarea introdusa nu a fost interpretata";
	}
}

CULORI transformaSirDeCaractereInEnum(const char* pointerCatreSir) {
	if (strcmp(pointerCatreSir, "alb") == 0) {
		return ALB;
	}
	else if (strcmp(pointerCatreSir, "negru") == 0) {
		return NEGRU;
	}
	else if (strcmp(pointerCatreSir, "verde") == 0) {
		return VERDE;
	}
	else if (strcmp(pointerCatreSir, "rosu") == 0) {
		return ROSU;
	}

	return ROZ;
}

//104 bytes
struct client {
	char nume[100];//100 bytes
	int varsta;//4 bytes
};

//100 bytes
union user
{
	char nume[100];//100 bytes
	int varsta;//4 bytes
	char gen;//1 byte
};

struct telefon {
	CULORI culoareTelefon;
	char* marca;
	double pret;
	int anFabricatie;
	char version;
	client proprietar;
};

void scrieClientLaConsola(client c) {
	printf("nume = %s\n", c.nume);
	printf("varsta = %d\n", c.varsta);
}

void citireClientDeLaConsola(client& c) {
	printf("nume = ");
	//getchar();//folosita pentru e a elibera bufferul de \n
	gets_s(c.nume);
	//scanf("%s", c.nume); //in cazul asta se citeste pana la primul spatiu

	printf("varsta = ");
	scanf("%d", &c.varsta);
}

void scrieClientInFisier(FILE* fisier, client c) {
	fprintf(fisier, "%s\n", c.nume);
	fprintf(fisier, "%d\n", c.varsta);
}

void citireClientDinFisier(FILE* fisier, client& c) {
	fgets(c.nume, 100, fisier);
	c.nume[strcspn(c.nume, "\n")] = 0; //pentru ca fgets citeste si cu \n de la final -> trebuie eliminat \n

	fscanf(fisier, "%d", &c.varsta);
	fgetc(fisier);
}


void scrieTelefonLaConsola(telefon t) {
	printf("culoare telefon = %s\n", transformaEnumInSirDeCaractere(t.culoareTelefon));

	printf("marca = %s\n", t.marca);
	printf("pret = %.2lf\n", t.pret);
	printf("an fabricatie = %d\n", t.anFabricatie);
	printf("version = %c\n", t.version);

	scrieClientLaConsola(t.proprietar);
	//linia de mai sus este echivalenta cu
	//printf("nume = %s\n", t.proprieta.nume);
	//printf("varsta = %d\n", t.proprieta.varsta);

	printf("\n\n");
}

void citireTelefonDeLaConsola(telefon& t) {
	//todo week 3
	printf("culoare telefon = ");

	printf("marca = ");

	printf("pret = ");
	scanf("%lf", t.pret);

	printf("an fabricatie = ");
	scanf("%d", t.anFabricatie);

	printf("version = ");
	scanf("%c", t.version);

	citireClientDeLaConsola(t.proprietar);
}
void main() {
	/// <summary>
	/// pentru a declara pe stack un sir de caractere poti scrie asa: char aux[100];
	/// aux reprezinta de fapt adresa primului element din sir ( aux[0] )
	/// strcpy(aux, "Rares");
	/// 
	/// de tinut minte ca un sir de caractere se comporta ca un pointer
	/// </summary>


	printf("%s\n", transformaEnumInSirDeCaractere(ROZ));
	printf("%d\n", transformaSirDeCaractereInEnum("negru"));

	client c1;
	c1.varsta = 20;
	strcpy(c1.nume, "Ion Popescu");


	user u1;
	u1.varsta = 40;
	printf("varsta = %d\n", u1.varsta);
	u1.gen = 'Z';
	printf("gen = %c\n", u1.gen);
	printf("varsta = %d\n", u1.varsta);


	client c2, c3;
	c2.varsta = 30;
	strcpy(c2.nume, "Ana Popescu");


	printf("\n\n---CITIRE DE LA CONSOLA---\n\n");
	citireClientDeLaConsola(c3);

	printf("\n\n---SCRIERE LA CONSOLA---\n\n");
	scrieClientLaConsola(c1);
	scrieClientLaConsola(c2);
	scrieClientLaConsola(c3);

	// scriere in fisiere
	//w-creare fisier si scriere in el, daca exista fisierul exista se sterg toate informatiile din el
	//wb-este "w" in mod binar
	//r-citire din fisier, daca fisierul nu exista se intoarce NULL la fopen()
	//rb-este "r" in mod binar, daca fisierul nu exista se intoarce NULL la fopen()
	//a-adaugare informatii la sf fisierului, daca NU exista fisierul se face unul nou
	//ab- este "a" in mod binar
	//r+ sau rb+ - fisier deschis pentru citire si scriere/ citire si scriere in mod binar, daca fisierul nu exista se intoarce NULL la fopen()
	//w+ sau wb+ - fisier deschis pentru citire si scriere in mod binar. 
	//a+ si ab+ - fisier deschis pentru citire si adaugare la final



	printf("\n\n---SCRIERE CLIENT IN FISIER TEXT---\n\n");

	FILE* fisierClienti = fopen("clienti.txt", "w");
	if (fisierClienti == NULL) {
		printf("Eroare: Fisierul clienti.txt nu poate fi deschis pentru scriere");
		exit(20);
	}

	scrieClientInFisier(fisierClienti, c1);
	scrieClientInFisier(fisierClienti, c2);
	scrieClientInFisier(fisierClienti, c3);

	fclose(fisierClienti);


	printf("\n\n---CITIRE CLIENT DIN FISIER TEXT---\n\n");

	fisierClienti = fopen("clienti.txt", "r");
	if (fisierClienti == NULL) {
		printf("Eroare: Fisierul clienti.txt nu poate fi deschis pentru citire");
		exit(25);
	}


	client c4, c5, c6;
	citireClientDinFisier(fisierClienti, c4);
	citireClientDinFisier(fisierClienti, c5);
	citireClientDinFisier(fisierClienti, c6);

	scrieClientLaConsola(c4);
	scrieClientLaConsola(c5);
	scrieClientLaConsola(c6);

	fclose(fisierClienti);

	printf("\n\n---CITIRE TELEFON DE LA CONSOLA---\n\n");
	//citireTelefonDeLaConsola(t3);

	telefon t1, t2, t3;
	t1.anFabricatie = 2021;
	t2.anFabricatie = 2022;

	t1.culoareTelefon = NEGRU;
	t2.culoareTelefon = VERDE;

	t1.pret = 1999.99;
	t2.pret = 2599.99;

	t1.proprietar = c1;
	t2.proprietar = c2;

	t1.version = 'Z';
	t2.version = '9';

	//pt a declara un sir de caractere pe heap trebuie sa:
	//1) aloci memorie pentru acel sir
	t1.marca = (char*)malloc(strlen("Apple") + 1); //unde +1 reprezinta sf de sir de caractere adica \0
	//2) copiezi acel sir in zona de memorie alocata mai sus
	strcpy(t1.marca, "Apple");

	t2.marca = (char*)malloc(strlen("Huawei") + 1);
	strcpy(t2.marca, "Huawei");


	printf("\n\n---SCRIERE TELEFON LA CONSOLA---\n\n");

	scrieTelefonLaConsola(t1);
	scrieTelefonLaConsola(t2);
	//scrieTelefonLaConsola(t3);
	
}