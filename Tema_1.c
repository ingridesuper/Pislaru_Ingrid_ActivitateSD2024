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
	p.adresa= (char*)malloc((strlen(loc) + 1) * sizeof(char));
	strcpy(p.adresa, loc);
	printf("Introduceti nr camere: \n");
	scanf("%d", &p.nrCamere);
	printf("Introduceti pretul unei camere: \n");
	scanf("%f", &p.pretCamera);
	printf("Introduceti pretul intretinerii unei camere: \n");
	scanf("%f", &p.pretIntretinereCamera);
	return p;
}

void afisarePensiune(struct Pensiune p) {
	printf("Denumire: %s, adresa: %s, numar de camere: %d, pretul unei camere: %.2f lei pe noapte, costul suportat de pensiune pentru intretinerea camerei: %.2f lei pe noapte", p.denumire, p.adresa, p.nrCamere, p.pretCamera, p.pretIntretinereCamera);
}

float profitMaximPeNoapte(struct Pensiune p) {
	return (p.pretCamera - p.pretIntretinereCamera) * p.nrCamere;
}

//trebuie transmis prin popinter!!
//altfel nu se modifica
//si dup cu p->
void modificaPretCamera(struct Pensiune* p, float pretNou) {
	p->pretCamera = pretNou;
}

int main() {
	struct Pensiune pensiuneLaMunte=citirePensiune();
	afisarePensiune(pensiuneLaMunte);
	printf("\n");
	printf(Profit maxim pe noapte: "%.2f", profitMaximPeNoapte(pensiuneLaMunte));
	printf("\n");
	modificaPretCamera(&pensiuneLaMunte, 200);
	printf("\n");
	afisarePensiune(pensiuneLaMunte);
	return 0;
}
