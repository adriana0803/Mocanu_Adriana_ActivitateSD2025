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

void afisareMasina(Masina masina) {
    printf("ID: %d\n", masina.id);
    printf("Nr. usi: %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
    for (int i = 0; i < nrMasini; i++) {
        afisareMasina(masini[i]);
    }
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
    Masina* copie = (Masina*)realloc(*masini, sizeof(Masina) * (*nrMasini + 1));
    if (!copie) {
        printf("Eroare alocare memorie!\n");
        return;
    }
    copie[*nrMasini] = masinaNoua;
    (*nrMasini)++;
    *masini = copie;
}

Masina citireMasinaFisier(FILE* file) {
    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), file)) {
        Masina m = { 0, 0, 0.0, NULL, NULL, 0 };
        return m;
    }

    Masina m;
    char* aux = strtok(buffer, ",\n");
    if (!aux) return m;
    m.id = atoi(aux);
    m.nrUsi = atoi(strtok(NULL, ",\n"));
    m.pret = atof(strtok(NULL, ",\n"));

    aux = strtok(NULL, ",\n");
    m.model = malloc(strlen(aux) + 1);
    strcpy(m.model, aux);

    aux = strtok(NULL, ",\n");
    m.numeSofer = malloc(strlen(aux) + 1);
    strcpy(m.numeSofer, aux);

    m.serie = *strtok(NULL, ",\n");
    return m;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
    FILE* file = fopen(numeFisier, "r");
    if (!file) {
        printf("Eroare la deschiderea fisierului!\n");
        return NULL;
    }

    Masina* masini = NULL;
    while (!feof(file)) {
        Masina m = citireMasinaFisier(file);
        if (m.model != NULL && m.numeSofer != NULL) {
            adaugaMasinaInVector(&masini, nrMasiniCitite, m);
        }
    }
    fclose(file);
    return masini;
}
void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	for (int i = 0; i < nrMasini; i++) {
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
	}
	free(*vector);
	*vector = NULL;
	*nrMasini = 0;
}

float pretMediuDupaNrUsi(Masina* vector, int nrMasini, int nrUsi) {
    float suma = 0;
    int index = 0;
    for (int i = 0; i < nrMasini; i++) {
        if (vector[i].nrUsi == nrUsi) {
            suma += vector[i].pret;
            index++;
        }
    }
    if (index > 0) {
        return suma / index;
    }
    else return 0;
}

int main() {

	Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);

    float medie = pretMediuDupaNrUsi(masini, nrMasini, 6);
    printf("Media masinilor cu x usi este: %.2f", medie);

    dezalocareVectorMasini(&masini, &nrMasini);

	return 0;
}