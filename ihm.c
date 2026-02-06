#include <stdio.h>
#include <stdlib.h>


int menu(){
	printf(" SPOTIFIX \n\n\n");
	printf("> 1. creer une nouvelle playlist\n");
	printf("> 2. charger une playlist a partir d'un fichier texte\n");
	printf("> 3. afficher une playlist\n");
	printf("> 4. ajouter un nouveau morceau dans une playlist\n");
	printf("> 5. ajouter un morceau d'une playlist dans une autre playlist\n");
	printf("> 6. rechercher un morceau\n");
	printf("> 7. enlever un morceau d'nue  playlist\n");
	printf("> 8. supprimer une playlist\n");
	printf("> 9. sauvegarder une playlist dans un fichier texte\n");

	int choix;
	printf("Que souhaitez vous faire ? ");
	scanf("%d", &choix);

	switch(choix){
		case '1':
			creer();
			break;

		case '2':
			charger();
			break;

		case '3':
			afficher();
			break;
		case '4':
			ajtNv();
			break;
		case '5':
			ajt();
			break;

		case '6':
			rechercher();
			break;

		case '7':
			enlever();
			break;
		case '8':
			supprimer();
			break;
		case '9':
			sauvegarder();
			break;	

		default:
			printf("Choix invalide\n");
			break;					
	}while(choix < 0 || choix > 10);

	return 0;

}