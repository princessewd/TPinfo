#ifndef morceau_H
#define morceau_H

typedef struct{
    char *titre;
    char *artiste;
    int annee;
    int duree;
    int nbRef;
} Morceau;

Morceau creerMorceau(const char* titre, const char* artiste, int annee, int duree); 
void detruireMorceau(Morceau m);
void incrementerRef(Morceau* m);
int decrementerRef(Morceau *m);
void afficherMorceau(const Morceau m);

#endif
