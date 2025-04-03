#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Muzica {
    int cod;
    char* titluMelodie;
    char* artist;
    float durataMin;
    int nrRecenzii;
    float* evaluari;
};

typedef struct Muzica Muzica;

//functia de citire de la tastatura
Muzica citireDeLaTastatura() {
    Muzica melodie;
    char buffer[100];

    printf("Introduceti codul melodiei: ");
    scanf("%d", &melodie.cod);
    getchar(); 

    printf("Introduceti titlul melodiei: ");
    fgets(buffer, sizeof(buffer), stdin);  
    buffer[strlen(buffer) - 1] = '\0';  
    melodie.titluMelodie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    if (melodie.titluMelodie) {
        strcpy(melodie.titluMelodie, buffer);
    }

    printf("Introduceti artistul: ");
    fgets(buffer, sizeof(buffer), stdin); 
    buffer[strlen(buffer) - 1] = '\0';  
    melodie.artist = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    if (melodie.artist) {
        strcpy(melodie.artist, buffer);
    }

    printf("Introduceti durata melodiei (minute): ");
    scanf("%f", &melodie.durataMin);

    printf("Introduceti numarul de recenzii: ");
    scanf("%d", &melodie.nrRecenzii);

    if (melodie.nrRecenzii > 0) {
        melodie.evaluari = (float*)malloc(melodie.nrRecenzii * sizeof(float));
        printf("Introduceti evaluarile utilizatorilor (0.0 - 10.0):\n");
        for (int i = 0; i < melodie.nrRecenzii; i++) {
            printf("Evaluare %d: ", i + 1);
            scanf("%f", &melodie.evaluari[i]);
        }
    }
    else {
        melodie.evaluari = NULL;
    }

    return melodie;
}

//functia de afisare la consola
void afisareMelodie(Muzica melodie) {
    printf("\nCod: %d\n", melodie.cod);
    printf("Titlu: %s\n", melodie.titluMelodie);
    printf("Artist: %s\n", melodie.artist);
    printf("Durata: %.2f minute\n", melodie.durataMin);
    printf("Numar recenzii: %d\n", melodie.nrRecenzii);

    if (melodie.nrRecenzii > 0) {
        printf("Evaluari utilizatori: ");
        for (int i = 0; i < melodie.nrRecenzii; i++) {
            printf("%.1f ", melodie.evaluari[i]);
        }
        printf("\n");
    }
}

//functie care calculeaza media recenziilor per melodie
float calculeazaMediaRecenziilor(float* evaluari, int nrRecenzii) {
    if (nrRecenzii == 0) {
        return 0;
    }

    float suma = 0.0;
    for (int i = 0; i < nrRecenzii; i++) {
        suma += evaluari[i];
    }

    return suma / nrRecenzii;
}

//functie care modifica titlul melodiei
void modificaTitlu(Muzica* melodie, const char* nouTitlu) {
    if (melodie->titluMelodie != NULL) {
        free(melodie->titluMelodie);
    }

    melodie->titluMelodie = (char*)malloc((strlen(nouTitlu) + 1) * sizeof(char));

    if (melodie->titluMelodie != NULL) {
        strcpy(melodie->titluMelodie, nouTitlu);
    }
}

void dezalocare(Muzica* melodie) {
    free(melodie->titluMelodie);
    free(melodie->artist);
    free(melodie->evaluari);
}

int main() {
    Muzica melodie1 = citireDeLaTastatura();
    afisareMelodie(melodie1);

    //medie
    float media = calculeazaMediaRecenziilor(melodie1.evaluari, melodie1.nrRecenzii);
    printf("\nMedia recenziilor: %.2f\n", media);

    //modificare titlu melodie
    const char* nouTitlu = "Hypnotize";
    modificaTitlu(&melodie1, nouTitlu);

    printf("\nDupa modificarea titlului:\n");
    afisareMelodie(melodie1);

    dezalocare(&melodie1);

    return 0;
}
