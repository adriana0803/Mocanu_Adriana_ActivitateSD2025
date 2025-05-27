//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Pacient {
//	char* nume;
//	int varsta;
//	int grad;
//};
//
//typedef struct Pacient Pacient;
//typedef struct Heap Heap;
//
//struct Heap {
//	Pacient* vector;
//	int lungime;
//	int nrElemente;
//};
//
//
//Pacient citirePacientDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	Pacient p;
//	char* aux;
//	aux = strtok(buffer, sep);
//	p.nume = (char*)malloc(strlen(aux) + 1);
//	strcpy(p.nume, aux);
//	aux = strtok(NULL, sep);
//	p.varsta = atoi(aux);
//	aux = strtok(NULL, sep);
//	p.grad = atoi(aux);
//	return p;
//}
//
//void afiseazaPacient(Pacient p) {
//	printf("Numele pacientului: %s \n", p.nume);
//	printf("Varsta: %d \n", p.varsta);
//	printf("Grad: %d \n\n", p.grad);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrElemente = 0;
//	heap.vector = (Pacient*)malloc(sizeof(Pacient) * lungime);
//	return heap;
//}
//
//void filtrareMaxHeap(Heap heap, int poz) {
//	int fiuS = poz * 2 + 1;
//	int fiuD = poz * 2 + 2;
//	int max = poz;
//	if (fiuS < heap.nrElemente && heap.vector[fiuS].grad > heap.vector[max].grad) {
//		max = fiuS;
//	}
//	if (fiuD < heap.nrElemente && heap.vector[fiuD].grad > heap.vector[max].grad) {
//		max = fiuD;
//	}
//	if (max != poz) {
//		Pacient aux = heap.vector[max];
//		heap.vector[max] = heap.vector[poz];
//		heap.vector[poz] = aux;
//		filtrareMaxHeap(heap, max);
//	}
//}
//
//Heap citireHeapDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(20);
//	while (!feof(file)) {
//		heap.vector[heap.nrElemente++] = citirePacientDinFisier(file);
//	}
//	fclose(file);
//	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
//		filtrareMaxHeap(heap, i);
//	}
//	return heap;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrElemente; i++) {
//		afiseazaPacient(heap.vector[i]);
//	}
//}
//
//Pacient extragePacientDinHeap(Heap* heap) {
//	if (heap->nrElemente == 0) {
//		Pacient gol = { NULL, 0, 0 };
//		return gol;
//	}
//	Pacient aux = heap->vector[0];
//	heap->vector[0] = heap->vector[heap->nrElemente - 1];
//	heap->nrElemente--;
//	filtrareMaxHeap(*heap, 0);
//	return aux;
//}
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->nrElemente; i++) {
//		free(heap->vector[i].nume);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrElemente = 0;
//}
//
//int main() {
//	Heap maxHeap = citireHeapDinFisier("pacienti.txt");
//	afisareHeap(maxHeap);
//
//	printf("\n---- Extragere pacient cu prioritate maxima: -----\n");
//	Pacient urgent = extragePacientDinHeap(&maxHeap);
//	afiseazaPacient(urgent);
//	free(urgent.nume);
//
//	printf("\n---- Heap dupa extragere: -----\n");
//	afisareHeap(maxHeap);
//
//	dezalocareHeap(&maxHeap);
//	return 0;
//}