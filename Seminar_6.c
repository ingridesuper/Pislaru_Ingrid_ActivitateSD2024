#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;
};

struct Nod {
	Biblioteca info:
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* head;
	Nod* tail;
};


Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
	Biblioteca biblioteca;
	biblioteca.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(biblioteca.nume, nume);
	biblioteca.nrCarti = nrCarti;
	biblioteca.nrCititori = nrCititori;
	return biblioteca;
}

void inserareInceput(ListaDubla* lista, Biblioteca b) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	//data trecuta am avut deep copy - acum facem shallow
	nod->info = b;
	nod->next = lista->head;
	nod->prev = NULL;
	if (lista->head != NULL) {
		lista->head->prev = nod;
		lista->head = nod;
	}
	else {
		lista->head = nod;
		lista->tail = nod;
	}
}

void afisareListaDeLaInceput(ListaDubla lista) {
	while (lista.head) {
		printf("Biblioteca: %s, %d nr cititori, %d nr carti\n", lista.head->info.nume, lista.head->info.nrCarti, lista.head->info.nrCititori);
		lista.head = lista.head->next;
	}
	printf("\n");
}

//poate fi primul, ultimul, singurul, sau intermediar
void stergeNodDupaNume(ListaDubla* lista, const char* nume) {
	Nod* aux = lista->head;
	while (aux && strcmp(nume, aux->info.nume)!=0) {
		aux = aux->next;
	}
	if (aux) {
		if (aux == lista->head) {
			if (aux == lista->tail) { //e unicul
				lista->head = NULL;
				lista->tail = NULL;
			}
			else { //primul
				lista->head = lista->head->next;
				lista->head->prev = NULL;
			}
		}
		else if (aux==lista->tail){ //ultimul
			aux->prev->next = NULL;
			lista->tail = aux->prev;
		}
		else {
			aux->next->prev = aux->prev;
			aux->prev->next = aux->next;
			//nu mai setam - oricum stergem aux
		}

		free(aux->info->nume);
		free(aux);
	}
}

void stergeLista(ListaDubla* lista) {
	while (lista->head) {
		free(lista->head->info.nume);
		//ceva
	}
	//ceva
}

int main() {

	Biblioteca b1 = initializare("Nora Iuga", 1200, 200);
	Biblioteca b2 = initializare("Nina Cassian", 500, 100);
	Biblioteca b3 = initializare("Medeea Iancu", 2093, 1000);
	ListaDubla listaDubla;
	listaDubla.head = NULL;
	listaDubla.tail = NULL;
	inserareInceput(&listaDubla, b1);
	inserareInceput(&listaDubla, b2);
	inserareInceput(&listaDubla, b3);
	afisareListaDeLaInceput(listaDubla);
	stergeNodDupaNume(&listaDubla, "Nina Cassian");
	afisareListaDeLaInceput(listaDubla);
	stergeNodDupaNume(&listaDubla, "Nora Iuga");
	afisareListaDeLaInceput(listaDubla);
	stergeNodDupaNume(&listaDubla, "Medeea Iancu");
	afisareListaDeLaInceput(listaDubla);
}
