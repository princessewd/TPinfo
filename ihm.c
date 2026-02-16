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
    printf("Entrez le titre du morceau : ");
    scanf("%s", titre);
    printf("Entrez l'artiste du morceau : ");
    scanf("%s", artiste);
    printf("Entrez l'année de sortie du morceau : ");
    scanf("%d", annee);
    printf("Entrez la durée du morceau (en secondes) : ");
    scanf("%d", duree);
}



void saisirNomFichier(char* nomFichier){
    printf("Entrez le nom du fichier : ");
    scanf("%s", nomFichier);
}