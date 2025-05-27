//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//struct Heap {
//	int lungime;
//	Masina* vector;
//	int nrMasini;
//};
//typedef struct Heap Heap;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atoi(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrMasini = 0;
//	heap.vector = (Masina*)malloc(sizeof(Masina) * lungime);
//	return heap;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	int pozSt = 2 * pozitieNod + 1;
//	int pozDr = 2 * pozitieNod + 2;
//	int pozMax = pozitieNod;
//	if (pozSt < heap.nrMasini && heap.vector[pozMax].pret < heap.vector[pozDr].pret) {
//		pozMax = pozSt;
//	}
//	if (pozDr < heap.nrMasini && heap.vector[pozMax].pret < heap.vector[pozSt].pret) {
//		pozMax = pozDr;
//	}
//	if (pozMax != pozitieNod) {
//		Masina aux = heap.vector[pozitieNod];
//		heap.vector[pozMax] = heap.vector[pozitieNod];
//		heap.vector[pozitieNod] = aux;
//		if (pozMax <= (heap.nrMasini - 2) / 2) {
//			filtreazaHeap(heap, pozMax);
//		}
//	}
//}
//
//Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	if (!file) {
//		perror("Fisierul nu a putut fi deschis");
//		exit(1);
//	}
//
//	Heap heap = initializareHeap(10);
//
//	while (!feof(file)) {
//		Masina m = citireMasinaDinFisier(file);
//		heap.vector[heap.nrMasini++] = m;
//	}
//	fclose(file);
//
//	for (int i = (heap.nrMasini - 2) / 2; i >= 0; i--) {
//		filtreazaHeap(heap, i);
//	}
//
//	return heap;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrMasini;i++) {
//		afisareMasina(heap.vector[i]);
//	}
//}
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0;i < heap->lungime;i++) {
//		free(heap->vector[i].model);
//		free(heap->vector[i].numeSofer);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrMasini = 0;
//}
//
//int main() {
//	Heap heap = citireHeapDeMasiniDinFisier("masini.txt");
//
//	printf("Heap-ul initial:\n");
//	afisareHeap(heap);
//	
//	dezalocareHeap(&heap);
//}