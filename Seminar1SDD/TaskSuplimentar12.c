//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//    int id;
//    char* nume;
//    char serie;
//    int nrNote;
//    float* note;
//} Student;
//
//Student citireStudent(FILE* f) {
//    char buffer[256];
//    fgets(buffer, sizeof(buffer), f);
//    if (strlen(buffer) < 3) return (Student) { 0 };
//
//    Student s;
//    char* token = strtok(buffer, ",\n");
//    s.id = atoi(token);
//
//    token = strtok(NULL, ",\n");
//    s.nume = strdup(token);
//
//    token = strtok(NULL, ",\n");
//    s.serie = token[0];
//
//    token = strtok(NULL, ",\n");
//    s.nrNote = atoi(token);
//
//    s.note = malloc(sizeof(float) * s.nrNote);
//    for (int i = 0; i < s.nrNote; i++) {
//        token = strtok(NULL, ",\n");
//        s.note[i] = atof(token);
//    }
//    return s;
//}
//
//void afiseazaStudent(Student s) {
//    printf("Id: %d, Nume: %s, Serie: %c, Note: ", s.id, s.nume, s.serie);
//    for (int i = 0; i < s.nrNote; i++) {
//        printf("%.1f ", s.note[i]);
//    }
//    printf("\n");
//}
//
//#define MAX_STACK 100
//Student stackVector[MAX_STACK];
//int top = -1;
//
//void pushVector(Student s) {
//    if (top < MAX_STACK - 1) {
//        stackVector[++top] = s;
//    }
//}
//
//Student popVector() {
//    if (top >= 0) {
//        return stackVector[top--];
//    }
//    return (Student) { 0 };
//}
//
//void afiseazaStackVector() {
//    for (int i = top; i >= 0; i--) {
//        afiseazaStudent(stackVector[i]);
//    }
//}
//
//typedef struct NodeS {
//    Student info;
//    struct NodeS* next;
//} NodeS;
//
//void pushList(NodeS** stiva, Student s) {
//    NodeS* nou = malloc(sizeof(NodeS));
//    nou->info = s;
//    nou->next = *stiva;
//    *stiva = nou;
//}
//
//Student popList(NodeS** stiva) {
//    Student s = { 0 };
//    if (*stiva) {
//        NodeS* temp = *stiva;
//        s = temp->info;
//        *stiva = temp->next;
//        free(temp);
//    }
//    return s;
//}
//
//typedef struct NodeDubluS {
//    Student info;
//    struct NodeDubluS* next;
//    struct NodeDubluS* prev;
//} NodeDubluS;
//
//NodeDubluS* topDouble = NULL;
//
//void pushDouble(Student s) {
//    NodeDubluS* nou = malloc(sizeof(NodeDubluS));
//    nou->info = s;
//    nou->prev = NULL;
//    nou->next = topDouble;
//    if (topDouble) topDouble->prev = nou;
//    topDouble = nou;
//}
//
//Student popDouble() {
//    Student s = { 0 };
//    if (topDouble) {
//        s = topDouble->info;
//        NodeDubluS* temp = topDouble;
//        topDouble = topDouble->next;
//        if (topDouble) topDouble->prev = NULL;
//        free(temp);
//    }
//    return s;
//}
//
//#define MAX_QUEUE 100
//Student queueVector[MAX_QUEUE];
//int front = 0, rear = 0;
//
//void enqueueVector(Student s) {
//    if (rear < MAX_QUEUE) {
//        queueVector[rear++] = s;
//    }
//}
//
//Student dequeueVector() {
//    if (front < rear) {
//        return queueVector[front++];
//    }
//    return (Student) { 0 };
//}
//
//typedef struct NodeQ {
//    Student info;
//    struct NodeQ* next;
//} NodeQ;
//
//typedef struct {
//    NodeQ* front;
//    NodeQ* rear;
//} Queue;
//
//void enqueueList(Queue* q, Student s) {
//    NodeQ* nou = malloc(sizeof(NodeQ));
//    nou->info = s;
//    nou->next = NULL;
//    if (!q->rear) q->front = q->rear = nou;
//    else {
//        q->rear->next = nou;
//        q->rear = nou;
//    }
//}
//
//Student dequeueList(Queue* q) {
//    Student s = { 0 };
//    if (q->front) {
//        NodeQ* temp = q->front;
//        s = temp->info;
//        q->front = q->front->next;
//        if (!q->front) q->rear = NULL;
//        free(temp);
//    }
//    return s;
//}
//
//typedef struct NodeDubluQ {
//    Student info;
//    struct NodeDubluQ* next;
//    struct NodeDubluQ* prev;
//} NodeDubluQ;
//
//typedef struct {
//    NodeDubluQ* front;
//    NodeDubluQ* rear;
//} CoadaDubla;
//
//void enqueueDouble(CoadaDubla* c, Student s) {
//    NodeDubluQ* nou = malloc(sizeof(NodeDubluQ));
//    nou->info = s;
//    nou->next = NULL;
//    nou->prev = c->rear;
//    if (c->rear) c->rear->next = nou;
//    else c->front = nou;
//    c->rear = nou;
//}
//
//Student dequeueDouble(CoadaDubla* c) {
//    Student s = { 0 };
//    if (c->front) {
//        NodeDubluQ* temp = c->front;
//        s = temp->info;
//        c->front = temp->next;
//        if (c->front) c->front->prev = NULL;
//        else c->rear = NULL;
//        free(temp);
//    }
//    return s;
//}
//
//int main() {
//    FILE* f = fopen("studenti.txt", "r");
//    if (!f) return -1;
//
//    NodeS* stivaLista = NULL;
//    Queue coadaLista = { NULL, NULL };
//    CoadaDubla coadaDubla = { NULL, NULL };
//
//    while (!feof(f)) {
//        Student s = citireStudent(f);
//        if (s.nume) {
//            pushVector(s);
//            pushList(&stivaLista, s);
//            pushDouble(s);
//            enqueueVector(s);
//            enqueueList(&coadaLista, s);
//            enqueueDouble(&coadaDubla, s);
//        }
//    }
//    fclose(f);
//
//    printf("=== STIVA VECTOR ===\n");
//    afiseazaStackVector();
//
//    printf("\n=== STIVA LISTA ===\n");
//    while (stivaLista) afiseazaStudent(popList(&stivaLista));
//
//    printf("\n=== STIVA LISTA DUBLA ===\n");
//    while (topDouble) afiseazaStudent(popDouble());
//
//    printf("\n=== COADA VECTOR ===\n");
//    while (front < rear) afiseazaStudent(dequeueVector());
//
//    printf("\n=== COADA LISTA ===\n");
//    while (coadaLista.front) afiseazaStudent(dequeueList(&coadaLista));
//
//    printf("\n=== COADA DUBLA ===\n");
//    while (coadaDubla.front) afiseazaStudent(dequeueDouble(&coadaDubla));
//
//    return 0;
//}