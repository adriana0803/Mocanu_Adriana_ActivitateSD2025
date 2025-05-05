//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Muzica {
//    int cod;
//    char* titluMelodie;
//    char* artist;
//    float durataMin;
//    int nrRecenzii;
//    float* evaluari;
//} Muzica;
//
//Muzica initializare(int cod, const char* titlu, const char* artist, float durata, int nrRecenzii, float* evaluari) {
//    Muzica m;
//    m.cod = cod;
//
//    m.titluMelodie = (char*)malloc(strlen(titlu) + 1);
//    strcpy(m.titluMelodie, titlu);
//
//    m.artist = (char*)malloc(strlen(artist) + 1);
//    strcpy(m.artist, artist);
//
//    m.durataMin = durata;
//    m.nrRecenzii = nrRecenzii;
//
//    m.evaluari = (float*)malloc(nrRecenzii * sizeof(float));
//    for (int i = 0; i < nrRecenzii; i++) {
//        m.evaluari[i] = evaluari[i];
//    }
//
//    return m;
//}
//
//void afisareMelodie(Muzica m) {
//    printf("\nCod: %d\nTitlu: %s\nArtist: %s\nDurata: %.2f\nRecenzii: %d\nEvaluari: ",
//        m.cod, m.titluMelodie, m.artist, m.durataMin, m.nrRecenzii);
//    for (int i = 0; i < m.nrRecenzii; i++) {
//        printf("%.1f ", m.evaluari[i]);
//    }
//    printf("\n");
//}
//
//float mediaEvaluari(float* evaluari, int nr) {
//    if (nr == 0) return 0;
//    float suma = 0;
//    for (int i = 0; i < nr; i++) suma += evaluari[i];
//    return suma / nr;
//}
//
//void afisareVector(Muzica* melodii, int dim) {
//    for (int i = 0; i < dim; i++) {
//        afisareMelodie(melodii[i]);
//    }
//}
//
//void copiazaMelodiiMediePeste(Muzica* melodii, int dim, float prag, Muzica** nou, int* nouDim) {
//    *nouDim = 0;
//    for (int i = 0; i < dim; i++) {
//        if (mediaEvaluari(melodii[i].evaluari, melodii[i].nrRecenzii) > prag) {
//            (*nouDim)++;
//        }
//    }
//
//    *nou = (Muzica*)malloc(*nouDim * sizeof(Muzica));
//    int k = 0;
//    for (int i = 0; i < dim; i++) {
//        if (mediaEvaluari(melodii[i].evaluari, melodii[i].nrRecenzii) > prag) {
//            (*nou)[k++] = initializare(melodii[i].cod, melodii[i].titluMelodie,
//                melodii[i].artist, melodii[i].durataMin, melodii[i].nrRecenzii, melodii[i].evaluari);
//        }
//    }
//}
//
//void mutaMelodiiDurataPeste(Muzica** melodii, int* dim, float prag, Muzica** nou, int* nouDim) {
//    *nouDim = 0;
//    *nou = NULL;
//
//    for (int i = 0; i < *dim; i++) {
//        if ((*melodii)[i].durataMin > prag) {
//            *nou = (Muzica*)realloc(*nou, (*nouDim + 1) * sizeof(Muzica));
//            (*nou)[*nouDim] = (*melodii)[i];
//            (*nouDim)++;
//
//            for (int j = i; j < *dim - 1; j++) {
//                (*melodii)[j] = (*melodii)[j + 1];
//            }
//            (*dim)--;
//            i--;
//        }
//    }
//}
//
//Muzica* concateneazaVectori(Muzica* v1, int n1, Muzica* v2, int n2, int* dimNoua) {
//    *dimNoua = n1 + n2;
//    Muzica* rezultat = (Muzica*)malloc((*dimNoua) * sizeof(Muzica));
//
//    for (int i = 0; i < n1; i++) {
//        rezultat[i] = initializare(v1[i].cod, v1[i].titluMelodie, v1[i].artist,
//            v1[i].durataMin, v1[i].nrRecenzii, v1[i].evaluari);
//    }
//    for (int i = 0; i < n2; i++) {
//        rezultat[n1 + i] = initializare(v2[i].cod, v2[i].titluMelodie, v2[i].artist,
//            v2[i].durataMin, v2[i].nrRecenzii, v2[i].evaluari);
//    }
//    return rezultat;
//}
//
//int main() {
//    int nrMelodii = 5;
//    Muzica* melodii = (Muzica*)malloc(nrMelodii * sizeof(Muzica));
//
//    melodii[0] = initializare(1, "Shape of You", "Ed Sheeran", 4.2, 3, (float[]) { 8.5, 9.0, 7.0 });
//    melodii[1] = initializare(2, "In the End", "Linkin Park", 3.5, 4, (float[]) { 9.5, 9.0, 9.0, 10 });
//    melodii[2] = initializare(3, "Thunder", "Imagine Dragons", 3.2, 2, (float[]) { 6.0, 6.5 });
//    melodii[3] = initializare(4, "Perfect", "Ed Sheeran", 4.0, 3, (float[]) { 9.5, 10, 9.0 });
//    melodii[4] = initializare(5, "Happy", "Pharrell", 3.8, 3, (float[]) { 6.5, 7.0, 7.5 });
//
//    printf("Melodii initiale:\n");
//    afisareVector(melodii, nrMelodii);
//
//    Muzica* melodiiMedieMare = NULL;
//    int nrMelodiiMedie = 0;
//    copiazaMelodiiMediePeste(melodii, nrMelodii, 8.0, &melodiiMedieMare, &nrMelodiiMedie);
//    printf("\nMelodii cu medie peste 8.0:\n");
//    afisareVector(melodiiMedieMare, nrMelodiiMedie);
//
//    Muzica* melodiiDurataMare = NULL;
//    int nrMelodiiDurata = 0;
//    mutaMelodiiDurataPeste(&melodii, &nrMelodii, 3.9, &melodiiDurataMare, &nrMelodiiDurata);
//    printf("\nMelodii mutate cu durata > 3.9 minute:\n");
//    afisareVector(melodiiDurataMare, nrMelodiiDurata);
//
//    int dimConcat = 0;
//    Muzica* melodiiConcat = concateneazaVectori(melodiiMedieMare, nrMelodiiMedie, melodiiDurataMare, nrMelodiiDurata, &dimConcat);
//    printf("\nVector concatenat:\n");
//    afisareVector(melodiiConcat, dimConcat);
//
//    return 0;
//}
