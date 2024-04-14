//1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru.Daca lista are mai putine noduri 
//decat index - ul dat, nu se realizeaza stergerea.
//
//2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel incat acestea a fie
//sortate crescator dupa un camp la alegerea voastra.
//
//3. Implementati o functie care salveaza intr - un vector toate obiectele care indeplinesc o conditie stabilita de 
//voi.Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele din lista.
//Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.
//
//4. Implementati o functie care primeste lista si doua pozitii.In cadrul functiei trebuie sa interschimbati
//elementele de pe cele doua pozitii din lista primita.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod Nod;
typedef struct Biblioteca Biblioteca;

struct Biblioteca {
	char* nume;
	int carti;
};

struct Nod {
	Biblioteca biblioteca;
	Nod* next;
};

Biblioteca initializare(const char* nume, int carti) {
	Biblioteca b;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.carti = carti;
	return b;
}

//in functie, cap e un Nod*
//deci ca sa se modifice in exterior, trebuie sa fie Nod**!!!
//practic e ca la dezalocare memorie vector!!




Nod* inserareInceput(Nod* cap, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->biblioteca = initializare(b.nume, b.carti);
	nou->next = cap;
	return nou;
}

void inserareInceput2(Nod** cap, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->biblioteca = initializare(b.nume, b.carti);
	nou->next = (*cap);
	(*cap) = nou;
}

void inserareFinal(Nod** cap, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->biblioteca = initializare(b.nume, b.carti);
	nou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		Nod* aux = (*cap);
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

Nod* inserareFinal2(Nod* cap, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->biblioteca = initializare(b.nume, b.carti);
	if (cap == NULL) {
		cap = nou;
	}
	else {
		Nod* copie = cap;
		while (copie->next != NULL) {
			copie = copie->next;
		}
		copie->next = nou;
	}
	return cap; //acum cap e altceva!!!
}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		printf("%s, %d\n", cap->biblioteca.nume, cap->biblioteca.carti);
		cap = cap->next;
	}
}

void stergeNodPozitie(Nod** cap, int poz) {
	Nod* aux = NULL;
	int i = 1;
	if (poz == 1) {
		aux = (*cap);
		(*cap) = (*cap)->next;
	}
	else if (poz > 1) {
		Nod* tmp = (*cap);
		while (tmp != NULL && i < poz - 1) {
			tmp = tmp->next;
			i++;
		}
		if (tmp != NULL && tmp->next != NULL) {
			aux = tmp->next; //urmatorul este cel ce tb sters
			tmp->next = aux->next; //chiar daca e ultimul => NULL (e bine)
		}
	}
	//NODUL TREBUIE ELLLIBERAT LA FINAL!!!
	//S A STERS CEVA => ELIBERARE
	if (aux != NULL) {
		free(aux->biblioteca.nume);
		free(aux);
	}
}




void sortareDupaCarti(Nod** cap) {
	Nod* p1 = *cap;
	Nod* p2 = NULL;
	while (p1 != NULL) {
		p2 = p1->next;
		while (p2 != NULL) {
			if (p1->biblioteca.carti > p2->biblioteca.carti) {
				//BIBLIOTECA, NU SI NEXT
				Biblioteca tmp = p1->biblioteca;
				p1->biblioteca = p2->biblioteca;
				p2->biblioteca = tmp;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}


//de terminat!!!!!!!!!!!
//void inserareSortataDupaCarti(Nod** cap, Biblioteca b) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->biblioteca = initializare(b.nume, b.carti);
//	nou->next = NULL;
//	if ((*cap) == NULL) {
//		(*cap) = nou;
//	}
//	else {
//		int k = 0;
//		Nod* aux = (*cap);
//		while (aux != NULL) {
//			if (aux->biblioteca.carti < b.carti) {
//				aux = aux->next;
//				k++;
//			}
//			else {
//				break;
//			}
//		}
//		if (k == 0) {
//			inserareInceput2(cap, b);
//		}
//		else {
//
//		}
//	}
//}

Biblioteca* vectorCartiPestePrag(Nod* cap, int prag, int* dim) {
	Biblioteca* v = NULL;
	Nod* aux = cap;
	*dim = 0;
	while (aux != NULL) {
		if (aux->biblioteca.carti >= prag) {
			(*dim)++;
		}
		aux = aux->next;
	}
	v = (Biblioteca*)malloc(sizeof(Biblioteca) * (*dim));
	aux = cap;
	int k = 0;
	while (aux != NULL) {
		if (aux->biblioteca.carti >= prag) {
			v[k].carti = aux->biblioteca.carti;
			v[k].nume = (char*)malloc(sizeof(char) * (strlen(aux->biblioteca.nume) + 1));
			strcpy(v[k].nume, aux->biblioteca.nume);
			k++;
		}
		aux = aux->next;
	}
	return v;
}

//presupun ambele pozitii valide
void InterschimbarePozitii(Nod** cap, int k1, int k2) {
	Nod* aux1 = (*cap);
	Nod* aux2 = (*cap);
	int q1 = 0;
	int q2 = 0;
	while (aux1 != NULL && q1!=k1) {
		aux1 = aux1->next;
		q1++;
	}
	while (aux2 != NULL && q2 != k2) {
		aux2 = aux2->next;
		q2++;
	}
	Biblioteca tmp = aux1->biblioteca;
	aux1->biblioteca = aux2->biblioteca;
	aux2->biblioteca = tmp;
}

void stergeLista(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->biblioteca.nume);
		Nod* copie = (*cap);
		(*cap) = (*cap)->next;
		free(copie);
	}
	*cap = NULL;
	//nu ai de ce sa faci free la next, ca e efectiv un nod caruia ii faci free in pasul urmator
}


//altele
void inserareNodPozitieK(Nod** cap, int k, Biblioteca b) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->biblioteca = initializare(b.nume, b.carti);
	if (k == 0) {
		nou->next = (*cap);
		(*cap) = nou;
	}
	else {
		Nod* aux = (*cap);
		int i = 0;
		while (aux != NULL && i < k-1) {
			aux = aux->next;
			i++;
		}
		//verificare validitate pozitie
		if (aux != NULL) {
			nou->next = aux->next;
			aux->next = nou;
		}
	}
}

int calculNoduriLista(Nod* cap) {
	int q = 0;
	while (cap != NULL) {
		q++;
		cap = cap->next;
	}
	return q;
}

//DE CE NU MERGE
Nod* separareListaDupaPozitie(Nod** cap, int poz) {
	Nod* sec = NULL;
	Nod* aux = NULL;
	int i = 0;
	if (poz == 0) {
		sec = (*cap)->next;
		(*cap)->next = NULL;
	}
	else {
		aux = (*cap);
		while (aux != NULL && i < poz) {
			aux = aux->next;
			i++;
		}
	}	
	if (aux != NULL) {
		sec = aux->next; //RESTUL POZ SUNT PRACTIC DEJA AICI
		aux->next = NULL;
	}
	return sec;
}

Nod* concatenareListe(Nod* l1, Nod* l2) {
	Nod* aux = l1;
	while (aux->next != NULL) {
		aux = aux->next;
	}
	aux->next = l2;
	return l1;
}


int main() {
	Biblioteca b1 = initializare("abc", 13);
	Biblioteca b2 = initializare("defgh", 16);
	Biblioteca b3 = initializare("xyz", 20);
	Biblioteca b4 = initializare("nskdnkned", 100);
	Nod* cap1 = NULL;
	cap1=inserareInceput(cap1, b1);
	cap1=inserareInceput(cap1, b2);
	cap1=inserareInceput(cap1, b3);
	cap1=inserareInceput(cap1, b4);
	afisareLista(cap1);
	printf("\n-------------\n");


	Nod* cap3 = NULL;
	inserareInceput2(&cap3, b1);
	inserareInceput2(&cap3, b2);
	inserareInceput2(&cap3, b3);
	inserareInceput2(&cap3, b4);
	afisareLista(cap3);
	printf("\n-------------\n");

	/*
	Nod* cap2 = NULL;
	inserareFinal(&cap2, b1);
	inserareFinal(&cap2, b2);
	inserareFinal(&cap2, b3);
	inserareFinal(&cap2, b4);
	afisareLista(cap2);
	printf("\n-------------\n");

	Nod* cap4 = NULL;
	cap4 = inserareFinal2(cap4, b1);
	cap4 = inserareFinal2(cap4, b2);
	cap4 = inserareFinal2(cap4, b3);
	cap4 = inserareFinal2(cap4, b4);
	afisareLista(cap4);
	printf("\n-------------\n");*/

	/*printf("Sterge nod\n");
	stergeNodPozitieK(&cap1, 3);
	afisareLista(cap1);

	printf("\n-------------\n");
	cap3=stergeNodPozitieK2(cap3, 3);
	afisareLista(cap3);*/

	/*printf("\n-------------\n");
	sortareDupaCarti(&cap1);
	afisareLista(cap1);*/
	
	/*int prag = 15;
	int dim = 0;
	Biblioteca* v = vectorCartiPestePrag(cap1, prag, &dim);
	for (int i = 0; i < dim; i++) {
		printf("%s, %d\n", v[i].nume, v[i].carti);
	}*/

	/*InterschimbarePozitii(&cap1, 0, 3);
	afisareLista(cap1);*/
	Biblioteca b5 = initializare("q", 10);
	
	//printf("%d", calculNoduriLista(cap1));
	/*stergeNodPozitie(&cap1, 6);
	afisareLista(cap1);
	printf("\n-------------\n");
	Nod* sec = separareListaDupaPozitie(&cap1, 2);
	printf("\n-------------\n");
	printf(cap1);
	printf("\n-------------\n");
	printf(sec);*/
	cap1 = concatenareListe(cap1, cap3);
	afisareLista(cap1);
}
