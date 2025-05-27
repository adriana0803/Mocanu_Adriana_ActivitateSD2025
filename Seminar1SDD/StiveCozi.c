//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//    int id;
//    int nrUsi;
//    float pret;
//    char* model;
//    char* numeSofer;
//    unsigned char serie;
//} Masina;
//
//Masina citireMasinaDinFisier(FILE* file) {
//    char buffer[100];
//    char sep[3] = ",\n";
//    if (!fgets(buffer, sizeof(buffer), file))
//        return (Masina) { 0 };
//
//    Masina m;
//    char* aux = strtok(buffer, sep);
//    m.id = atoi(aux);
//    m.nrUsi = atoi(strtok(NULL, sep));
//    m.pret = atof(strtok(NULL, sep));
//
//    aux = strtok(NULL, sep);
//    m.model = malloc(strlen(aux) + 1);
//    strcpy(m.model, aux);
//
//    aux = strtok(NULL, sep);
//    m.numeSofer = malloc(strlen(aux) + 1);
//    strcpy(m.numeSofer, aux);
//
//    m.serie = *strtok(NULL, sep);
//
//    return m;
//}
//
//void afisareMasina(Masina m) {
//    printf("Id: %d | Usi: %d | Pret: %.2f | Model: %s | Sofer: %s | Serie: %c\n",
//        m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
//}
//
//void dezalocaMasina(Masina* m) {
//    free(m->model);
//    free(m->numeSofer);
//}
//
//// ---------------------------- STIVA -----------------------------
//
//typedef struct NodStiva {
//    Masina info;
//    struct NodStiva* next;
//} NodStiva;
//
//void pushStack(NodStiva** varf, Masina masina) {
//    NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
//    nou->info = masina;
//    nou->next = *varf;
//    *varf = nou;
//}
//
//int emptyStack(NodStiva* varf) {
//    return varf == NULL;
//}
//
//Masina popStack(NodStiva** varf) {
//    if (*varf == NULL) return (Masina) { 0 };
//    Masina m = (*varf)->info;
//    NodStiva* temp = *varf;
//    *varf = (*varf)->next;
//    free(temp);
//    return m;
//}
//
//int sizeStack(NodStiva* varf) {
//    int count = 0;
//    while (varf) {
//        count++;
//        varf = varf->next;
//    }
//    return count;
//}
//
//NodStiva* citireStackMasiniDinFisier(const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "r");
//    if (!f) {
//        perror("Fisier inexistent");
//        return NULL;
//    }
//
//    NodStiva* stiva = NULL;
//    while (!feof(f)) {
//        Masina m = citireMasinaDinFisier(f);
//        if (m.model)
//            pushStack(&stiva, m);
//    }
//    fclose(f);
//    return stiva;
//}
//
//void dezalocareStivaDeMasini(NodStiva** varf) {
//    while (*varf) {
//        dezalocaMasina(&(*varf)->info);
//        NodStiva* temp = *varf;
//        *varf = (*varf)->next;
//        free(temp);
//    }
//}
//
//// ---------------------------- COADA -----------------------------
//
//typedef struct NodCoada {
//    Masina info;
//    struct NodCoada* next;
//} NodCoada;
//
//typedef struct {
//    NodCoada* prim;
//    NodCoada* ultim;
//} Coada;
//
//void enqueue(Coada* c, Masina masina) {
//    NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
//    nou->info = masina;
//    nou->next = NULL;
//    if (!c->prim)
//        c->prim = c->ultim = nou;
//    else {
//        c->ultim->next = nou;
//        c->ultim = nou;
//    }
//}
//
//int emptyQueue(Coada* c) {
//    return c->prim == NULL;
//}
//
//Masina dequeue(Coada* c) {
//    if (!c->prim) return (Masina) { 0 };
//    NodCoada* temp = c->prim;
//    Masina m = temp->info;
//    c->prim = c->prim->next;
//    if (!c->prim) c->ultim = NULL;
//    free(temp);
//    return m;
//}
//
//int sizeQueue(Coada* c) {
//    int count = 0;
//    NodCoada* p = c->prim;
//    while (p) {
//        count++;
//        p = p->next;
//    }
//    return count;
//}
//
//Coada citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//    FILE* f = fopen(numeFisier, "r");
//    Coada c = { NULL, NULL };
//    if (!f) {
//        perror("Fisier inexistent");
//        return c;
//    }
//
//    while (!feof(f)) {
//        Masina m = citireMasinaDinFisier(f);
//        if (m.model)
//            enqueue(&c, m);
//    }
//    fclose(f);
//    return c;
//}
//
//void dezalocareCoadaDeMasini(Coada* c) {
//    while (!emptyQueue(c)) {
//        Masina m = dequeue(c);
//        dezalocaMasina(&m);
//    }
//}
//
//
//int main() {
//    // Test cu stiva
//    printf("--- Stiva ---\n");
//    NodStiva* stiva = citireStackMasiniDinFisier("masini.txt");
//    NodStiva* tmp = stiva;
//    while (tmp) {
//        afisareMasina(tmp->info);
//        tmp = tmp->next;
//    }
//    dezalocareStivaDeMasini(&stiva);
//
//    // Test cu coada
//    printf("\n--- Coada ---\n");
//    Coada c = citireCoadaDeMasiniDinFisier("masini.txt");
//    NodCoada* q = c.prim;
//    while (q) {
//        afisareMasina(q->info);
//        q = q->next;
//    }
//    dezalocareCoadaDeMasini(&c);
//
//    return 0;
//}