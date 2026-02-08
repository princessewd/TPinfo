#ifndef morceau_H
#define morceau_H

typedef struct{
    char *titre;
    char *artiste;
    int annee;
    int duree;
    int nbRef;
} morceau;

morceau creerMorceau(const char* titre, const char* artiste, int annee, int duree);
void detruireMorceau(morceau m);
void incrementerRef(morceau* m);
int decrementerRef(morceau *m);
void afficherMorceau(const morceau m);

#endif
