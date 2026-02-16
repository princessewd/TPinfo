#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "playlist.h"

playlist* creerPlaylist(int capacite, const char* nom){
    playlist *p = (playlist*)malloc(sizeof(playlist));
    assert (p != NULL);

    p->TabMorceaux = (Morceau**)malloc(capacite * sizeof(Morceau*));
    assert (p->TabMorceaux != NULL);
    
    // Allouer de la mémoire pour stocker le nom (strlen(nom)+1 pour le caractère '\0')
    p->nom = (char*)malloc((strlen(nom) + 1) * sizeof(char));
    assert (p->nom != NULL);
    
    // Copier le contenu de 'nom' dans p->nom
    strcpy(p->nom, nom);
    
    p->capacite = capacite;
    p->nbMorceaux = 0;
    return p;
}

int ajouterMorceauPlaylist(playlist *p, Morceau m){
    if(p->nbMorceaux >= p->capacite){
        fprintf(stderr, "La playlist est pleine, impossible d'ajouter le morceau\n");
        return -1;
    }
    Morceau *mPtr = (Morceau*)malloc(sizeof(Morceau));
    assert (mPtr != NULL);
   
    *mPtr = m;
    p->TabMorceaux[p->nbMorceaux] = mPtr;
    p->nbMorceaux++;
    return 0;
}

void enleverMorceauPlaylist(playlist *p, int indice){
    if(indice < 0 || indice >= p->nbMorceaux){
        fprintf(stderr, "Indice invalide pour enlever le morceau\n");
        return;
    }
    free(p->TabMorceaux[indice]);
    for(int i = indice; i < p->nbMorceaux - 1; i++){
        p->TabMorceaux[i] = p->TabMorceaux[i + 1];
    }
    p->nbMorceaux--;
}

void supprimerPlaylist(playlist *p){
    for(int i = 0; i < p->nbMorceaux; i++){
        free(p->TabMorceaux[i]);
    }
    free(p->TabMorceaux);
    free(p->nom);
    free(p);
}

void ajouterMorceauPlaylistDansAutrePlaylist(playlist *psource, playlist *pdestination, int indice){
    if(indice < 0 || indice >= psource->nbMorceaux){
        fprintf(stderr, "Indice invalide pour ajouter le morceau dans l'autre playlist\n");
        return;
    }
    Morceau *mPtr = psource->TabMorceaux[indice];
    ajouterMorceauPlaylist(pdestination, *mPtr);
}

Morceau* rechercherMorceau(playlist *p, const char* titre){
    for(int i = 0; i < p->nbMorceaux; i++){
        if(strcmp(p->TabMorceaux[i]->titre, titre) == 0){
            return p->TabMorceaux[i];
        }
    }
    return NULL;
}

void sauvegarderPlaylist(const playlist *p, const char* nomFichier){
    FILE *f = fopen(nomFichier, "w");
    if(f == NULL){
        perror("Erreur d'ouverture du fichier pour sauvegarder la playlist\n");
        return ;
    }
    fprintf(f, "%s\n", p->nom);
    fprintf(f, "%d\n", p->nbMorceaux);
    for(int i = 0; i < p->nbMorceaux; i++){
        Morceau *m = p->TabMorceaux[i];
        fprintf(f, "%s\n%s\n%d\n%d\n%d\n", m->titre, m->artiste, m->annee, m->duree, m->nbRef);
    }
    fclose(f);
}

playlist* chargerPlaylist(const char* nomFichier){
    FILE *f = fopen(nomFichier, "r");
    if(f == NULL){
        perror("Erreur d'ouverture du fichier pour charger la playlist\n");
        return NULL;
    }
    char nom[100];
    fgets(nom, 100, f);
    nom[strcspn(nom, "\n")] = '\0'; // Enlever le saut de ligne
    playlist *p = creerPlaylist(10, nom); // Capacité initiale de 10 morceaux
    int nbMorceaux;
    fscanf(f, "%d\n", &nbMorceaux);
    for(int i = 0; i < nbMorceaux; i++){
        Morceau m;
        char titre[100], artiste[100];
        fscanf(f, "%s\n%s\n%d\n%d\n%d\n", titre, artiste, &m.annee, &m.duree, &m.nbRef);
        m.titre = strdup(titre);
        m.artiste = strdup(artiste);
        ajouterMorceauPlaylist(p, m);
    }
    fclose(f);
    return p;
}

void afficherPlaylist(playlist *p){
    printf("Playlist : %s\n", p->nom);
    for(int i = 0; i < p->nbMorceaux; i++){
        printf("%d. %s - %s (%d) [%d secondes]\n", i+1, p->TabMorceaux[i]->titre, p->TabMorceaux[i]->artiste, p->TabMorceaux[i]->annee, p->TabMorceaux[i]->duree);
    }
}
