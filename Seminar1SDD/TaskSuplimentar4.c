//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//    int id;
//    char* titlu;
//    char* artist;
//    float durata;
//    int nrRecenzii;
//    float* note;
//} Melodie;
//
//void afisareMelodie(Melodie m) {
//    printf("ID: %d\nTitlu: %s\nArtist: %s\nDurata: %.2f\nRecenzii: %d\n", m.id, m.titlu, m.artist, m.durata, m.nrRecenzii);
//    if (m.nrRecenzii > 0) {
//        printf("Note: ");
//        for (int i = 0; i < m.nrRecenzii; i++) {
//            printf("%.2f ", m.note[i]);
//        }
//        printf("\n");
//    }
//    printf("------------\n");
//}
//
//Melodie citireMelodie(FILE* f) {
//    char buffer[256];
//    if (!fgets(buffer, sizeof(buffer), f)) {
//        return (Melodie) { 0, NULL, NULL, 0, 0, NULL };
//    }
//
//    Melodie m;
//    char* token = strtok(buffer, ",\n");
//    m.id = atoi(token);
//
//    token = strtok(NULL, ",\n");
//    m.titlu = strdup(token);
//
//    token = strtok(NULL, ",\n");
//    m.artist = strdup(token);
//
//    token = strtok(NULL, ",\n");
//    m.durata = atof(token);
//
//    token = strtok(NULL, ",\n");
//    m.nrRecenzii = atoi(token);
//
//    m.note = NULL;
//    if (m.nrRecenzii > 0) {
//        m.note = malloc(sizeof(float) * m.nrRecenzii);
//        for (int i = 0; i < m.nrRecenzii; i++) {
//            token = strtok(NULL, ",\n");
//            m.note[i] = atof(token);
//        }
//    }
//
//    return m;
//}
//
//Melodie* citireVectorMelodii(const char* numeFisier, int* nrMelodii) {
//    FILE* f = fopen(numeFisier, "r");
//    if (!f) {
//        printf("Eroare deschidere fisier.\n");
//        return NULL;
//    }
//
//    Melodie* vector = NULL;
//    *nrMelodii = 0;
//
//    Melodie m;
//    while ((m = citireMelodie(f)).titlu != NULL) {
//        vector = realloc(vector, (*nrMelodii + 1) * sizeof(Melodie));
//        vector[*nrMelodii] = m;
//        (*nrMelodii)++;
//    }
//
//    fclose(f);
//    return vector;
//}
//
//int categorieDurata(float durata) {
//    if (durata < 3.0f) return 0;
//    else if (durata <= 4.0f) return 1;
//    else return 2;
//}
//
//void deepCopyInMatrice(Melodie* v, int n, Melodie*** matrice, int** dimLinii, int* nrLinii) {
//    *nrLinii = 3;  // 0: <3.0, 1: [3.0, 4.0], 2: >4.0
//    *matrice = malloc(sizeof(Melodie*) * (*nrLinii));
//    *dimLinii = calloc(*nrLinii, sizeof(int));
//
//    for (int i = 0; i < *nrLinii; i++) {
//        (*matrice)[i] = NULL;
//    }
//
//    for (int i = 0; i < n; i++) {
//        int linie = categorieDurata(v[i].durata);
//        int poz = (*dimLinii)[linie];
//
//        (*matrice)[linie] = realloc((*matrice)[linie], (poz + 1) * sizeof(Melodie));
//
//        Melodie m;
//        m.id = v[i].id;
//        m.titlu = strdup(v[i].titlu);
//        m.artist = strdup(v[i].artist);
//        m.durata = v[i].durata;
//        m.nrRecenzii = v[i].nrRecenzii;
//        m.note = malloc(sizeof(float) * m.nrRecenzii);
//        for (int j = 0; j < m.nrRecenzii; j++) {
//            m.note[j] = v[i].note[j];
//        }
//
//        (*matrice)[linie][poz] = m;
//        (*dimLinii)[linie]++;
//    }
//}
//
//void sortareLinii(Melodie*** matrice, int** dimLinii, int nrLinii) {
//    for (int i = 0; i < nrLinii - 1; i++) {
//        for (int j = i + 1; j < nrLinii; j++) {
//            if ((*dimLinii)[i] > (*dimLinii)[j]) {
//                int tmp = (*dimLinii)[i];
//                (*dimLinii)[i] = (*dimLinii)[j];
//                (*dimLinii)[j] = tmp;
//
//                Melodie* aux = (*matrice)[i];
//                (*matrice)[i] = (*matrice)[j];
//                (*matrice)[j] = aux;
//            }
//        }
//    }
//}
//
//void afisareMatrice(Melodie** matrice, int* dimLinii, int nrLinii) {
//    for (int i = 0; i < nrLinii; i++) {
//        printf("Cluster %d (nr melodii: %d):\n", i, dimLinii[i]);
//        for (int j = 0; j < dimLinii[i]; j++) {
//            afisareMelodie(matrice[i][j]);
//        }
//    }
//}
//
//void dezalocareVector(Melodie** v, int* n) {
//    if (*v) {
//        for (int i = 0; i < *n; i++) {
//            free((*v)[i].titlu);
//            free((*v)[i].artist);
//            free((*v)[i].note);
//        }
//        free(*v);
//        *v = NULL;
//        *n = 0;
//    }
//}
//
//void dezalocareMatrice(Melodie*** matrice, int** dimLinii, int nrLinii) {
//    for (int i = 0; i < nrLinii; i++) {
//        for (int j = 0; j < (*dimLinii)[i]; j++) {
//            free((*matrice)[i][j].titlu);
//            free((*matrice)[i][j].artist);
//            free((*matrice)[i][j].note);
//        }
//        free((*matrice)[i]);
//    }
//    free(*matrice);
//    free(*dimLinii);
//    *matrice = NULL;
//    *dimLinii = NULL;
//}
//
//int main() {
//    int nrMelodii = 0;
//    Melodie* vector = citireVectorMelodii("melodii.txt", &nrMelodii);
//
//    if (!vector) {
//        return -1;
//    }
//
//    Melodie** matrice = NULL;
//    int* dimLinii = NULL;
//    int nrLinii = 0;
//
//    deepCopyInMatrice(vector, nrMelodii, &matrice, &dimLinii, &nrLinii);
//
//    printf("Matrice nesortata:\n");
//    afisareMatrice(matrice, dimLinii, nrLinii);
//
//    sortareLinii(&matrice, &dimLinii, nrLinii);
//
//    printf("\nMatrice sortata dupa numarul de melodii pe linie:\n");
//    afisareMatrice(matrice, dimLinii, nrLinii);
//
//    dezalocareVector(&vector, &nrMelodii);
//    dezalocareMatrice(&matrice, &dimLinii, nrLinii);
//
//    return 0;
//}
