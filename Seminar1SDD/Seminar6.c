//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
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
//typedef struct Node Node;
//struct Node {
//	Masina info;
//	Node* next;
//};
//
//struct HashTable {
//	int dim;
//	Node** v;
//};
//typedef struct HashTable HashTable;
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
//	m1.pret = atof(strtok(NULL, sep));
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
//void afisareListaMasini(Node* v) {
//	while (v != NULL) {
//		afisareMasina(v->info);
//		v = v->next;
//	}
//}
//
//void adaugaMasinaInLista(Node* v, Masina masinaNoua) {
//	if (v == NULL)return;
//	Node* nou = (Node*)malloc(sizeof(Node));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	while (v->next != NULL) {
//		v = v->next;
//	}
//	v->next = nou;
//}
//
//HashTable initializareHashTable(int dimensiune) {
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.v = (Node*)malloc(sizeof(Node) * dimensiune);
//	for (int i = 0; i < dimensiune; i++) {
//		ht.v[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(const char* nume, int dimensiune) {
//	if (dimensiune == 0) return 0;
//	int s = 0;
//	for (int i = 0; i < strlen(nume); i++) {
//		s += nume[i];
//		return s % dimensiune;
//	}
//}
//
//void inserareMasinaInTabela(HashTable hash, Masina masina) {
//	int poz = calculeazaHash(masina.numeSofer, hash.dim);
//	if (hash.v[poz] == NULL) {
//		Node* nou = (Node*)malloc(sizeof(Node));
//		nou->info = masina;
//		nou->next = NULL;
//		hash.v[poz] = nou;
//	}
//	else {
//		adaugaMasinaInLista(hash.v[poz], masina);
//	}
//
//}
//
//HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune) {
//	FILE* file = fopen(numeFisier, "r");
//	HashTable ht = initializareHashTable(dimensiune);
//	while (!feof(file)) {
//		inserareMasinaInTabela(ht, citireMasinaDinFisier(file));
//	}
//	fclose(file);
//	return ht;
//}
//
//void afisareTabelaDeMasini(HashTable ht) {
//	//sunt afisate toate masinile cu evidentierea clusterelor realizate
//}
//
//void dezalocareTabelaDeMasini(HashTable* ht) {
//	//sunt dezalocate toate masinile din tabela de dispersie
//}
//
//float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
//	//calculeaza pretul mediu al masinilor din fiecare cluster.
//	//trebuie sa returnam un vector cu valorile medii per cluster.
//	//lungimea vectorului este data de numarul de clustere care contin masini
//	return NULL;
//}
//
//Masina getMasinaDupaCheie(HashTable ht) {
//	Masina m;
//	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
//	//trebuie sa modificam numele functiei 
//	return m;
//}
//
//int main() {
//	HashTable ht = citireMasiniDinFisier("masini.txt", 10);
//
//	return 0;
//}