#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Pensiune {
	char* denumire;
	int nrCamere;
	float pretCamera;
	float pretIntretinereCamera;
};

void afisarePensiune(struct Pensiune p) {
	printf("Nume: %s, nr camere: %d, pret camera: %.2f lei/noapte, pret intretinere camera: %.2f lei/noapte\n", p.denumire, p.nrCamere, p.pretCamera, p.pretIntretinereCamera);
}

void afisareVectorPensiuni(struct Pensiune* v, int dim) {
	if (v != NULL && dim > 0) {
		for (int i = 0; i < dim; i++) {
			afisarePensiune(v[i]);
		}
	}
}

struct Pensiune* adaugarePensiune(struct Pensiune* pensiuni, struct Pensiune p, int* dimensiune) {
	struct Pensiune* vector = (struct Pensiune*)malloc(((*dimensiune) + 1) * sizeof(struct Pensiune));
	for (int i = 0; i < (*dimensiune); i++) {
		vector[i].nrCamere = pensiuni[i].nrCamere;
		vector[i].pretCamera = pensiuni[i].pretCamera;
		vector[i].pretIntretinereCamera = pensiuni[i].pretIntretinereCamera;
		vector[i].denumire = (char*)malloc((strlen(pensiuni[i].denumire) + 1) * sizeof(char));
		strcpy(vector[i].denumire, pensiuni[i].denumire);
	}
	vector[(*dimensiune)].nrCamere = p.nrCamere;
	vector[(*dimensiune)].pretCamera = p.pretCamera;
	vector[(*dimensiune)].pretIntretinereCamera = p.pretIntretinereCamera;
	vector[(*dimensiune)].denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(vector[(*dimensiune)].denumire, p.denumire);
	(*dimensiune)++;
	for (int i = 0; i < ((*dimensiune) - 1); i++) {
		free(pensiuni[i].denumire);
	}
	free(pensiuni);
	return vector;
}

struct Pensiune* citireFisier(const char* numeFisier, int* dim) {
	FILE* f = fopen(numeFisier, "r");
	struct Pensiune* pensiuni;
	pensiuni = NULL;
	*dim = 0;
	if (f != NULL) {
		char buffer[100];
		char del[] = " ";
		while (fgets(buffer, 100, f)!=NULL) {
			struct Pensiune p;
			char* token = strtok(buffer, del);
			p.denumire = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(p.denumire, token);
			token = strtok(NULL, del);
			p.nrCamere = atoi(token);
			token = strtok(NULL, del);
			p.pretCamera = atof(token);
			token = strtok(NULL, del);
			p.pretIntretinereCamera = atof(token);
			pensiuni = adaugarePensiune(pensiuni, p, dim);
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu a putut fi deschis.");
	}
	return pensiuni;
}

void scriePensiune(const char* nume, struct Pensiune p) {
	FILE* g = fopen(nume, "w");
	if (g == NULL) {
		printf("Nu s-a putut deschide fisierul!");
		return;
	}
	fprintf(g, "Nume: % s, nr camere : % d, pret camera : % .2f lei / noapte, pret intretinere camera : % .2f lei / noapte\n", p.denumire, p.nrCamere, p.pretCamera, p.pretIntretinereCamera);
	printf("Pensiunea a fost salvata cu succes in fisierul %s\n", nume);
	fclose(g);
}

void scrieVector(const char* nume, struct Pensiune* v, int dim) {
	FILE* g = fopen(nume, "w");
	if (g == NULL) {
		printf("Nu s-a putut deschide fisierul!");
		return;
	}
	if (v != NULL && dim > 0) {
		for (int i = 0; i < dim; i++) {
			//trebuie sa inchizi abia la final, nu sa apelezi functia de mai sus
			//pentru ca asa se inchide de fiecare data
			//si doar suprascrie prima linie
			fprintf(g, "Nume: % s, nr camere : % d, pret camera : % .2f lei / noapte, pret intretinere camera : % .2f lei / noapte\n", v[i].denumire, v[i].nrCamere, v[i].pretCamera, v[i].pretIntretinereCamera);
		}
	}
	printf("Pensiunile au fost salvate cu succes!");
	fclose(g);
}

int main() {
	int nr = 2;
	//afisare proasta - la floats
	printf("Partea 1\n");
	struct Pensiune* pensiuni = citireFisier("pensiuniIn.txt", &nr);
	afisareVectorPensiuni(pensiuni, nr);

	printf("Partea 2\n");
	struct Pensiune p;
	p.denumire = "z";
	p.nrCamere = 10;
	p.pretCamera = 11;
	p.pretIntretinereCamera = 1;
	scriePensiune("pensiuniOut.txt", p);

	printf("Partea 3\n");
	scrieVector("pensiuniOut.txt", pensiuni, nr);
}
