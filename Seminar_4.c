#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

//de corectat ceva aici
struct Aeroport* adaugareAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune) {

	struct Aeroport* copie = (struct Aeroport*)malloc((*(dimensiune)+1) *sizeof(struct Aeroport));
	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}
	
	copie[*(dimensiune)] = aeroport;

	(*dimensiune)++;

	//nu merge daca am instructiunea asta
	//de ce?
	/*
	if (vector != NULL) {
		for (int i = 0; i < ((*dimensiune) - 1); i++) {
			free(vector);
		}
	}
	*/

	return copie;
}


void citireMatrice(const char* numeFisier, int* nrAeroporturiLinie, int nrClustere, struct Aeroport** aeroporturi) {
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		char buffer[100];
		char delimitator[] = ",\n";
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);
			int poz = aeroport.nrTerminale % 2;
			aeroporturi[poz] = adaugareAeroport(aeroporturi[poz], aeroport, &(nrAeroporturiLinie[poz])); 
		}
		//inchidem fisierul
		fclose(f);
	}
	else {
		printf("Fisierul nu a fost deschis");
	}
}


void afisareAeroport(struct Aeroport a) {
	printf("ID: %d. %s are %d terminale.", a.id, a.nume, a.nrTerminale);
}

void afisareMatrice(struct Aeroport** matrice, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareAeroport(matrice[i][j]);
			printf("   ");
		}
		printf("\n");
	}
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

//nr mediu de terminale 
//pt aeroporturile cu nr par/impar de terminale
int mediaTerminale(struct Aeroport** aeroporturi, int* nrAeroporturiLinie, int paritate) {
	//in caz ca e 0, 1 sau 1,2 sau ...
	paritate = paritate % 2;
	int sum = 0;
	for (int i = 0; i < nrAeroporturiLinie[paritate]; i++) {
		sum += aeroporturi[paritate][i].nrTerminale;
	}
	if (nrAeroporturiLinie[paritate] == 0) return 0;
	return sum / nrAeroporturiLinie[paritate];
}

void dezalocareMatrice(struct Aeroporturi*** aeroporturi, int** nrColoane, int* nrLinii) {
	//ASA
	for (int i = 0; i < (*nrLinii); i++) {
		dezalocare(&((*aeroporturi)[i]), &((*nrColoane)[i]));
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	free(*nrColoane);
	(*nrColoane) = NULL;
	(*nrLinii) = 0;
}

//functie care sa ret aeroport dupa ID
struct Aeroport* cautareAeroportDupaID(struct Aeroport** aeroporturi, int nrLinii, int* nrAeroporturiLinie, int idCautat) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrAeroporturiLinie[i]; j++) {
			if (aeroporturi[i][j].id == idCautat) {
				return &(aeroporturi[i][j]);
			}
		}
	}
	return NULL;
}

int main() {
	//nr par vs impar de terminale
	int nrLinii = 2;
	//o matrice e un vector de vectori
	struct Aeroport** aeroporturi=(struct Aeroport**)malloc(nrLinii*sizeof(struct Aeroport*));
	int* nrColoane = (int*)malloc(nrLinii * sizeof(int));

	//initializam
	for (int i = 0; i < nrLinii; i++) {
		nrColoane[i] = 0;
		//NULL cu litere mari
		aeroporturi[i] = NULL; //intai e vector de null, inainte de vector de vectori
	}
	citireMatrice("fisier.txt", nrColoane, nrLinii, aeroporturi);
	printf("Afisare matrice: \n");
	afisareMatrice(aeroporturi, nrLinii, nrColoane);
	printf("------------------\n");
	printf("Media terminale (pare): %d\n", mediaTerminale(aeroporturi, nrColoane, 0));
	printf("Media terminale (impare): %d\n", mediaTerminale(aeroporturi, nrColoane, 1));
	printf("------------------\n");
	printf("Cautare dupa ID, pentru ID=2: \n");
	if (cautareAeroportDupaID(aeroporturi, nrLinii, nrColoane, 2) != NULL) {
		afisareAeroport(*(cautareAeroportDupaID(aeroporturi, nrLinii, nrColoane, 2)));
	}
	else {
		printf("Nu exista aeroportul cu ID-ul dat!");
	}
	dezalocareMatrice(&aeroporturi, &nrColoane, &nrLinii);
}
