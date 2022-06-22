/**
<h1>Contient le programme principal<h1>
@name main.c
@author Machkour Oke
*/
#include <stdio.h>
#include <stdlib.h>
#include "polynome.h"


int main() {
    system("color F0");
    pol *p = (pol *) calloc(20, sizeof(pol));
    char choix = 'o';
    char nom[20];
    printf("Quelle est votre nom : \n");
    gets(nom);
    system("cls");
    printf("******Bienvenue %s, que voulez vous faire ?******\n", nom);
    while (choix == 'o') {
        /* Envoi des informations au gestionnaire de choix
        tout en fixant le nombre de polynômes maximale à 20 */
        gestionnaireDeChoix(menu(nom), p, 20);
        printf("\nVoulez vous continuer(o/n)\n");
        scanf("%c", &choix);
        vidageBuffer();
    }
    printf("Merci d'avoir utilise notre logiciel tres chere %s nous vous espérons prochainement\n", nom);
    free(p);

    return 0;
}
