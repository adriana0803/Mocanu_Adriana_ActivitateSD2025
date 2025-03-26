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

struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct Lista {
	Nod* first;
	Nod* last;
};
typedef struct Lista Lista;

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

void afisareListaMasini(Lista list) {
	Nod* f = list.first;
	while (f) {
		afisareMasina(f->info);
		f = f->next;
	}
}

void afisareListaMasiniSf(Lista list) {
	Nod* f = list.last;
	while (f) {
		afisareMasina(f->info);
		f = f->prev;
	}
}

void adaugaMasinaInLista(Lista* list, Masina masinaNoua) {
	Nod* f = (Nod*)malloc(sizeof(Nod));
	f->info = masinaNoua;
	f->prev = list->last;
	f->next = NULL;
	if (list->last) {
		list->last->next = f;
	}
	else {
		list->first = f;
	}
	list->last = f;
}


void adaugaLaInceputInLista(Lista* list, Masina masinaNoua) {
	Nod* f = (Nod*)malloc(sizeof(Nod));
	f->info = masinaNoua;
	f->next= list->first;
	f->prev = NULL;
	if (list->first) {
		list->first->prev = f;
	}
	else {
		list->last = f;
	}
	list->first = f;
}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista list;
	list.first = NULL;
	list.last = NULL;
	while (!feof(f)) {
		//adaugaMasinaInLista(&list, citireMasinaDinFisier(f));
		adaugaLaInceputInLista(&list, citireMasinaDinFisier(f));
	}
	fclose(f);
	return list;
}

void dezalocareLDMasini(Lista* list) {
	Nod* f = list->first;
	while (f->next != NULL) {
		free(f->info.numeSofer);
		free(f->info.model);
		f = f->next;
		free(f->prev);
	}
	free(f->info.numeSofer);
	free(f->info.model);
	free(f);
	list->first = NULL;
	list->last = NULL;
}

float calculeazaPretMediu(Lista list) {
	Nod* aux = list.first;
	float suma = 0;
	float cnt = 0;
	while (aux) {
		suma += aux->info.pret;
		aux = aux->next;
		cnt += 1;
	}
	return suma/cnt;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {
	Lista list;
	list = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(list);
	float pretMediu = calculeazaPretMediu(list);
	printf("Pret Mediu: %.2f\n", pretMediu);
	dezalocareLDMasini(&list);

	return 0;
}