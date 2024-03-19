#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;
};

struct Nod {
	Biblioteca info;
	Nod* next;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
	Biblioteca biblioteca;
	biblioteca.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(biblioteca.nume, nume);
	biblioteca.nrCarti = nrCarti;
	biblioteca.nrCititori = nrCititori;
	return biblioteca;
}

//ret noul cap al listei
Nod* inserareInceput(Nod* cap, Biblioteca b) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	//nodNou->info = b; e shallow
	//deep:
	nod->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	nod->next = cap; //nu tb exceptie pt cap null, merge si asa
	return nod;
}

//nu transmitem prin adresa, deci nu avem nevoie de aux
void afisareLista(Nod* cap) {
	while (cap != NULL) {
		printf("Biblioteca %s are %d de carti si %d de cititori.\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
		cap = cap->next;
	}
}

char* celeMaiMulteCartiPerCititor(Nod* cap) {
	double medie = 0;
	char* nume_aux = NULL;
	while (cap != NULL) {
		if ((cap->info.nrCarti / cap->info.nrCititori) > medie) {
			medie = (cap->info.nrCarti / cap->info.nrCititori);
			nume_aux = cap->info.nume;
		}
		cap = cap->next;
	}
	
	//vrem deep
	char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
	strcpy(nume, nume_aux);
	return nume;
}

void stergeLista(Nod** cap) {
	while (*cap != NULL) {
		free((*cap)->info.nume);
		//ne tb copie pt ca altfel nu mai avem cum sa facem next
		Nod* copie = (*cap);
		(*cap) = (*cap)->next;
		free(copie);
	}
}

//daca transmitem ** aka se modifica
//ne tb neaparat auxiliat
void inserareLaSfarsit(Nod** cap, Biblioteca b) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	nod->next = NULL;	
	if ((*cap) != NULL) {
		Nod* aux = (*cap);
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nod;
	}
	else {
		(*cap) = nod;
	}
}

int main() {
	Nod* cap = NULL;
	/* daca faci asa se init de 2 ori
	cap=inserareInceput(cap, initializare("Mihai Emi", 1200, 200));
	cap=inserareInceput(cap, initializare("I. Slavici", 500, 100));
	cap = inserareInceput(cap, initializare("I L Caragiale", 2093, 1000));
	*/

	Biblioteca b1= initializare("Nora Iuga", 1200, 200);
	Biblioteca b2 = initializare("Nina Cassian", 500, 100);
	Biblioteca b3 = initializare("Medeea Iancu", 2093, 1000);
	Biblioteca b4 = initializare("Sofia Nadejde", 20930, 600);

	cap = inserareInceput(cap, b1);
	cap = inserareInceput(cap, b2);
	cap = inserareInceput(cap, b3);
	afisareLista(cap);

	//trebuie obligatoriu dezalocat
	char* numeDeAfisat = celeMaiMulteCartiPerCititor(cap);
	printf("Bibl cu med maxima: %s\n", numeDeAfisat);
	free(numeDeAfisat);
	
	inserareLaSfarsit(&cap, b4);

	afisareLista(cap);
	stergeLista(&cap);
	//bibl sunt aloc de 2 ori - deep copy - tb dez si aici!!
	free(b1.nume);
	free(b2.nume);
	free(b3.nume);
	free(b4.nume);
	afisareLista(cap);
}
