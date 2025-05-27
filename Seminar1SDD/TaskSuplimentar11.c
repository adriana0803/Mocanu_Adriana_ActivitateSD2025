//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// Structura Student
//typedef struct {
//    int id;
//    char* nume;
//    int an;
//} Student;
//
//// Nod AVL
//typedef struct Node {
//    Student info;
//    struct Node* st;
//    struct Node* dr;
//    int gradEchilibru;
//} Node;
//
//// Lista simplu înlănțuită
//typedef struct NodLista {
//    Student info;
//    struct NodLista* next;
//} NodLista;
//
//Student citireStudentFisier(FILE* file) {
//    char buffer[100];
//    fgets(buffer, 100, file);
//    char* token = strtok(buffer, ",\n");
//    Student s;
//    s.id = atoi(token);
//    token = strtok(NULL, ",\n");
//    s.nume = strdup(token);
//    token = strtok(NULL, ",\n");
//    s.an = atoi(token);
//    return s;
//}
//
//void afiseazaStudent(Student s) {
//    printf("Id: %d, Nume: %s, An: %d\n", s.id, s.nume, s.an);
//}
//
//Node* rotireLaDreapta(Node* y) {
//    Node* x = y->st;
//    Node* T2 = x->dr;
//    x->dr = y;
//    y->st = T2;
//    return x;
//}
//
//Node* rotireLaStanga(Node* x) {
//    Node* y = x->dr;
//    Node* T2 = y->st;
//    y->st = x;
//    x->dr = T2;
//    return y;
//}
//
//int inaltime(Node* n) {
//    if (!n) return 0;
//    int st = inaltime(n->st);
//    int dr = inaltime(n->dr);
//    return 1 + (st > dr ? st : dr);
//}
//
//int getBalance(Node* n) {
//    if (!n) return 0;
//    return inaltime(n->st) - inaltime(n->dr);
//}
//
//Node* inserareAVL(Node* rad, Student s) {
//    if (!rad) {
//        Node* nou = malloc(sizeof(Node));
//        nou->info = s;
//        nou->st = nou->dr = NULL;
//        nou->gradEchilibru = 0;
//        return nou;
//    }
//    if (s.id < rad->info.id)
//        rad->st = inserareAVL(rad->st, s);
//    else if (s.id > rad->info.id)
//        rad->dr = inserareAVL(rad->dr, s);
//    else
//        return rad;
//
//    rad->gradEchilibru = getBalance(rad);
//
//    if (rad->gradEchilibru > 1 && s.id < rad->st->info.id)
//        return rotireLaDreapta(rad);
//    if (rad->gradEchilibru < -1 && s.id > rad->dr->info.id)
//        return rotireLaStanga(rad);
//    if (rad->gradEchilibru > 1 && s.id > rad->st->info.id) {
//        rad->st = rotireLaStanga(rad->st);
//        return rotireLaDreapta(rad);
//    }
//    if (rad->gradEchilibru < -1 && s.id < rad->dr->info.id) {
//        rad->dr = rotireLaDreapta(rad->dr);
//        return rotireLaStanga(rad);
//    }
//    return rad;
//}
//
//Student cautaStudent(Node* rad, int id) {
//    if (!rad) return (Student) { -1, NULL, 0 };
//    if (id == rad->info.id) return rad->info;
//    if (id < rad->info.id) return cautaStudent(rad->st, id);
//    return cautaStudent(rad->dr, id);
//}
//
//void parcurgereInOrdine(Node* rad, Student* vect, int* i) {
//    if (rad) {
//        parcurgereInOrdine(rad->st, vect, i);
//        vect[*i] = rad->info;
//        (*i)++;
//        parcurgereInOrdine(rad->dr, vect, i);
//    }
//}
//
//void parcurgerePreOrdine(Node* rad, Student* vect, int* i) {
//    if (rad) {
//        vect[*i] = rad->info;
//        (*i)++;
//        parcurgerePreOrdine(rad->st, vect, i);
//        parcurgerePreOrdine(rad->dr, vect, i);
//    }
//}
//
//void parcurgerePostOrdine(Node* rad, Student* vect, int* i) {
//    if (rad) {
//        parcurgerePostOrdine(rad->st, vect, i);
//        parcurgerePostOrdine(rad->dr, vect, i);
//        vect[*i] = rad->info;
//        (*i)++;
//    }
//}
//
//void inserareInLista(NodLista** cap, Student s) {
//    NodLista* nou = malloc(sizeof(NodLista));
//    nou->info = s;
//    nou->next = NULL;
//    if (!*cap) *cap = nou;
//    else {
//        NodLista* temp = *cap;
//        while (temp->next) temp = temp->next;
//        temp->next = nou;
//    }
//}
//
//void listaInOrdine(Node* rad, NodLista** cap) {
//    if (rad) {
//        listaInOrdine(rad->st, cap);
//        inserareInLista(cap, rad->info);
//        listaInOrdine(rad->dr, cap);
//    }
//}
//
//void afiseazaLista(NodLista* cap) {
//    while (cap) {
//        afiseazaStudent(cap->info);
//        cap = cap->next;
//    }
//}
//
//void dezalocareAVL(Node** rad) {
//    if (*rad) {
//        dezalocareAVL(&(*rad)->st);
//        dezalocareAVL(&(*rad)->dr);
//        free((*rad)->info.nume);
//        free(*rad);
//        *rad = NULL;
//    }
//}
//
//int numarNoduri(Node* rad) {
//    if (!rad) return 0;
//    return 1 + numarNoduri(rad->st) + numarNoduri(rad->dr);
//}
//
//int main() {
//    Node* rad = NULL;
//    FILE* f = fopen("studenti.txt", "r");
//    while (!feof(f)) {
//        Student s = citireStudentFisier(f);
//        rad = inserareAVL(rad, s);
//    }
//    fclose(f);
//
//    printf("--- Inordine ---\n");
//    int nr = numarNoduri(rad);
//    Student* vect = malloc(sizeof(Student) * nr);
//    int i = 0;
//    parcurgereInOrdine(rad, vect, &i);
//    for (int j = 0; j < nr; j++) afiseazaStudent(vect[j]);
//    free(vect);
//
//    printf("\n--- Lista simpla in inordine ---\n");
//    NodLista* lista = NULL;
//    listaInOrdine(rad, &lista);
//    afiseazaLista(lista);
//
//    dezalocareAVL(&rad);
//    return 0;
//}