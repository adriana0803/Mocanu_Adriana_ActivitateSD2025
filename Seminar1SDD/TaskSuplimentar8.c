//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//    int id;
//    int anConstructie;
//    char* nume;
//    int nrRenovari;
//    int* anulRenovarii;
//} Cladire;
//
//typedef struct Node {
//    Cladire info;
//    struct Node* next;
//} Node;
//
//typedef struct {
//    int dim;
//    Node** tabela;
//} HashTable;
//
//int hash(int an, int dim) {
//    return an % dim;
//}
//
//HashTable initializareHashTable(int dim) {
//    HashTable ht;
//    ht.dim = dim;
//    ht.tabela = (Node**)malloc(sizeof(Node*) * dim);
//    for (int i = 0; i < dim; i++) ht.tabela[i] = NULL;
//    return ht;
//}
//
//Cladire citireCladire(FILE* f) {
//    Cladire c;
//    char buffer[256];
//    fgets(buffer, 256, f);
//    char* token = strtok(buffer, ",\n");
//    c.id = atoi(token);
//
//    token = strtok(NULL, ",\n");
//    c.anConstructie = atoi(token);
//
//    token = strtok(NULL, ",\n");
//    c.nume = malloc(strlen(token) + 1);
//    strcpy(c.nume, token);
//
//    token = strtok(NULL, ",\n");
//    c.nrRenovari = atoi(token);
//
//    c.anulRenovarii = NULL;
//    if (c.nrRenovari > 0) {
//        c.anulRenovarii = malloc(sizeof(int) * c.nrRenovari);
//        for (int i = 0; i < c.nrRenovari; i++) {
//            token = strtok(NULL, ",\n");
//            c.anulRenovarii[i] = atoi(token);
//        }
//    }
//    return c;
//}
//
//void inserare(HashTable* ht, Cladire c) {
//    int index = hash(c.anConstructie, ht->dim);
//    Node* nou = malloc(sizeof(Node));
//    nou->info = c;
//    nou->next = ht->tabela[index];
//    ht->tabela[index] = nou;
//}
//
//void afisareCladire(Cladire c) {
//    printf("ID: %d, An: %d, Nume: %s, Renovari: %d\n", c.id, c.anConstructie, c.nume, c.nrRenovari);
//    for (int i = 0; i < c.nrRenovari; i++) {
//        printf("  - %d\n", c.anulRenovarii[i]);
//    }
//}
//
//void afisareCluster(HashTable ht, int an) {
//    int index = hash(an, ht.dim);
//    Node* p = ht.tabela[index];
//    while (p) {
//        if (p->info.anConstructie == an)
//            afisareCladire(p->info);
//        p = p->next;
//    }
//}
//
//void stergereIdAn(HashTable* ht, int id, int an) {
//    int index = hash(an, ht->dim);
//    Node* p = ht->tabela[index], * prev = NULL;
//    while (p) {
//        if (p->info.id == id && p->info.anConstructie == an) {
//            if (prev) prev->next = p->next;
//            else ht->tabela[index] = p->next;
//            free(p->info.nume);
//            free(p->info.anulRenovarii);
//            free(p);
//            return;
//        }
//        prev = p;
//        p = p->next;
//    }
//}
//
//void stergereId(HashTable* ht, int id) {
//    for (int i = 0; i < ht->dim; i++) {
//        Node* p = ht->tabela[i], * prev = NULL;
//        while (p) {
//            if (p->info.id == id) {
//                if (prev) prev->next = p->next;
//                else ht->tabela[i] = p->next;
//                free(p->info.nume);
//                free(p->info.anulRenovarii);
//                free(p);
//                return;
//            }
//            prev = p;
//            p = p->next;
//        }
//    }
//}
//
//Cladire* getCladiriDinAn(HashTable ht, int an, int* count) {
//    int index = hash(an, ht.dim);
//    Node* p = ht.tabela[index];
//    *count = 0;
//    for (Node* q = p; q; q = q->next)
//        if (q->info.anConstructie == an) (*count)++;
//
//    Cladire* vector = malloc(sizeof(Cladire) * (*count));
//    int j = 0;
//    while (p) {
//        if (p->info.anConstructie == an) {
//            vector[j].id = p->info.id;
//            vector[j].anConstructie = p->info.anConstructie;
//            vector[j].nume = strdup(p->info.nume);
//            vector[j].nrRenovari = p->info.nrRenovari;
//            if (p->info.nrRenovari > 0) {
//                vector[j].anulRenovarii = malloc(sizeof(int) * p->info.nrRenovari);
//                memcpy(vector[j].anulRenovarii, p->info.anulRenovarii, sizeof(int) * p->info.nrRenovari);
//            }
//            else {
//                vector[j].anulRenovarii = NULL;
//            }
//            j++;
//        }
//        p = p->next;
//    }
//    return vector;
//}
//
//void modificaAnCladire(HashTable* ht, int id, int vechiAn, int nouAn) {
//    int index = hash(vechiAn, ht->dim);
//    Node* p = ht->tabela[index], * prev = NULL;
//    while (p) {
//        if (p->info.id == id) {
//            if (prev) prev->next = p->next;
//            else ht->tabela[index] = p->next;
//            p->info.anConstructie = nouAn;
//            inserare(ht, p->info);
//            free(p);
//            return;
//        }
//        prev = p;
//        p = p->next;
//    }
//}
//
//void dezalocare(HashTable* ht) {
//    for (int i = 0; i < ht->dim; i++) {
//        Node* p = ht->tabela[i];
//        while (p) {
//            Node* temp = p;
//            p = p->next;
//            free(temp->info.nume);
//            free(temp->info.anulRenovarii);
//            free(temp);
//        }
//    }
//    free(ht->tabela);
//}
//
//int main() {
//    HashTable ht = initializareHashTable(7);
//    FILE* f = fopen("cladiri.txt", "r");
//    if (!f) return -1;
//    while (!feof(f)) {
//        Cladire c = citireCladire(f);
//        inserare(&ht, c);
//    }
//    fclose(f);
//
//    printf("Cladiri din anul 2005:\n");
//    afisareCluster(ht, 2005);
//
//    printf("\nStergem cladirea cu ID 5 si an 1967:\n");
//    stergereIdAn(&ht, 5, 1967);
//    afisareCluster(ht, 1967);
//
//    printf("\nModificam anul construirii pentru ID 4 din 2012 in 2020:\n");
//    modificaAnCladire(&ht, 4, 2012, 2020);
//    afisareCluster(ht, 2020);
//
//    int count;
//    Cladire* vec = getCladiriDinAn(ht, 1998, &count);
//    printf("\nCladiri deep copy din 1998:\n");
//    for (int i = 0; i < count; i++) {
//        afisareCladire(vec[i]);
//        free(vec[i].nume);
//        free(vec[i].anulRenovarii);
//    }
//    free(vec);
//
//    dezalocare(&ht);
//    return 0;
//}
