#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//Se doreste gestiunea cladirilor din Bucuresti in funtie de anul construirii.Acest lucru va ajuta 
// la stabilire riscului seismic al acestora.

//1. Sa se creeze o tabela de dispersie pentru stocarea cladirilor din Bucuresti(structura Cladire contine 
// ce atribute vreti voi dar va contine obligatoriu anul construirii si un id unic).campul folosit pentru 
// clusterizare este anul construirii cladirii.

//2. Implementati o functie care afiseaza cladirile dintr - un cluster(construite intr - un an primit ca parametru).

//3. Implementati o functie care sterge o cladire pentru care se primeste id - ul si anul construirii.
//4. Implementati o functie care sterge o cladire pentru care se primeste doar id - ul cladirii.

//5. Observatii diferenta dintre functia implementata la 4 si functia de la 5.

//6. Implementati o functie care salveaza intr - un vector toate  cladirile dintr - un an primit ca parametru.
// Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele din tabela de dispersie.
// Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.

//7. Implementati o functie care modifica anul construirii unei cladiri identificate prin ID.Functia primeste ca 
// parametri : id - ul cladirii, vechiul an de constructie si noul an de constructie.Aveti grija se modifica valoarea 
// atributului folosit pentru clusterizare.

typedef struct Cladire Cladire;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Cladire {
	int an;
	int id;
	char* nume;
};

struct Nod {
	Cladire cladire;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dimensiune;
};

Cladire initializareCladire(int an, int id, const char* nume) {
	Cladire c;
	c.an = an;
	c.id = id;
	c.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(c.nume, nume);
	return c;
}

HashTable initializareHashTable(int dimensiune) {
	HashTable table;
	table.dimensiune = dimensiune;
	table.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		table.vector[i] = NULL;
	}
	return table;
}

void inserareLaFinalDeLista(Nod** cap, Cladire c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->cladire = c;
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

int calculHash(int an, int dimensiune) {
	if (dimensiune > 0) {
		return an % dimensiune;
	}
	return -1;
}

void inserareCladireInHashTable(Cladire c, HashTable table) {
	int poz = calculHash(c.an, table.dimensiune);
	if (poz >= 0 && poz < table.dimensiune) {
		if (table.vector[poz] != NULL) {
			inserareLaFinalDeLista(&(table.vector[poz]), c);
		}
		else {
			inserareLaFinalDeLista(&(table.vector[poz]), c);
		}
	}
}

void afisareCladire(Cladire c) {
	printf("Cladirea %s, construita in anul %d, id %d", c.nume, c.an, c.id);
}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		afisareCladire(cap->cladire);
		printf("\n");
		cap = cap->next;
	}
}

void afisareHashTable(HashTable table) {
	for (int i = 0; i < table.dimensiune; i++) {
		if (table.vector[i] != NULL) {
			printf("Cladirile din clusterul %d:\n", (i + 1));
			afisareLista(table.vector[i]);
		}
	}
}

//2
void afisareCladiriDinCluster(HashTable table, int cluster) {
	if (table.vector[cluster - 1] != NULL) {
		afisareLista(table.vector[cluster-1]);
	}
	else {
		printf("In acest cluster nu sunt cladiri!");
	}
}

void stergereCladireIdAnDinLista(Nod** cap, int id, int an) {
	Nod* deSters = NULL;
	//se sterge primul element
	if ((*cap) != NULL && (*cap)->cladire.an == an && (*cap)->cladire.id == id) {
		deSters = (*cap);
		(*cap) = (*cap)->next;
	}
	else {
		Nod* aux = (*cap);
		//aici trebuie LOGICA ASA
		while (aux->next != NULL) {
			if (aux->next->cladire.an == an && aux->next->cladire.id == id) {
				break;
			}
			aux = aux->next;
		}
		if (aux->next != NULL) {
			deSters = aux->next;
			aux->next = aux->next->next;

		}
	}
	if (deSters != NULL) {
		free(deSters->cladire.nume);
		free(deSters);
	}
	else {
		printf("Nu exista o cladire cu id-ul si anul specificat!");
	}
}

void stergereDupaIdLista(Nod** cap, int id) {
	Nod* deSters = NULL;
	if ((*cap)->cladire.id == id) {
		deSters = (*cap);
		(*cap) = (*cap)->next;
	}
	else {
		Nod* aux = (*cap);
		while (aux->next != NULL && aux->next->cladire.id!=id) {
			aux = aux->next;
		}
		if (aux->next != NULL) {
			deSters = aux->next;
			aux->next = aux->next->next;
		}
	}

	if (deSters != NULL) {
		free(deSters->cladire.nume);
		free(deSters);
	}
}

//3
void stergereCladireDupaIdSiAn(HashTable table, int an, int id) {
	int poz = calculHash(an, table.dimensiune);
	if (poz >= 0 && poz < table.dimensiune) {
		if (table.vector[poz] != NULL) {
			stergereCladireIdAnDinLista(&(table.vector[poz]), id, an);
		}
		else {
			printf("Nu exista o cladire cu id-ul si anul specificat!");
		}
	}
}

//4
void stergeCladireDupaId(HashTable table, int id) {
	//nu putem sa ne dam seama in ce lista suntem (clusterizarea s-a facut dupa an) deci trebuie parcurse toate
	for (int i = 0; i < table.dimensiune; i++) {
		if (table.vector[i] != NULL) {
			stergereDupaIdLista(&(table.vector[i]), id);
		}
	}
}

//6

void salveazaVectorAnLista(Nod* cap, Cladire** vector, int an, int* dim) {
	int q = 0;
	Nod* aux = cap;
	while (aux != NULL) {
		if (aux->cladire.an == an) {
			q++;
		}
		aux = aux->next;
	}
	(*dim) = q;
	(*vector) = (Cladire*)malloc(sizeof(Cladire) * q);
	int k = 0;
	aux = cap;
	while (aux != NULL) {
		if (aux->cladire.an == an) {
			(*vector)[k].an = aux->cladire.an;
			(*vector)[k].id = aux->cladire.id;
			(*vector)[k].nume = (char*)malloc(sizeof(char) * (strlen(aux->cladire.nume) + 1));
			strcpy((*vector)[k].nume, aux->cladire.nume);
			k++;
		}
		aux = aux->next;
	}
}

Cladire* salveazaInVectorCladirileDinAn(HashTable table, int an, int* dim) {
	*dim = 0;
	Cladire* vector = NULL;
	int poz = calculHash(an, table.dimensiune);
	//acelasi an => same cluster
	if (poz >= 0 && poz < table.dimensiune) {
		if (table.vector[poz] != NULL) {
			salveazaVectorAnLista(table.vector[poz], &vector, an, dim);
		}
	}
	return vector;
}


//7
void modificareAnIdentificarePrinId(HashTable table, int id, int anNou, int anVechi) {
	int poz1 = calculHash(anVechi, table.dimensiune);
	int poz2 = calculHash(anNou, table.dimensiune);
	if (poz1 >= 0 && poz1 < table.dimensiune) {
		if (table.vector[poz1] != NULL) {
			Nod* aux = table.vector[poz1];
			Cladire c=initializareCladire(-1, -1, "");
			while (aux != NULL) {
				if (aux->cladire.id == id && aux->cladire.an == anVechi) {
					c.an = anNou;
					c.id = id;
					c.nume = (char*)malloc(sizeof(char) * (strlen(aux->cladire.nume) + 1));
					strcpy(c.nume, aux->cladire.nume);
				}
				aux = aux->next;
			}
			if (c.id != -1) {
				inserareCladireInHashTable(c, table);
				stergereCladireDupaIdSiAn(table, anVechi, id);
			}
			else {
				printf("Nu exista astfel de cladiri. Lista ramane neschimbata!");
			}
		}
		else {
			printf("Nu exista cladiri construite in anul %d ", anVechi);
		}
	}
}

void dezalocareLista(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->cladire.nume);
		Nod* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux);
	}
	(*cap) = NULL;
}

void dezalocareHashTable(HashTable* table) {
	for (int i = 0; i <(*table).dimensiune; i++) {
		if ((*table).vector[i] != NULL) {
			dezalocareLista(&((*table).vector[i]));
		}
	}
	*((*table).vector) = NULL;
	(*table).dimensiune = 0;
}

int main() {
	Cladire c1 = initializareCladire(1989, 1, "Securisti");
	Cladire c2 = initializareCladire(1991, 2, "Rev2");
	Cladire c3 = initializareCladire(2000, 3, "Nou");
	Cladire c4 = initializareCladire(1970, 4, "Bulina");
	Cladire c5 = initializareCladire(1970, 5, "Airbnb");
	HashTable table = initializareHashTable(5);
	inserareCladireInHashTable(c1, table);
	inserareCladireInHashTable(c2, table);
	inserareCladireInHashTable(c3, table);
	inserareCladireInHashTable(c4, table);
	inserareCladireInHashTable(c5, table);
	printf("Tabela arata astfel:\n");
	afisareHashTable(table);
	printf("\n--------------\n");
	int cluster = 2;
	printf("Clusterul cu numarul %d:\n", cluster);
	afisareCladiriDinCluster(table, cluster);
	printf("\n--------------\n");


	int id = 8;
	int an = 1970;
	printf("Se sterge cladirea cu id %d construita in anul %d.\n", id, an);
	stergereCladireDupaIdSiAn(table, an, id);
	printf("Acum tabela arata astfel:\n");
	afisareHashTable(table);
	printf("\n--------------\n");

	id = 1;
	printf("Se sterge cladirea cu id %d.\n", id);
	stergeCladireDupaId(table, id);
	printf("Acum tabela arata astfel:\n");
	afisareHashTable(table);
	printf("\n--------------\n");

	//6
	printf("Se salveaza intr-un vector toate cladirile construite in anul %d.\n Acesta este rezultatul:\n", an);
	Cladire* vector = NULL;
	int dim = 0;
	vector = salveazaInVectorCladirileDinAn(table, an, &dim);
	for (int i = 0; i < dim; i++) {
		afisareCladire(vector[i]);
		printf("\n");
	}
	printf("\n--------------\n");


	//7
	id = 4;
	int anVechi = 1970;
	int anNou = 2007;
	printf("Se modifica anul cladirii cu id %d. Acesta se modifica de la %d la %d.\n Rezultatul este: ", id, anVechi, anNou);
	modificareAnIdentificarePrinId(table, id, anNou, anVechi);
	afisareHashTable(table);

	dezalocareHashTable(&table);
	printf("%d", table.dimensiune);

	return 0;
}
