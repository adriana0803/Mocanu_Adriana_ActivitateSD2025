//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Masina {
//    int id;
//    int nrUsi;
//    float pret;
//    char* model;
//    char* numeSofer;
//    unsigned char serie;
//};
//
//typedef struct Masina Masina;
//
//typedef struct Nod {
//    Masina info;
//    struct Nod* st;
//    struct Nod* dr;
//} Nod;
//
//Masina citireMasinaDinFisier(FILE* file) {
//    char buffer[128];
//    char* aux;
//    fgets(buffer, 128, file);
//    char sep[] = ",\n";
//    Masina m;
//    aux = strtok(buffer, sep);
//    m.id = atoi(aux);
//    m.nrUsi = atoi(strtok(NULL, sep));
//    m.pret = atof(strtok(NULL, sep));
//    aux = strtok(NULL, sep);
//    m.model = malloc(strlen(aux) + 1);
//    strcpy(m.model, aux);
//    aux = strtok(NULL, sep);
//    m.numeSofer = malloc(strlen(aux) + 1);
//    strcpy(m.numeSofer, aux);
//    m.serie = *strtok(NULL, sep);
//    return m;
//}
//
//void afisareMasina(Masina m) {
//    printf("ID: %d, Nr usi: %d, Pret: %.2f, Model: %s, Sofer: %s, Serie: %c\n",
//        m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
//}
//
//Nod* adaugaMasina(Nod* rad, Masina m) {
//    if (!rad) {
//        Nod* nou = malloc(sizeof(Nod));
//        nou->info = m;
//        nou->st = nou->dr = NULL;
//        return nou;
//    }
//    if (m.id < rad->info.id)
//        rad->st = adaugaMasina(rad->st, m);
//    else if (m.id > rad->info.id)
//        rad->dr = adaugaMasina(rad->dr, m);
//    return rad;
//}
//
//Nod* citireArbore(const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "r");
//    Nod* rad = NULL;
//    while (!feof(f)) {
//        Masina m = citireMasinaDinFisier(f);
//        rad = adaugaMasina(rad, m);
//    }
//    fclose(f);
//    return rad;
//}
//
//void afisareInOrdine(Nod* rad) {
//    if (rad) {
//        afisareInOrdine(rad->st);
//        afisareMasina(rad->info);
//        afisareInOrdine(rad->dr);
//    }
//}
//
//void dezalocare(Nod** rad) {
//    if (*rad) {
//        dezalocare(&(*rad)->st);
//        dezalocare(&(*rad)->dr);
//        free((*rad)->info.model);
//        free((*rad)->info.numeSofer);
//        free(*rad);
//        *rad = NULL;
//    }
//}
//
//int inaltime(Nod* rad) {
//    if (!rad) return 0;
//    int st = inaltime(rad->st);
//    int dr = inaltime(rad->dr);
//    return 1 + (st > dr ? st : dr);
//}
//
//Nod* subarboreMaiInalt(Nod* rad) {
//    if (!rad) return NULL;
//    return inaltime(rad->st) >= inaltime(rad->dr) ? rad->st : rad->dr;
//}
//
//int numarNoduri(Nod* rad) {
//    if (!rad) return 0;
//    return 1 + numarNoduri(rad->st) + numarNoduri(rad->dr);
//}
//
//int numarSubordonati(Nod* rad, int id) {
//    if (!rad) return 0;
//    if (id < rad->info.id)
//        return numarSubordonati(rad->st, id);
//    else if (id > rad->info.id)
//        return numarSubordonati(rad->dr, id);
//    else
//        return numarNoduri(rad) - 1;
//}
//
//Nod* subarboreCuMaiMultiDescendenti(Nod* rad) {
//    if (!rad) return NULL;
//    return numarNoduri(rad->st) >= numarNoduri(rad->dr) ? rad->st : rad->dr;
//}
//
//Nod* minim(Nod* rad) {
//    while (rad && rad->st) rad = rad->st;
//    return rad;
//}
//
//Nod* stergeNod(Nod* rad, int id) {
//    if (!rad) return NULL;
//    if (id < rad->info.id)
//        rad->st = stergeNod(rad->st, id);
//    else if (id > rad->info.id)
//        rad->dr = stergeNod(rad->dr, id);
//    else {
//        if (!rad->st) {
//            Nod* temp = rad->dr;
//            free(rad->info.model);
//            free(rad->info.numeSofer);
//            free(rad);
//            return temp;
//        }
//        else if (!rad->dr) {
//            Nod* temp = rad->st;
//            free(rad->info.model);
//            free(rad->info.numeSofer);
//            free(rad);
//            return temp;
//        }
//        Nod* succ = minim(rad->dr);
//        free(rad->info.model);
//        free(rad->info.numeSofer);
//        rad->info = succ->info;
//        rad->dr = stergeNod(rad->dr, succ->info.id);
//    }
//    return rad;
//}
//
//int main() {
//    Nod* arbore = citireArbore("masini.txt");
//
//    printf("--- Afisare inordine ---\n");
//    afisareInOrdine(arbore);
//
//    int idStergere = 2;
//    printf("\n--- Stergere nod cu ID %d ---\n", idStergere);
//    arbore = stergeNod(arbore, idStergere);
//    afisareInOrdine(arbore);
//
//    Nod* inalt = subarboreMaiInalt(arbore);
//    printf("\n--- Subarbore cu inaltime mai mare ---\n");
//    afisareInOrdine(inalt);
//
//    int idCautat = 3;
//    int nrSub = numarSubordonati(arbore, idCautat);
//    printf("\n--- Nr noduri subordonate pentru ID %d: %d ---\n", idCautat, nrSub);
//
//    Nod* subarboreMaxNoduri = subarboreCuMaiMultiDescendenti(arbore);
//    printf("\n--- Subarbore cu mai multi descendenti ---\n");
//    afisareInOrdine(subarboreMaxNoduri);
//
//    dezalocare(&arbore);
//    return 0;
//}
