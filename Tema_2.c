#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//Pislaru Ingrid => pensiune
struct Pensiune {
	char* denumire;
	char* adresa;
	int nrCamere;
	float pretCamera;
	float pretIntretinereCamera;
};

struct Pensiune citirePensiune() {
	struct Pensiune p;
	char den[50];
	char loc[60];
	printf("Introduceti denumirea: \n");
	scanf("%s", den);
	p.denumire = (char*)malloc((strlen(den) + 1) * sizeof(char));
	strcpy(p.denumire, den);
	printf("Introduceti adresa: \n");
	scanf("%s", loc);
	p.adresa = (char*)malloc((strlen(loc) + 1) * sizeof(char));
	strcpy(p.adresa, loc);
	printf("Introduceti nr camere: \n");
	scanf("%d", &p.nrCamere);
	printf("Introduceti pretul unei camere: \n");
	scanf("%f", &p.pretCamera);
	printf("Introduceti pretul intretinerii unei camere: \n");
	scanf("%f", &p.pretIntretinereCamera);
	return p;
}

struct Pensiune initializare(const char* denumire, const char* adresa, int nrCamere, float pretCamera, float pretIntretinereCamera) {
	struct Pensiune c;
	//intai alocam spatiul necesar
	c.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	//si dupa facem copie aka atribuim
	strcpy(c.denumire, denumire);

	c.adresa = (char*)malloc(sizeof(char) * (strlen(adresa) + 1));
	//si dupa facem copie aka atribuim
	strcpy(c.adresa, adresa);

	c.nrCamere = nrCamere;
	c.pretCamera = pretCamera;
	c.pretIntretinereCamera = pretIntretinereCamera;
	return c;
}

void afisarePensiune(struct Pensiune p) {
	printf("Denumire: %s, adresa: %s, numar de camere: %d, pretul unei camere: %.2f lei pe noapte, costul suportat de pensiune pentru intretinerea camerei: %.2f lei pe noapte", p.denumire, p.adresa, p.nrCamere, p.pretCamera, p.pretIntretinereCamera);
}

float profitMaximPeNoapte(struct Pensiune p) {
	return (p.pretCamera - p.pretIntretinereCamera) * p.nrCamere;
}

//trebuie transmis prin pointer!!
//altfel nu se modifica
//si dupa cu p->
void modificaPretCamera(struct Pensiune* p, float pretNou) {
	p->pretCamera = pretNou;
}

struct Pensiune* pensiuniCuProfitPeste100(struct Pensiune* vector, int nr, int* nrPensiuniCuProfitPeste100) {
	*nrPensiuniCuProfitPeste100 = 0;
	int k = 0;
	for (int i = 0; i< nr; i++) {
		if (profitMaximPeNoapte(vector[i]) >= 100) {
			(*nrPensiuniCuProfitPeste100)++;
		}
	}

	struct Pensiune* rez = (struct Pensiune*)malloc(sizeof(struct Pensiune) * (*nrPensiuniCuProfitPeste100));
	for (int i = 0; i< nr; i++) {
		if (profitMaximPeNoapte(vector[i]) >= 100) {
			rez[k++] = initializare(vector[i].denumire, vector[i].adresa, vector[i].nrCamere, vector[i].pretCamera, vector[i].pretIntretinereCamera);
		}
	}

	return rez;
}

struct Pensiune* pensiuniCuProfitSub100(struct Pensiune* vector, int nr, int* nrPensiuniCuProfitSub100) {
	int x = 0;
	struct Pensiune* rez = pensiuniCuProfitPeste100(vector, nr, &x);
	*nrPensiuniCuProfitSub100 = nr - x;
	struct Pensiune* ans = (struct Pensiune*)malloc(sizeof(struct Pensiune) * (*nrPensiuniCuProfitSub100));
	int k = 0;
	for (int i = 0; i < nr; i++) {
		if (profitMaximPeNoapte(vector[i]) < 100) {
			ans[k++] = initializare(vector[i].denumire, vector[i].adresa, vector[i].nrCamere, vector[i].pretCamera, vector[i].pretIntretinereCamera);
		}
	}
	return ans;
}

void afisareVectorPensiuni(struct Pensiune* vector, int nr) {
	if (nr > 0 && vector != NULL) {
		for (int i = 0; i < nr; i++) {
			afisarePensiune(vector[i]);
			printf("\n");
		}
	}
}

struct Pensiune* concatenareDoiVectori(struct Pensiune* v1, int nr1, struct Pensiune* v2, int nr2) {
	struct Pensiune* vectorConcatenat = (struct Pensiune*)malloc(sizeof(struct Pensiune) * (nr1 + nr2));
	int k = 0;
	for (int i = 0; i < nr1; i++) {
		vectorConcatenat[k++] = initializare(v1[i].denumire, v1[i].adresa, v1[i].nrCamere, v1[i].pretCamera, v1[i].pretIntretinereCamera);
	}
	for (int i = 0; i < nr2; i++) {
		vectorConcatenat[k++] = initializare(v2[i].denumire, v2[i].adresa, v2[i].nrCamere, v2[i].pretCamera, v2[i].pretIntretinereCamera);
	}
	return vectorConcatenat;
}




/*

void dezalocare() {

}
*/

int main() {
	/*
	int nr;
	printf("Introduceti un numar de pensiune, mai mare sau egal cu 5: ");
	scanf("%d", &nr);
	if (nr < 5) {
		printf("Numarul este prea mic");
		return 1;
	}
	*/

	int nr = 5;

	//1. Afisare vector pensiuni
	
	struct Pensiune* pensiuni = (struct Pensiune*)malloc(nr * sizeof(struct Pensiune));
	/*
	for (int i = 0; i < nr; i++) {
		pensiuni[i] = citirePensiune();
	}
	*/

	pensiuni[0] = initializare("a", "a", 10, 10, 1);
	pensiuni[1] = initializare("b", "b", 20, 11, 1);
	pensiuni[2] = initializare("c", "c", 100, 2, 1);
	pensiuni[3] = initializare("d", "d", 20, 21, 1);
	pensiuni[4] = initializare("e", "e", 80, 10, 9);

	printf("Afisare toate pensiunile: ");
	afisareVectorPensiuni(pensiuni, 5);

	//2. Conditie

	int nrPensiuniCuProfitPeste100 = 0;

	struct Pensiune* pensiuniProfitabile=pensiuniCuProfitPeste100(pensiuni, nr, &nrPensiuniCuProfitPeste100);
	printf("Afisare pensiuni profitabile:\n");
	for (int i = 0; i < nrPensiuniCuProfitPeste100; i++) {
		printf("Pensiunea %d: ", i+1);
		afisarePensiune(pensiuniProfitabile[i]);
		printf("\n");
		printf("\n");
	}

	//3. Negarea conditiei

	int nrPensiuniCuProfitSub100 = 0;
	struct Pensiune* pensiuniNeprofitabile = pensiuniCuProfitSub100(pensiuni, nr, &nrPensiuniCuProfitSub100);
	printf("Afisare pensiuni neprofitabile:\n");
	for (int i = 0; i < nrPensiuniCuProfitSub100; i++) {
		printf("Pensiunea %d: ", i + 1);
		afisarePensiune(pensiuniNeprofitabile[i]);
		printf("\n");
		printf("\n");
	}

	//4. Concatenare

	struct Pensiune p1 = initializare("pens1", "munte", 10, 10, 1);
	struct Pensiune p2 = initializare("pens2", "mare", 20, 11, 1);
	struct Pensiune* vector1=(struct Pensiune*)malloc(2*sizeof(struct Pensiune));
	vector1[0] = p1;
	vector1[1] = p2;
	struct Pensiune p3= initializare("pens3", "padure", 100, 10, 1);
	struct Pensiune p4 = initializare("pens4", "lac", 10, 10, 1);
	struct Pensiune p5 = initializare("pens5", "munte", 1000, 10, 1);
	struct Pensiune* vector2 = (struct Pensiune*)malloc(3 * sizeof(struct Pensiune));
	vector2[0] = p3;
	vector2[1] = p4;
	vector2[2] = p5;
	printf("Afisare vectori concatenati: \n\n");
	afisareVectorPensiuni(concatenareDoiVectori(vector1, 2, vector2, 3), 5);

	return 0;
}
