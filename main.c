#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ihm.h"
#include "morceau.h"
#include "playlist.h"



#define MAX_PLAYLIST 10

int main() {
    int choix;
    playlist *playlists[MAX_PLAYLIST];
    int nbPlaylists = 0;
    int playlistCourante = -1; 

    do {
        printf("=========================================================================\n");
        printf("                            S P O T I F I X                              \n");
        printf("=========================================================================\n\n");

        if (nbPlaylists > 0) {
            printf("Playlists disponibles :\n");
            for (int i = 0; i < nbPlaylists; i++) {
                if (i == playlistCourante) {
                    printf("  -> [%d] %s (ACTIVE)\n", i, playlists[i]->nom);
                } else {
                    printf("     [%d] %s\n", i, playlists[i]->nom);
                }
            }
        }

        printf("-------------------------------------------------------------------------\n");
        choix = afficherMenu(); 

        switch(choix) {
            case 1:
                printf("                      CREER UNE NOUVELLE PLAYLIST                    \n");
                printf("=========================================================================\n\n");
                
                if (nbPlaylists >= MAX_PLAYLIST) {
                    printf("Erreur : nombre maximum de playlists atteint !\n");
                    break;
                }
                
                char nom[100];
                int capacite;
                
                printf("Nom de la playlist : ");
                scanf("%s", nom);
                printf("Capacite (nombre max de morceaux) : ");
                scanf("%d", &capacite);
                
                playlists[nbPlaylists] = creerPlaylist(capacite, nom);
                printf("\n>>> Playlist '%s' creee avec succes !\n", nom);
                playlistCourante = nbPlaylists;
                nbPlaylists++;
                break;

            case 2:
                printf("                    CHARGER UNE PLAYLIST                             \n");
                printf("=========================================================================\n\n");
                
                if (nbPlaylists >= MAX_PLAYLIST) {
                    printf("Erreur : nombre maximum de playlists atteint !\n");
                    break;
                }
                
                char nomFichier[100];
                saisirNomFichier(nomFichier);
                
                playlist* p = chargerPlaylist(nomFichier);
                if (p != NULL) {
                    playlists[nbPlaylists] = p;
                    playlistCourante = nbPlaylists;
                    nbPlaylists++;
                    printf("\n>>> Playlist chargee avec succes !\n");
                } else {
                    printf("\n>>> Erreur lors du chargement de la playlist\n");
                }
                break;

            case 3:
                printf("                     AFFICHER UNE PLAYLIST                           \n");
                printf("=========================================================================\n\n");
                
                if (nbPlaylists == 0) {
                    printf("Aucune playlist disponible.\n");
                    break;
                }
                
                int indice;
                printf("Numero de la playlist a afficher (0-%d) : ", nbPlaylists - 1);
                scanf("%d", &indice);
                
                if (indice >= 0 && indice < nbPlaylists) {
                    printf("\n");
                    afficherPlaylist(playlists[indice]);
                } else {
                    printf("\n>>> Playlist invalide\n");
                }
                break;

            case 4:
                printf("                   AJOUTER UN NOUVEAU MORCEAU                        \n");
                printf("=========================================================================\n\n");
                
                if (playlistCourante == -1) {
                    printf("Aucune playlist active. Veuillez d'abord creer ou charger une playlist.\n");
                    break;
                }
                
                char titre[100], artiste[100];
                int annee, duree;
                
                saisirInfosMorceau(titre, artiste, &annee, &duree);
                
                Morceau m = creerMorceau(titre, artiste, annee, duree);
                int resultat = ajouterMorceauPlaylist(playlists[playlistCourante], m);
                
                if (resultat == 0) {
                    printf("\n>>> Morceau ajoute avec succes !\n");
                } else {
                    printf("\n>>> Erreur : impossible d'ajouter le morceau\n");
                }
                break;

            case 5:
                printf("           AJOUTER UN MORCEAU DEPUIS UNE AUTRE PLAYLIST              \n");
                printf("=========================================================================\n\n");
                
                if (nbPlaylists < 2) {
                    printf("Il faut au moins 2 playlists pour cette operation.\n");
                    break;
                }
                
                int source, dest, indiceMorceau;
                
                printf("Numero de la playlist source (0-%d) : ", nbPlaylists - 1);
                scanf("%d", &source);
                printf("Numero de la playlist destination (0-%d) : ", nbPlaylists - 1);
                scanf("%d", &dest);
                
                if (source >= 0 && source < nbPlaylists && dest >= 0 && dest < nbPlaylists) {
                    afficherPlaylist(playlists[source]);
                    printf("\nNumero du morceau a copier (1-%d) : ", playlists[source]->nbMorceaux);
                    scanf("%d", &indiceMorceau);

                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    
                    ajouterMorceauPlaylistDansAutrePlaylist(playlists[source], playlists[dest], indiceMorceau - 1);
                    printf("\n>>> Morceau copie avec succes !\n");
                } else {
                    printf("\n>>> Playlists invalides\n");
                }
                break;

            case 6:
                printf("                    RECHERCHER UN MORCEAU                            \n");
                printf("=========================================================================\n\n");
                
                if (playlistCourante == -1) {
                    printf("Aucune playlist active.\n");
                    break;
                }
                
                int c;
                while ((c = getchar()) != '\n' && c != EOF);

                char titreRech[100];
                printf("Titre du morceau a rechercher : ");

                if (fgets(titreRech, sizeof(titreRech), stdin) != NULL){
                    titreRech[strcspn(titreRech, "\n")] = '\0';  
                    printf("Recherche du titre: '%s'\n", titreRech);               
                    Morceau* morceauTrouve = rechercherMorceau(playlists[playlistCourante], titreRech); 
                    if (morceauTrouve != NULL) {
                        printf("\n>>> Morceau trouve !\n\n");
                        afficherMorceau(*morceauTrouve);
                    } else {
                        printf("\n>>> Morceau non trouve\n");
                    }
                }
                break;

            case 7:
                printf("                  ENLEVER UN MORCEAU                                 \n");
                printf("=========================================================================\n\n");
                
                if (playlistCourante == -1) {
                    printf("Aucune playlist active.\n");
                    break;
                }
                
                afficherPlaylist(playlists[playlistCourante]);
                
                int indiceEnlever;
                printf("\nNumero du morceau a enlever (1-%d) : ", playlists[playlistCourante]->nbMorceaux);
                scanf("%d", &indiceEnlever);
                
                enleverMorceauPlaylist(playlists[playlistCourante], indiceEnlever - 1);
                printf("\n>>> Morceau enleve avec succes !\n");
                break;
                
            case 8:
                printf("                   SUPPRIMER UNE PLAYLIST                            \n");
                printf("=========================================================================\n\n");
                
                if (nbPlaylists == 0) {
                    printf("Aucune playlist disponible.\n");
                    break;
                }
                
                int indiceSuppr;
                printf("Numero de la playlist a supprimer (0-%d) : ", nbPlaylists - 1);
                scanf("%d", &indiceSuppr);
                
                if (indiceSuppr >= 0 && indiceSuppr < nbPlaylists) {
                    supprimerPlaylist(playlists[indiceSuppr]);
                    
                    for (int i = indiceSuppr; i < nbPlaylists - 1; i++) {
                        playlists[i] = playlists[i + 1];
                    }
                    nbPlaylists--;
                    
                    if (playlistCourante == indiceSuppr) {
                        playlistCourante = (nbPlaylists > 0) ? 0 : -1;
                    } else if (playlistCourante > indiceSuppr) {
                        playlistCourante--;
                    }
                    
                    printf("\n>>> Playlist supprimee avec succes !\n");
                } else {
                    printf("\n>>> Playlist invalide\n");
                }
                break;

            case 9:
                printf("                  SAUVEGARDER UNE PLAYLIST                           \n");
                printf("=========================================================================\n\n");
                
                if (playlistCourante == -1) {
                    printf("Aucune playlist active.\n");
                    break;
                }
                
                char nomFichierSauvegarde[100];
                saisirNomFichier(nomFichierSauvegarde);
                
                sauvegarderPlaylist(playlists[playlistCourante], nomFichierSauvegarde);
                printf("\n>>> Playlist sauvegardee avec succes !\n");
                break; 
                
            case 10:
                printf("                  CHANGER DE PLAYLIST ACTIVE                         \n");
                printf("=========================================================================\n\n");
                
                if (nbPlaylists == 0) {
                    printf("Aucune playlist disponible.\n");
                    break;
                }
                
                int indiceActiver;
                printf("Numero de la playlist a activer (0-%d) : ", nbPlaylists - 1);
                scanf("%d", &indiceActiver);
                
                if (indiceActiver >= 0 && indiceActiver < nbPlaylists) {
                    playlistCourante = indiceActiver;
                    printf("\n>>> Playlist '%s' activee !\n", playlists[playlistCourante]->nom);
                } else {
                    printf("\n>>> Playlist invalide\n");
                }
                break;

            default:
                printf("Choix invalide\n");
                break;
        }
    } while(choix != 0); 
    
    return 0;
}