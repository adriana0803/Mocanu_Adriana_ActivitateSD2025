//#include<stdio.h>
//#include<malloc.h>
//
//struct Masina {
//	int id;
//	int nrLocuri;
//	char* marca;
//	float capacitate_C;
//	char normaPoluare;
//};
//
//struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitate_C, char normaPoluare) {
//	struct Masina s;
//	s.id = id;
//	s.nrLocuri = nrLocuri;
//	s.capacitate_C = capacitate_C;
//	s.normaPoluare = normaPoluare;
//
//	s.marca = (char*)malloc(strlen(marca) + 1);  // Alocăm memorie pentru marca
//	strcpy(s.marca, marca);  // Copiem conținutul
//
//	return s;
//}
//
//
//void afisare(struct Masina s) {
//	printf("\n Id masina: %d\n Nr locuri: %d \n Capacitate: %.2f \n Marca: %s \n Norma: %c",
//		s.id, s.nrLocuri, s.capacitate_C, s.marca, s.normaPoluare);
//}
//
//
//void afisareVector(struct Masina* vector, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++)
//		afisare(vector[i]);
//}
//
//struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
//	if (nrElementeCopiate > nrElemente)
//		nrElementeCopiate = nrElemente;
//
//	struct Masina* vectorNou = (struct Masina*)malloc(nrElementeCopiate * sizeof(struct Masina));
//
//	for (int i = 0; i < nrElementeCopiate; i++) {
//		vectorNou[i].id = vector[i].id;
//		vectorNou[i].nrLocuri = vector[i].nrLocuri;
//		vectorNou[i].capacitate_C = vector[i].capacitate_C;
//		vectorNou[i].normaPoluare = vector[i].normaPoluare;
//
//		vectorNou[i].marca = (char*)malloc(strlen(vector[i].marca) + 1);
//		strcpy(vectorNou[i].marca, vector[i].marca);
//	}
//
//	return vectorNou;
//}
//
//
//
//void dezalocare(struct Masina** vector, int* nrElemente) {
//	for (int i = 0; i < *nrElemente; i++) {
//		free((*vector)[i].marca);
//	}
//	free(*vector);
//	*vector = NULL;
//	*nrElemente = 0;
//}
//
//
//struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
//	if (nrElementeCopiate > nrElemente)
//		nrElementeCopiate = nrElemente;
//
//	struct Masina* vectorNou = (struct Masina*)malloc(nrElementeCopiate * sizeof(struct Masina));
//
//	for (int i = 0; i < nrElementeCopiate; i++) {
//		vectorNou[i].id = vector[i].id;
//		vectorNou[i].nrLocuri = vector[i].nrLocuri;
//		vectorNou[i].capacitate_C = vector[i].capacitate_C;
//		vectorNou[i].normaPoluare = vector[i].normaPoluare;
//
//		vectorNou[i].marca = (char*)malloc(strlen(vector[i].marca) + 1);
//		strcpy(vectorNou[i].marca, vector[i].marca);
//	}
//
//	return vectorNou;
//}
//
//void copiazaMasiniCuCCMare(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
//	*dimensiune = 0;
//	for (char i = 0; i < nrElemente; i++) {
//		if (vector[i].capacitate_C > prag) {
//			(*dimensiune)++;
//		}
//	}
//	if (*dimensiune > 0)
//	{
//		int j = 0;
//		*vectorNou = (struct Masina*)malloc((*dimensiune) * sizeof(struct Masina));
//		for (int i = 0; i < nrElemente; i++) {
//			if (vector[i].capacitate_C > prag) {
//				(*vectorNou)[j] = vector[i];
//				(*vectorNou)[j].marca = (char*)malloc(strlen(vector[i].marca) + 1);
//				strcpy_s((*vectorNou)[j].marca, strlen(vector[i].marca) + 1, vector[i].marca);
//				j++;
//			}
//		}
//	}
//}
//
//struct Masina getPrimaMasinaDupaMarca(struct Masina* vector, int nrElemente, const char* conditie) {
//	for (int i = 0; i < nrElemente; i++) {
//		if (strcmp(vector[i].marca, conditie) == 0)
//			return vector[i];
//	}
//	return initializare(1, 0, "", 0, 0);
//}
//
//int main() {
//	struct Masina* vector;
//	int nrElem = 3;
//	vector = (struct Masina*)malloc(nrElem * sizeof(struct Masina));
//
//	vector[0] = initializare(1, 3, "Dacia", 40, '5');
//	vector[1] = initializare(2, 5, "Honda", 30, '6');
//	vector[2] = initializare(2, 5, "Dacia", 50, '3');
//
//	afisareVector(vector, nrElem);
//
//	struct Masina* vectorMasiniCopiate;
//	int nrElemCop = 2;
//
//	printf("Afisare masini copiate:");
//	vectorMasiniCopiate = copiazaPrimeleNElemente(vector, nrElem, nrElemCop);
//	afisareVector(vectorMasiniCopiate, nrElemCop);
//	dezalocare(&vectorMasiniCopiate, &nrElemCop);
//
//	printf("Afisare masini cu capacitate mai mare:");
//	copiazaMasiniCuCCMare(vector, nrElem, 35, &vectorMasiniCopiate, &nrElemCop);
//
//	afisareVector(vectorMasiniCopiate, nrElemCop);
//	dezalocare(&vectorMasiniCopiate, &nrElemCop);
//	struct Masina m1 = getPrimaMasinaDupaMarca(vector, nrElem, "Dacia");
//
//	printf("Masina dupa marca:\n");
//	afisare(m1);
//	dezalocare(&vector, &nrElem);
//
//	return 0;
//}