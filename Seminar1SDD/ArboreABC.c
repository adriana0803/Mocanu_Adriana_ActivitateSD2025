//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//} Masina;
//
//typedef struct NodABC {
//	Masina info;
//	struct NodABC* stanga;
//	struct NodABC* dreapta;
//} NodABC;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	if (!fgets(buffer, 100, file)) return (Masina) { 0 };
//
//	char* aux;
//	Masina m1;
//
//	aux = strtok(buffer, sep);
//	if (!aux) return (Masina) { 0 };
//	m1.id = atoi(aux);
//
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy(m1.model, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy(m1.numeSofer, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina m) {
//	printf("ID: %d | Usi: %d | Pret: %.2f | Model: %s | Sofer: %s | Serie: %c\n",
//		m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
//}
//
//NodABC* adaugareMasinaInArbore(NodABC* rad, Masina m) {
//	if (!rad) {
//		NodABC* nou = (NodABC*)malloc(sizeof(NodABC));
//		nou->info = m;
//		nou->stanga = nou->dreapta = NULL;
//		return nou;
//	}
//	if (m.id < rad->info.id)
//		rad->stanga = adaugareMasinaInArbore(rad->stanga, m);
//	else
//		rad->dreapta = adaugareMasinaInArbore(rad->dreapta, m);
//	return rad;
//}
//
//NodABC* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	if (!file) {
//		perror("Eroare la deschiderea fisierului");
//		return NULL;
//	}
//
//	NodABC* rad = NULL;
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		if (m.model != NULL)
//			rad = adaugareMasinaInArbore(rad, m);
//	}
//	fclose(file);
//	return rad;
//}
//
//void inordine(NodABC* rad) {
//	if (rad) {
//		inordine(rad->stanga);
//		afisareMasina(rad->info);
//		inordine(rad->dreapta);
//	}
//}
//
//void preordine(NodABC* rad) {
//	if (rad) {
//		afisareMasina(rad->info);
//		preordine(rad->stanga);
//		preordine(rad->dreapta);
//	}
//}
//
//void postordine(NodABC* rad) {
//	if (rad) {
//		postordine(rad->stanga);
//		postordine(rad->dreapta);
//		afisareMasina(rad->info);
//	}
//}
//
//void afisareMasiniDinArbore(NodABC* rad) {
//	printf("\n--- INORDINE ---\n");
//	inordine(rad);
//	printf("\n--- PREORDINE ---\n");
//	preordine(rad);
//	printf("\n--- POSTORDINE ---\n");
//	postordine(rad);
//}
//
//void dezalocareArboreDeMasini(NodABC* rad) {
//	if (rad) {
//		dezalocareArboreDeMasini(rad->stanga);
//		dezalocareArboreDeMasini(rad->dreapta);
//		dezalocaMasina(&rad->info);
//		free(rad);
//	}
//}
//
//int main() {
//	NodABC* rad = citireArboreDeMasiniDinFisier("masini.txt");
//
//	afisareMasiniDinArbore(rad);
//	dezalocareArboreDeMasini(rad);
//	return 0;
//}