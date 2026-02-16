#ifndef ihm_H
#define ihm_H
#include "playlist.h"

int afficherMenu();
void saisirInfosMorceau(char* titre, char* artiste, int* annee, int* duree);
void afficherPlaylist(playlist *p);
void saisirNomFichier(char* nomFichier);    

#endif