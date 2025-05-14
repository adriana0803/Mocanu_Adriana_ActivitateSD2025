#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct NodD NodD;
struct NodD {
	Masina info;
	NodD* next;
	NodD* prev;
};

typedef struct {
	NodD* first;
	NodD* last;
} ListaDubla;

typedef struct NodS {
	Masina info;
	struct NodS* next;
} NodS;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[256];
	Masina m;
	if (!fgets(buffer, sizeof(buffer), file)) return (Masina) { 0, 0, 0, NULL, NULL, 0 };
	char* token = strtok(buffer, ",\n");
	m.id = atoi(token);
	m.nrUsi = atoi(strtok(NULL, ",\n"));
	m.pret = atof(strtok(NULL, ",\n"));
	m.model = strdup(strtok(NULL, ",\n"));
	m.numeSofer = strdup(strtok(NULL, ",\n"));
	char* serie = strtok(NULL, ",\n");
	m.serie = serie ? serie[0] : 'X';
	return m;
}

void afisareMasina(Masina m) {
	printf("ID: %d | Usi: %d | Pret: %.2f | Model: %s | Sofer: %s | Serie: %c\n",
		m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
}

void adaugaSortatPret(ListaDubla* lista, Masina m) {
	NodD* nou = malloc(sizeof(NodD));
	nou->info = m;
	nou->next = nou->prev = NULL;
	if (!lista->first) {
		lista->first = lista->last = nou;
		return;
	}
	NodD* temp = lista->first;
	while (temp && temp->info.pret < m.pret) temp = temp->next;
	if (temp == lista->first) {
		nou->next = lista->first;
		lista->first->prev = nou;
		lista->first = nou;
	}
	else if (!temp) {
		nou->prev = lista->last;
		lista->last->next = nou;
		lista->last = nou;
	}
	else {
		nou->next = temp;
		nou->prev = temp->prev;
		temp->prev->next = nou;
		temp->prev = nou;
	}
}

void stergePozitie(ListaDubla* lista, int poz) {
	if (!lista->first) return;
	NodD* p = lista->first;
	int i = 0;
	while (p && i < poz) { p = p->next; i++; }
	if (!p) return;
	if (p == lista->first) {
		lista->first = p->next;
		if (lista->first) lista->first->prev = NULL;
		else lista->last = NULL;
	}
	else if (p == lista->last) {
		lista->last = p->prev;
		lista->last->next = NULL;
	}
	else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	free(p->info.model);
	free(p->info.numeSofer);
	free(p);
}

void afisareCrescator(ListaDubla lista) {
	for (NodD* p = lista.first; p; p = p->next) afisareMasina(p->info);
}

void afisareDescrescator(ListaDubla lista) {
	for (NodD* p = lista.last; p; p = p->prev) afisareMasina(p->info);
}

NodS* salvareInListaSimpla(ListaDubla lista, float prag) {
	NodS* cap = NULL, * sf = NULL;
	for (NodD* p = lista.first; p; p = p->next) {
		if (p->info.pret > prag) {
			NodS* nou = malloc(sizeof(NodS));
			nou->info.id = p->info.id;
			nou->info.nrUsi = p->info.nrUsi;
			nou->info.pret = p->info.pret;
			nou->info.serie = p->info.serie;
			nou->info.model = strdup(p->info.model);
			nou->info.numeSofer = strdup(p->info.numeSofer);
			nou->next = NULL;
			if (!cap) cap = sf = nou;
			else { sf->next = nou; sf = nou; }
		}
	}
	return cap;
}

void interschimbaPozitii(ListaDubla lista, int p1, int p2) {
	if (p1 == p2) return;
	NodD* n1 = NULL, * n2 = NULL;
	NodD* p = lista.first;
	int i = 0;
	while (p) {
		if (i == p1) n1 = p;
		if (i == p2) n2 = p;
		i++;
		p = p->next;
	}
	if (n1 && n2) {
		Masina aux = n1->info;
		n1->info = n2->info;
		n2->info = aux;
	}
}

void dezalocare(ListaDubla* lista, NodS** capSimpla) {
	while (*capSimpla) {
		NodS* temp = *capSimpla;
		*capSimpla = temp->next;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
	while (lista->first) {
		NodD* temp = lista->first;
		lista->first = temp->next;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
	lista->last = NULL;
}

int main() {
	ListaDubla lista = { NULL, NULL };
	FILE* f = fopen("masini.txt", "r");
	if (!f) return -1;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		if (m.model && m.numeSofer) adaugaSortatPret(&lista, m);
	}
	fclose(f);

	printf("Crescator:\n"); afisareCrescator(lista);
	printf("\nDescrescator:\n"); afisareDescrescator(lista);

	printf("\nDupa stergere pozitia 2:\n");
	stergePozitie(&lista, 2);
	afisareCrescator(lista);

	printf("\nInterschimbare 0 si 1:\n");
	interschimbaPozitii(lista, 0, 1);
	afisareCrescator(lista);

	printf("\nLista simpla masini cu pret > 5000:\n");
	NodS* cap = salvareInListaSimpla(lista, 5000);
	for (NodS* p = cap; p; p = p->next) afisareMasina(p->info);

	dezalocare(&lista, &cap);
	return 0;
}
