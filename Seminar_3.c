#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

//deasupra - apelam
struct Aeroport* adaugareAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune) {
	//intai scrie dereferntierea *dimensiune +1
	//nu invers - + are prioritate
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * (*(dimensiune)+1));

	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}

	//e shallow copy - e ok
	//il lasam asa - nu mai facem stergerea dupa
	copie[*(dimensiune)] = aeroport;

	(*dimensiune)++;

	//SA NU UITI SA STERGI!!!!
	//pt ca am facut shallow copy
	//stergem tot vectorul deodata
	//daca era deep copy - trebuiau dezalocate si partile
	if (vector != NULL) {
		for (int i = 0; i < ((*dimensiune) - 1); i++) {
			free(vector);
		}
	}
	
	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL; //sa nu l lasam dangling
	FILE* f = fopen(numeFisier, "r");
	//verificam daca a fost deschis cu succes
	if (f != NULL) {
		(*nrAeroporturi) = 0;
		char buffer[100];
		//OBS buffer e deja un pointer!!!
		//fgets returneaza adresa catre ceea ce a citit
		//ret null cand ajunge la finalul fisierului

		//vector de doua delimitatoare!! new line si virgula
		char delimitator[] = ",\n";
		/*
		The C library function char *fgets(char *str, int n, FILE *stream) reads a line from the specified 
		stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, 
		the newline character is read, or the end-of-file is reached, whichever comes first.*/
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			//separa dupa virgula SAU newline!!!
			// echivalent strtok(buffer, ",\n");

			/*
			The first time strtok is called, it expects the string to tokenize (str) as 
			its first parameter. On subsequent calls, it expects NULL as the first parameter, 
			indicating that it should continue tokenizing the same string.
			*/
			char* token = strtok(buffer, delimitator);
			//parseuim sa fie int
			//atoi conversie ascii to int
			//atol concersie ascii to long
			//etc
			aeroport.id = atoi(token);
			//vedem unde apelul lui strtok a ramas in buffer
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);
			vectorAeroporturi = adaugareAeroport(vectorAeroporturi, aeroport, nrAeroporturi); //nu cu & pt ca e deja pointer in par functiei
		}
		//inchidem fisierul
		fclose(f);
	}
	else {
		printf("Fisierul nu a fost deschis");
	}
	return vectorAeroporturi;
}

//trimitere pointer Aeroport*
//accesare prin -> deref
//altfel e cu .
void afisareAeroport(struct Aeroport a) {
	printf("Aeroportul cu id: %d, nume: %s, nr terminale: %d\n", a.id, a.nume, a.nrTerminale);
}

void afisareVector(struct Aeroport* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		afisareAeroport(vector[i]);
	}
}

void dezalocare(struct Aeroport** vector, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*vector)[i].nume);
	}
	free(*vector);
	(*vector) = NULL;
	*dim = 0;
}


int main() {
	int dimensiune = 2;
	
	//vectorul acum e null
	//dar dimensiunea e data totusi
	//si intra in primul for - intr un vector null sau v[0] nu se poate
	//deci punem asta
	//(*nrAeroporturi) = 0;

	struct Aeroport* aeroporturi = NULL;
	aeroporturi=citireFisier("fisier.txt", &dimensiune);
	afisareVector(aeroporturi, dimensiune);
	dezalocare(&aeroporturi, &dimensiune);
	return 0;
}
