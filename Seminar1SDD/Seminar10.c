#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct NodePrincipal NodePrincipal;

typedef struct NodeSecundar NodeSecundar;

struct NodeSecundar {
	NodePrincipal* info;
	NodeSecundar* next;
};


struct NodePrincipal {
	NodePrincipal* next;
	NodeSecundar* vecin;
	Masina info;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara

//2.
//functii de inserare in liste
//si in principala si in secundara

NodePrincipal* inserareLaSfInListaPrincipala(NodePrincipal* cap, Masina info) {
	NodePrincipal* nou = (NodePrincipal*)malloc(sizeof(NodePrincipal));
	nou->info = info;
	nou->next = NULL;
	nou->vecin = NULL;

	if (!cap) return nou;
	NodePrincipal* p = cap;
	while (p->next) {
		p = p->next;
		p->next = nou;
		return cap;
	}
}

NodeSecundar* inserareLaInceputListaSecundara(NodeSecundar* cap, NodePrincipal* info) {
	NodeSecundar* nou = (NodeSecundar*)malloc(sizeof(NodeSecundar));
	nou->info = info;
	nou->next = NULL;

	nou->next = cap;
	return cap;
}

//3.
//functie de cautarea in lista principala dupa ID
void* cautaNodDupaID(NodePrincipal* listaPrincipala, int id) {
	while (listaPrincipala && listaPrincipala->info.id != id) {
		listaPrincipala = listaPrincipala->next;
	}
	return listaPrincipala;
}

//4.
//inserare muchie
void inserareMuchie(void* listaPrincipala, int idStart, int idStop) {
	NodePrincipal* nodStart = cautaNodDupaID(listaPrincipala, idStart);
	NodePrincipal* nodStop = cautaNodDupaID(listaPrincipala, idStop);
	if (nodStart && nodStop) {
		nodStart->vecin = inserareLaInceputListaSecundara(nodStart->vecin, nodStop);
		nodStop->vecin = inserareLaInceputListaSecundara(nodStop->vecin, nodStart);
	}
}


void* citireNoduriMasiniDinFisier(const char* numeFisier) {
	NodePrincipal* listaPrincipala = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		inserareLaSfInListaPrincipala(listaPrincipala, citireMasinaDinFisier(file));
	}
	fclose(file);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodePrincipal* listaPrincipala, const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		int idStart;
		int idStop;

		fscanf(file, "%d %d", &idStart, &idStop);
		inserareMuchie(listaPrincipala, idStart, idStop);
	}
}

void stergereNodeSecundar(NodeSecundar** cap) {
	NodeSecundar* aux = (*cap)->next;
	while ((*cap)) {
		aux = (*cap)->next;
		free(*cap);
		(*cap) = aux;
	}
}

void dezalocareNoduriGraf(NodePrincipal** listaPrincipala) {
	NodePrincipal* aux;
	while ((*listaPrincipala)) {
		aux = (*listaPrincipala)->next;
		stergereNodeSecundar((*listaPrincipala)->vecin);
		if ((*listaPrincipala)->info.model) {
			free((*listaPrincipala)->info.model);
		}
		if ((*listaPrincipala)->info.numeSofer) {
			free((*listaPrincipala)->info.numeSofer);
		}
	}
	free(*listaPrincipala);
	(*listaPrincipala) = aux;
}

int main() {
	NodePrincipal* graf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	dezalocareNoduriGraf(&graf);

	return 0;
}