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
//typedef struct NodAVL {
//	Masina info;
//	struct NodAVL* stanga;
//	struct NodAVL* dreapta;
//	int inaltime;
//} NodAVL;
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
//NodAVL* adaugaMasinaInArboreEchilibrat(NodAVL* rad, Masina m) {
//	if (!rad) {
//		NodAVL* nou = (NodAVL*)malloc(sizeof(NodAVL));
//		nou->info = m;
//		nou->stanga = nou->dreapta = NULL;
//		nou->inaltime = 1;
//		return nou;
//	}
//
//	if (m.id < rad->info.id)
//		rad->stanga = adaugaMasinaInArboreEchilibrat(rad->stanga, m);
//	else if (m.id > rad->info.id)
//		rad->dreapta = adaugaMasinaInArboreEchilibrat(rad->dreapta, m);
//	else
//		return rad; // ID duplicat, ignor?m
//
//	rad->inaltime = 1 + max(inaltime(rad->stanga), inaltime(rad->dreapta));
//
//	int balans = gradEchilibru(rad);
//
//	if (balans > 1 && m.id < rad->stanga->info.id)
//		return rotatieDreapta(rad);
//
//	if (balans < -1 && m.id > rad->dreapta->info.id)
//		return rotatieStanga(rad);
//
//	if (balans > 1 && m.id > rad->stanga->info.id) {
//		rad->stanga = rotatieStanga(rad->stanga);
//		return rotatieDreapta(rad);
//	}
//
//	if (balans < -1 && m.id < rad->dreapta->info.id) {
//		rad->dreapta = rotatieDreapta(rad->dreapta);
//		return rotatieStanga(rad);
//	}
//
//	return rad;
//}
//
//NodAVL* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	if (!f) {
//		perror("Fisier inexistent");
//		return NULL;
//	}
//
//	NodAVL* rad = NULL;
//	while (!feof(f)) {
//		Masina m = citireMasinaDinFisier(f);
//		if (m.model != NULL)
//			rad = adaugaMasinaInArboreEchilibrat(rad, m);
//	}
//
//	fclose(f);
//	return rad;
//}
//
//void inordine(NodAVL* rad) {
//	if (rad) {
//		inordine(rad->stanga);
//		afisareMasina(rad->info);
//		inordine(rad->dreapta);
//	}
//}
//
//void preordine(NodAVL* rad) {
//	if (rad) {
//		afisareMasina(rad->info);
//		preordine(rad->stanga);
//		preordine(rad->dreapta);
//	}
//}
//
//void postordine(NodAVL* rad) {
//	if (rad) {
//		postordine(rad->stanga);
//		postordine(rad->dreapta);
//		afisareMasina(rad->info);
//	}
//}
//
//void afisareMasiniDinArbore(NodAVL* rad) {
//	printf("\n--- Inordine ---\n");
//	inordine(rad);
//	printf("\n--- Preordine ---\n");
//	preordine(rad);
//	printf("\n--- Postordine ---\n");
//	postordine(rad);
//}
//
//void dezalocareArboreDeMasini(NodAVL* rad) {
//	if (rad) {
//		dezalocareArboreDeMasini(rad->stanga);
//		dezalocareArboreDeMasini(rad->dreapta);
//		free(rad->info.model);
//		free(rad->info.numeSofer);
//		free(rad);
//	}
//}
//
//int main() {
//	NodAVL* rad = citireArboreDeMasiniDinFisier("masini.txt");
//
//	afisareMasiniDinArbore(rad);
//	dezalocareArboreDeMasini(rad);
//	return 0;
//}