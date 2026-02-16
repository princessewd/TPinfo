#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ihm.h"

int afficherMenu(){
	int choix;
    printf(" SPOTIFIX \n\n\n");
    printf("> 1. creer une nouvelle playlist\n");
    printf("> 2. charger une playlist a partir d'un fichier texte\n");
    printf("> 3. afficher une playlist\n");
    printf("> 4. ajouter un nouveau morceau dans une playlist\n");
    printf("> 5. ajouter un morceau d'une playlist dans une autre playlist\n");
    printf("> 6. rechercher un morceau\n");
    printf("> 7. enlever un morceau d'une playlist\n");
    printf("> 8. supprimer une playlist\n");
    printf("> 9. sauvegarder une playlist dans un fichier texte\n");
	scanf("%d", &choix);

	return choix;
}

void saisirInfosMorceau(char* titre, char* artiste, int* annee, int* duree){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Entrez le titre du morceau : ");
    if (fgets(titre, 100, stdin) != NULL) {
        size_t len = strlen(titre);
        if (len > 0 && titre[len-1] == '\n') {
            titre[len-1] = '\0';
        }
    }
    
    
    printf("Entrez l'artiste du morceau : ");
    if (fgets(artiste, 100, stdin) != NULL) {
        size_t len = strlen(artiste);
        if (len > 0 && artiste[len-1] == '\n') {
            artiste[len-1] = '\0';
        }
    }
    
    
    printf("Entrez l'annee de sortie du morceau : ");
    scanf("%d", annee);
    
    printf("Entrez la duree du morceau (en secondes) : ");
    scanf("%d", duree);
}



void saisirNomFichier(char* nomFichier){
    printf("Entrez le nom du fichier : ");
    scanf("%s", nomFichier);
}