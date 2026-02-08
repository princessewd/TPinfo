#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morceau.h"

morceau creerMorceau(const char* titre, const char* artiste, int annee, int duree){
    morceau m;
    m.titre = NULL;
    m.artiste = NULL;
    m.annee = annee;
    m.duree = duree;
    m.nbRef = 0;

    m.titre = malloc(100 * sizeof(char));
    if(m.titre == NULL){
        printf("Erreur d'allocation pour le titre");
        return m;
    }
    strcpy(m.titre, titre);

    m.artiste = malloc(100*sizeof(char));
    if (m.artiste == NULL){
        printf("Erreur d'allocation pour l'artiste");
        free(m.titre);
        m.titre = NULL;
        return m;
    }
    strcpy(m.artiste, artiste);

    return m;

}

void detruireMorceau(morceau m){
    if (m.titre != NULL) {
        free(m.titre);
    }
    if (m.artiste != NULL) {
        free(m.artiste);
    }
}

void incrementerRef(morceau*m){
    if (m != NULL){
        m->nbRef++;
    }
}

int decrementerRef(morceau*m){
    if(m == NULL){
        return 0;
    }
    m->nbRef--;
    if(m->nbRef <= 0){
        detruireMorceau(*m);
        return 1;
    }
    return 0;
}

void afficherMorceau(const morceau m){
    if(m.titre == NULL || m.artiste == NULL){
        printf("Morceau inexistant");
    }
    else{
        printf("Tire: %s\n", m.titre);
        printf("Artiste: %s\n", m.artiste);
        printf("Année: %d\n", m.annee);
        printf("Durée: %d sec\n", m.duree);
        printf("Nombre de reference: %d\n", m.nbRef);


    }

}


int main() {
    printf("test module morceau\n\n");
    
    // Création
    printf("1. Creation d'un morceau:\n");
    morceau m1 = creerMorceau("Yesterday", "The Beatles", 1965, 125);
    afficherMorceau(m1);
    
    // Incrémentation
    printf("2. Apres 2 references:\n");
    incrementerRef(&m1);
    incrementerRef(&m1);
    afficherMorceau(m1);
    
    // Décrémentation
    printf("3. Apres une decrementation:\n");
    int resultat = decrementerRef(&m1);
    if (resultat == 0) {
        printf("Le morceau n'a pas ete detruit\n");
    }
    afficherMorceau(m1);
    
    //Destruction
    printf("4. Decrementation jusqu'a destruction:\n");
    resultat = decrementerRef(&m1);
    if (resultat == 1) {
        printf("Le morceau a ete detruit\n");
    }
    
    // Nouveau morceau
    printf("5. Test avec un autre morceau:\n");
    morceau m2 = creerMorceau("Smells Like Teen Spirit", "Nirvana", 1991, 301);
    afficherMorceau(m2);
    detruireMorceau(m2);
    printf("Morceau detruit manuellement\n");


    return 0;
}

