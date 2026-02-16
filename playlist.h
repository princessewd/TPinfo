#ifndef playlist_H
#define playlist_H
#include "morceau.h"

typedef struct{
    char *nom;
    Morceau** TabMorceaux;
    int capacite;
    int nbMorceaux;
} playlist;

playlist* creerPlaylist(int capacite, const char* nom);
int ajouterMorceauPlaylist(playlist *p, Morceau m);
void enleverMorceauPlaylist(playlist *p, int indice);
void supprimerPlaylist(playlist *p);
void ajouterMorceauPlaylistDansAutrePlaylist(playlist *psource, playlist *pdestination, int indice);
Morceau* rechercherMorceau(playlist *p, const char *titre);
void sauvegarderPlaylist(const playlist *p, const char *nomFichier);
playlist* chargerPlaylist(const char* nomFichier);
void afficherPlaylist(playlist *p);
#endif