#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Galerie Galerie;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Galerie {
	int cod;
	char* nume;
	float pretIntrare;
};

struct Nod {
	Galerie galerie;
	Nod* next;
};

struct HashTable {
	int dimensiune;
	Nod** vector;
};

//initializare hashtable gol de dimensiune dim
HashTable initializareHashTable(int dimensiune) {
	HashTable table;
	table.dimensiune = dimensiune;
	table.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		table.vector[i] = NULL;
	}
	return table;
}

//initializare galerie
Galerie initializareGalerie(int cod, const char* nume, int pret) {
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(g.nume, nume);
	g.pretIntrare = pret;
	return g;
}


int calculHash(int cod, const char* nume, int dim) {
	if (dim > 0) {
		int poz = cod * strlen(nume);
		return poz % dim;
	}
	return -1;
}

//insereaza galeria la sfarsitul listei simplu inlantuite
void inserareLaFinal(Nod** cap, Galerie g) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->galerie = g;
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = (*cap);
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		(*cap) = nou;
	}
}



//inserare galerie in tabela
void inserareGalerieInTabela(HashTable table, Galerie g) {
	int poz = calculHash(g.cod, g.nume, table.dimensiune);
	if (poz >= 0 && poz < table.dimensiune) {
		if (table.vector[poz] != NULL) {
			inserareLaFinal(&(table.vector[poz]), g);
		}
		else {
			inserareLaFinal(&(table.vector[poz]), g);
		}
	}
}


void afisareGalerie(Galerie g) {
	printf("Cod %d, nume %s, pret %d ", g.cod, g.nume, g.pretIntrare);
}


void afisareListaGalerii(Nod* cap) {
	while (cap != NULL) {
		afisareGalerie(cap->galerie);
		printf("\n");
		cap = cap->next;
	}
}


void afisareTabela(HashTable table) {
	for (int i = 0; i < table.dimensiune; i++) {
		if (table.vector[i] != NULL) {
			printf("Cluster %d\n", (i + 1));
			afisareListaGalerii(table.vector[i]);
		}
	}
}


Galerie cautaGalerieDupaCheie(int cod, const char* nume, HashTable table) {
	int poz = calculHash(cod, nume, table.dimensiune);
	if (poz >= 0 && poz < table.dimensiune) {
		Nod* aux = table.vector[poz];
		while (aux != NULL && aux->galerie.cod != cod && strcmp(aux->galerie.nume, nume) != 0) {
			aux = aux->next;
		}
		if (aux != NULL) {
			return aux->galerie;
		}
		else {
			return initializareGalerie(-1, "", -1);
		}
	}
	else {
		return initializareGalerie(-1, "", -1);
	}
}


void main()
{
	Galerie g1 = initializareGalerie(1, "Orizont", 10);
	Galerie g2 = initializareGalerie(2, "Cercul armatei", 6);
	Galerie g3 = initializareGalerie(3, "Louvre", 30);
	Galerie g4 = initializareGalerie(4, "Antipa", 20);
	Galerie g5 = initializareGalerie(5, "Istorie", 15);
	Galerie g6 = initializareGalerie(6, "Geologie", 17);

	HashTable tabela = initializareHashTable(5);

	//Shallow copy
	inserareGalerieInTabela(tabela, g1);
	inserareGalerieInTabela(tabela, g2);
	inserareGalerieInTabela(tabela, g3);
	inserareGalerieInTabela(tabela, g4);
	inserareGalerieInTabela(tabela, g5);
	inserareGalerieInTabela(tabela, g6);

	afisareTabela(tabela);
	printf("cautare:\n");
	Galerie g10 = cautaGalerieDupaCheie(4, "Antipa", tabela);
	afisareGalerie(g10);
	printf("\n");
	Galerie g11 = cautaGalerieDupaCheie(1, "Orizont", tabela);
	afisareGalerie(g11);

}
