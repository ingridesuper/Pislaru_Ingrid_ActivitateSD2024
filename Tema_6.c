//Obiectele pe care le cititi dintr - un fisier text le salvati intr - o lista dublu inlantuita.
//1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru.Daca lista are mai 
// putine noduri decat index - ul dat, nu se realizeaza stergerea;
//
//2. Implementati o functie care sa insereze elementele in cadrul listei dublu inlantuite astfel
//  incat acestea a fie sortate crescator dupa un camp la alegerea voastra;
//
//3. Realizati parcurgerile pentru lista dublu inlantuita, astfel incat sa afiseze elementele sortate
// 
//  crescator dar si sortate descrescator;
//
//4. Implementati o functie care salveaza intr - o lista simplu inlantuita toate obiectele care indeplinesc o conditie stabilita de voi.
// Realizati deep copy, astfel incat elementele din lista simplu inlantuita sa fie diferite de cele din lista dublu inlantuita.
// Observati diferenta dintre utilizarea de lista inlantuita si vector(task - ul precedent);
//
//5. Implementati o functie care primeste lista dublu inlantuita si doua pozitii.In cadrul functiei trebuie 
// sa interschimbati elementele de pe cele doua pozitii din lista primita.Interschimbati informatiile utile din cele doua noduri.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;
typedef struct NodSimplu NodSimplu;

struct Biblioteca {
	char* nume;
	int carti;
};

struct Nod {
	Nod* prev;
	Nod* next;
	Biblioteca biblioteca;
};

struct ListaDubla {
	Nod* head;
	Nod* tail;
};

struct NodSimplu {
	Biblioteca biblioteca;
	NodSimplu* next;
};

void inserareFinal(ListaDubla* lista, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->biblioteca = b;
	nou->next = NULL;
	if (lista->head != NULL) {
		nou->prev = lista->tail;
		lista->tail->next = nou;
	}
	else {
		nou->prev = NULL;
		lista->head = nou;
	}
	lista->tail = nou;
}

//2
void inserareCrescatoareDupaCarti(ListaDubla* lista, Biblioteca b) {
	if (lista->head == NULL && lista->tail == NULL) {
		inserareFinal(lista, b);
	}
	else {
		Nod* nou=(Nod*)malloc(sizeof(Nod));
		nou->biblioteca = b;
		Nod* aux = lista->head;
		while (aux != NULL && aux->biblioteca.carti < b.carti) {
			aux = aux->next;
		}
		if (aux == lista->head) {
			nou->next = lista->head;
			nou->prev = NULL;
			lista->head->prev = nou;
			lista->head = nou;
		}
		else if (aux == NULL) {
			nou->prev = lista->tail;
			nou->next = NULL;
			lista->tail->next = nou;
			lista->tail = nou;
		}
		else {
			//tb adaugat inaintea lui aux
			nou->next = aux;
			nou->prev = aux->prev;
			aux->prev = nou;
			aux->prev->next = nou;
		}
	}
}



void citesteFisier(const char* numeFisier, ListaDubla* lista) {
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		char buffer[100];
		char del[] = ",\n";
		char* token;
		while (fgets(buffer, 100, f)) {
			Biblioteca b;
			token = strtok(buffer, del);
			b.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(b.nume, token);
			token = strtok(NULL, del);
			b.carti = atoi(token);
			//inserareFinal(lista, b);
			inserareCrescatoareDupaCarti(lista, b);
		}
		fclose(f);
	}
}

//3
void afisareListaInceput(ListaDubla lista) {
	while (lista.head != NULL) {
		printf("%s, %d carti\n", lista.head->biblioteca.nume, lista.head->biblioteca.carti);
		lista.head = lista.head->next;
	}
}

void afisareListaFinal(ListaDubla lista) {
	while (lista.tail != NULL) {
		printf("%s, %d carti\n", lista.tail->biblioteca.nume, lista.tail->biblioteca.carti);
		lista.tail = lista.tail->prev;
	}
}

///1
void stergeNodPozitieK(ListaDubla* lista, int k) {
	Nod* aux = lista->head;
	int i = 0;
	while (aux != NULL && i < k) {
		aux = aux->next;
		i++;
	}
	//il sterg pe primul, ultimul, unicul, sau altul
	if (aux != NULL) {
		if (aux == lista->head && aux == lista->tail) {
			lista->head = NULL;
			lista->tail = NULL;
		}
		else if (aux==lista->head){
			lista->head->next->prev = NULL;
			lista->head = lista->head->next;
		}

		else if (aux == lista->tail) {
			lista->tail->prev->next = NULL;
			lista->tail = lista->tail->prev;
		}

		else {
			aux->prev->next = aux->next;
			aux->next->prev = aux->prev;
		}

		free(aux->biblioteca.nume);
		free(aux);
	}
}

//4

void inserareListaSimplaFinal(Nod** cap, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->biblioteca.nume = (char*)malloc(sizeof(char)*(strlen(b.nume)+1));
	strcpy(nou->biblioteca.nume, b.nume);
	nou->biblioteca.carti = b.carti;
	nou->next = NULL;
	Nod* aux = (*cap);
	if ((*cap) != NULL) {
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	} else{
		(*cap) = nou;
	}
}


NodSimplu* salvareListaSimplaPestePrag(ListaDubla lista, int prag) {
	Nod* cap = NULL;
	while (lista.head != NULL) {
		if (lista.head->biblioteca.carti >= prag) {
			inserareListaSimplaFinal(&cap, lista.head->biblioteca);
		}
		lista.head = lista.head->next;
	}
	return cap;
}

void afisareListaSimpla(Nod* cap) {
	while (cap != NULL) {
		printf("%s, %d carti\n", cap->biblioteca.nume, cap->biblioteca.carti);
		cap = cap->next;
	}
}

//5
void interschimbarePozitiiListaDubla(ListaDubla* lista, int poz1, int poz2) {
	Nod* aux1 = NULL;
	Nod* aux2 = NULL;
	Nod* tmp = lista->head;
	int i = 0;
	while (tmp != NULL) {
		if (i == poz1) {
			aux1 = tmp;
		}
		if (i == poz2) {
			aux2 = tmp;
		}
		tmp = tmp->next;
		i++;
	}
	Biblioteca baux = aux1->biblioteca;
	aux1->biblioteca = aux2->biblioteca;
	aux2->biblioteca = baux;
}


int main() {
	ListaDubla lista;
	lista.head = NULL;
	lista.tail = NULL;
	citesteFisier("biblioteci.txt", &lista);
	afisareListaInceput(lista);
	printf("\n------------------\n");
	afisareListaFinal(lista);
	printf("\n------------------\n");
	//stergeNodPozitieK(&lista, 3);
	//afisareListaInceput(lista);
	/*ListaDubla lista2;
	lista2.head = NULL;
	lista2.tail = NULL;
	Biblioteca b;
	b.carti = 100;
	b.nume = (char*)malloc(sizeof(char) * (strlen("nichita stanescu") + 1));
	strcpy(b.nume, "nichita stanescu");
	inserareFinal(&lista2, b);*/
	/*printf("\n------------------\n");
	afisareListaInceput(lista2);
	stergeNodPozitieK(&lista2, 0);
	printf("\n------------------\n");
	afisareListaInceput(lista2);*/
	/*NodSimplu* cap = NULL;
	cap = salvareListaSimplaPestePrag(lista, 1800);
	afisareListaSimpla(cap);*/
	interschimbarePozitiiListaDubla(&lista, 0, 2);
	afisareListaInceput(lista);
	return 0;
}
