//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//typedef struct Nod Nod;
//
//struct Nod {
//	Masina info;
//	struct Nod* next;
//};
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[256];
//	Masina m;
//	if (!fgets(buffer, sizeof(buffer), file)) return (Masina) { 0, 0, 0, NULL, NULL, 0 };
//	char* token = strtok(buffer, ",\n");
//	m.id = atoi(token);
//	m.nrUsi = atoi(strtok(NULL, ",\n"));
//	m.pret = atof(strtok(NULL, ",\n"));
//	m.model = strdup(strtok(NULL, ",\n"));
//	m.numeSofer = strdup(strtok(NULL, ",\n"));
//	char* serie = strtok(NULL, ",\n");
//	m.serie = serie ? serie[0] : 'X';
//	return m;
//}
//
//void afisareMasina(Masina m) {
//	printf("ID: %d | Usi: %d | Pret: %.2f | Model: %s | Sofer: %s | Serie: %c\n",
//		m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
//}
//
//void afisareLista(Nod* cap) {
//	while (cap) {
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void inserareSortataPret(Nod** cap, Masina m) {
//	Nod* nod = malloc(sizeof(Nod));
//	nod->info = m;
//	nod->next = NULL;
//	if (!*cap || m.pret < (*cap)->info.pret) {
//		nod->next = *cap;
//		*cap = nod;
//	}
//	else {
//		Nod* p = *cap;
//		while (p->next && p->next->info.pret < m.pret) {
//			p = p->next;
//		}
//		nod->next = p->next;
//		p->next = nod;
//	}
//}
//
//void stergerePozitie(Nod** cap, int poz) {
//	if (!*cap || poz < 0) return;
//	Nod* temp = *cap;
//	if (poz == 0) {
//		*cap = temp->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//		return;
//	}
//	for (int i = 0; temp && i < poz - 1; i++) temp = temp->next;
//	if (!temp || !temp->next) return;
//	Nod* del = temp->next;
//	temp->next = del->next;
//	free(del->info.model);
//	free(del->info.numeSofer);
//	free(del);
//}
//
//Masina* filtrareMasini(Nod* cap, float prag, int* dim) {
//	*dim = 0;
//	Nod* p = cap;
//	while (p) {
//		if (p->info.pret > prag) (*dim)++;
//		p = p->next;
//	}
//	Masina* v = malloc((*dim) * sizeof(Masina));
//	int i = 0;
//	p = cap;
//	while (p) {
//		if (p->info.pret > prag) {
//			v[i].id = p->info.id;
//			v[i].nrUsi = p->info.nrUsi;
//			v[i].pret = p->info.pret;
//			v[i].serie = p->info.serie;
//			v[i].model = strdup(p->info.model);
//			v[i].numeSofer = strdup(p->info.numeSofer);
//			i++;
//		}
//		p = p->next;
//	}
//	return v;
//}
//
//void interschimbaPozitii(Nod* cap, int p1, int p2) {
//	if (p1 == p2) return;
//	Nod* n1 = NULL, * n2 = NULL, * p = cap;
//	int i = 0;
//	while (p) {
//		if (i == p1) n1 = p;
//		if (i == p2) n2 = p;
//		p = p->next;
//		i++;
//	}
//	if (n1 && n2) {
//		Masina aux = n1->info;
//		n1->info = n2->info;
//		n2->info = aux;
//	}
//}
//
//void dezalocareLista(Nod** cap) {
//	while (*cap) {
//		Nod* temp = *cap;
//		*cap = temp->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//	}
//}
//
//int main() {
//	Nod* cap = NULL;
//	FILE* f = fopen("masini.txt", "r");
//	if (!f) {
//		printf("Eroare la deschiderea fisierului.\n");
//		return -1;
//	}
//	while (!feof(f)) {
//		Masina m = citireMasinaDinFisier(f);
//		if (m.model && m.numeSofer) {
//			inserareSortataPret(&cap, m);
//		}
//	}
//	fclose(f);
//
//	printf("Lista initiala:\n");
//	afisareLista(cap);
//
//	printf("\nStergem de pe pozitia 1:\n");
//	stergerePozitie(&cap, 1);
//	afisareLista(cap);
//
//	int dim;
//	Masina* v = filtrareMasini(cap, 5000.0f, &dim);
//	printf("\nMasini filtrate (pret > 5000):\n");
//	for (int i = 0; i < dim; i++) {
//		afisareMasina(v[i]);
//		free(v[i].model);
//		free(v[i].numeSofer);
//	}
//	free(v);
//
//	printf("\nInterschimbare pozitii 0 si 1 (daca exista):\n");
//	interschimbaPozitii(cap, 0, 1);
//	afisareLista(cap);
//
//	dezalocareLista(&cap);
//	return 0;
//}