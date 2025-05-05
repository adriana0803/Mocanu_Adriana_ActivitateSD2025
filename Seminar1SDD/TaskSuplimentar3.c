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
//    printf("Id: %d\nTitlu: %s\nArtist: %s\nDurata: %.2f minute\nNumar recenzii: %d\n",
//        m.id, m.titlu, m.artist, m.durata, m.nrRecenzii);
//    if (m.nrRecenzii > 0) {
//        printf("Note: ");
//        for (int i = 0; i < m.nrRecenzii; i++) {
//            printf("%.2f ", m.note[i]);
//        }
//        printf("\n");
//    }
//    else {
//        printf("Nu exista recenzii.\n");
//    }
//}
//
//void afisareVectorMelodii(Melodie* melodii, int nrMelodii) {
//    for (int i = 0; i < nrMelodii; i++) {
//        afisareMelodie(melodii[i]);
//    }
//}
//
//void adaugareMelodieInVector(Melodie** melodii, int* nrMelodii, Melodie mNoua) {
//    Melodie* aux = (Melodie*)malloc(sizeof(Melodie) * (*nrMelodii + 1));
//    if (*melodii) {
//        for (int i = 0; i < *nrMelodii; i++) {
//            aux[i] = (*melodii)[i];
//        }
//        free(*melodii);
//    }
//    aux[*nrMelodii] = mNoua;
//    *melodii = aux;
//    (*nrMelodii)++;
//}
//
//Melodie citireMelodie(FILE* file) {
//    char buffer[256];
//    char sep[] = ",\n";
//    char* token;
//
//    if (!fgets(buffer, sizeof(buffer), file)) {
//        return (Melodie) { 0 };
//    }
//
//    Melodie m;
//
//    token = strtok(buffer, sep);
//    m.id = atoi(token);
//
//    token = strtok(NULL, sep);
//    m.titlu = malloc(strlen(token) + 1);
//    strcpy(m.titlu, token);
//
//    token = strtok(NULL, sep);
//    m.artist = malloc(strlen(token) + 1);
//    strcpy(m.artist, token);
//
//    token = strtok(NULL, sep);
//    m.durata = atof(token);
//
//    token = strtok(NULL, sep);
//    m.nrRecenzii = atoi(token);
//
//    m.note = NULL;
//    if (m.nrRecenzii > 0) {
//        m.note = (float*)malloc(sizeof(float) * m.nrRecenzii);
//        for (int i = 0; i < m.nrRecenzii; i++) {
//            token = strtok(NULL, sep);
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
//        printf("Eroare la deschiderea fisierului!\n");
//        return NULL;
//    }
//
//    Melodie* melodii = NULL;
//    Melodie m;
//    while ((m = citireMelodie(f)).titlu != NULL) {
//        adaugareMelodieInVector(&melodii, nrMelodii, m);
//    }
//
//    fclose(f);
//    return melodii;
//}
//
//void salvareMelodieInFisier(Melodie m, const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "a");
//    if (!f) {
//        printf("Eroare la deschiderea fisierului de salvare!\n");
//        return;
//    }
//
//    fprintf(f, "%d, %s, %s, %.2f, %d", m.id, m.titlu, m.artist, m.durata, m.nrRecenzii);
//    for (int i = 0; i < m.nrRecenzii; i++) {
//        fprintf(f, ", %.2f", m.note[i]);
//    }
//    fprintf(f, "\n");
//    fclose(f);
//}
//
//void salvareVectorMelodiiInFisier(Melodie* melodii, int nrMelodii, const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "w");
//    if (!f) {
//        printf("Eroare la deschiderea fisierului de scriere vector!\n");
//        return;
//    }
//
//    for (int i = 0; i < nrMelodii; i++) {
//        fprintf(f, "%d, %s, %s, %.2f, %d", melodii[i].id, melodii[i].titlu, melodii[i].artist, melodii[i].durata, melodii[i].nrRecenzii);
//        for (int j = 0; j < melodii[i].nrRecenzii; j++) {
//            fprintf(f, ", %.2f", melodii[i].note[j]);
//        }
//        fprintf(f, "\n");
//    }
//
//    fclose(f);
//}
//
//void dezalocareMelodii(Melodie** melodii, int* nrMelodii) {
//    for (int i = 0; i < *nrMelodii; i++) {
//        free((*melodii)[i].titlu);
//        free((*melodii)[i].artist);
//        free((*melodii)[i].note);
//    }
//    free(*melodii);
//    *melodii = NULL;
//    *nrMelodii = 0;
//}
//
//int main() {
//    int nrMelodii = 0;
//    Melodie* melodii = citireVectorMelodii("melodii.txt", &nrMelodii);
//
//    if (melodii) {
//        salvareMelodieInFisier(melodii[0], "melodie_singura.txt");
//        salvareVectorMelodiiInFisier(melodii, nrMelodii, "melodii_vector.txt");
//
//        afisareVectorMelodii(melodii, nrMelodii);
//        dezalocareMelodii(&melodii, &nrMelodii);
//    }
//
//    return 0;
//}
