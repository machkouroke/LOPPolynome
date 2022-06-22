/**
<h1>Contient les définition des fonctions sur les polynômes <h1>
@name polynome.c

@author Machkour Oke

*/
#include "polynome.h"

#define retour() printf("\n");

static int compteurPolynome = 0;

/**
 * Fonction pour vérifier si un nombre réel n'est qu'un simple entier
 * @param a Nombre à vérifier
 * @return Retourne si si le nombre est un entier ou non
 */
int isInteger(float a) {
    return (float) (int) a == a;
}

/**
 * Transforme un polynômes en polynomes nul
 * @param p Polynômes à transformer
 */
void NulPoly(pol *p) {
    int i;
    /* le polynome nul a pour degré -1 ici */
    p->degre = -1;
    for (i = 0; i < DegreMax + 1; i++) {
        p->coeff[i] = 0;
    }
}

/**
 * Permet à l'utilisateur de saisir un polynôme
 * @param p
 */
void SaisiePoly(pol *p) {
    int i, k;
    char *lettreCoefficient = NULL;

    float degree;
    int saisie;
    saisieDegree: //libellé permettant un saut en cas d'erreur
    printf("Quelle est le degree de votre polynome : ");
    saisie = scanf("%f", &degree);
    vidageBuffer();
    if (saisie != 1) {
        printf("Saisie incorrect veuillez réessayer !\n");
        goto saisieDegree;
    }
    p->degre = (int) degree;
    if (!isInteger(degree)) {
        printf("Votre degree a ete tronque a %d \n", (int) degree);
    }
    if (p->degre >= 21) {
        printf("Veuillez entrer un degree inferieur ou égal  a 20!\n");
        goto saisieDegree;
    } else if (p->degre >= 0) {
        printf("Votre polynome est de la forme :");
        lettreCoefficient = (char *) calloc(p->degre + 1,
                                            sizeof(char));
        if (lettreCoefficient == NULL) {
            printf("Erreur d'allocation mémoire");
            exit(0);
        }
        /* Pour l'attribution des lettres du polynomes d'exemples, on commence par 'a' */
        k = 97 +
            (p->degre);
        for (i = 97; i <= k; i++) {
            /* si le degré est egal à 0 on écrit juste a qui répresente la constante à entrer */
            if (p->degre == 0) {
                lettreCoefficient[0] = 'a';
                printf("a(polynome constant)\n");
                break;
            } else if (i != k && k - i != 1) {
                lettreCoefficient[i - 97] = i;
                printf("%cx^%d+", i, k - i);
            } else if (i != k &&
                       k - i == 1)         /*Pour un affichage plus propre je supprime l'exposant du monome de degré 1*/
            {
                lettreCoefficient[i - 97] = i;
                printf("%cx+", i);
            } else   //De meme pour un affichage plus propre je garde juste le coefficient du monome de degré 0
            {
                lettreCoefficient[i - 97] = i;
                printf("%c\n", i);
            }
        }
        printf("Veuillez saisir le coefficient: \n"); //Saisie des coefficients
        for (i = DegreMax; i >= 0; i--) {
            if (i <=
                p->degre) {
                do {
                    printf("%c:", lettreCoefficient[p->degre - i]);
                    saisie = scanf("%f", &(p->coeff[i]));
                    vidageBuffer();
                    if (saisie != 1) {
                        printf("Saisie incorrect veuillez reesayer !");
                    }
                    retour()
                } while (saisie != 1);
            } else
                p->coeff[i] = 0;
        }
        printf("Votre polynome est ");
        voirPoly(*p);
        free(lettreCoefficient);
        compteurPolynome++; //Incrémentation du nombre de polynome pour pouvoir plus tard optimiser la liste d'affichage
    } else if (p->degre == -1) {
        printf("Votre polynome est le polynome nul. P(x)=0\n");
        NulPoly(p); //Si le polynome est le polynome nul on met toutes ses cases a 0 avec nulpoly
        compteurPolynome++;
    } else {
        printf("Veuillez entrer un degree positif(inferieur a 20) ,nul ou -1 pour le polynome nul\n");
        goto saisieDegree; //Si le dégré est inférieur à -1 on retourne à la saisie de dégré
    }


}

/**
 * Permet d'afficher un polynômes
 * @param p
 */
void voirPoly(pol p) {
    int i;
    printf("P(x)= ");
    for (i = p.degre; i >= 0; i--) {
        /*Si le coefficient est entier on l'affiche sans virgule juste sous forme d'entier
            tout en optimisant l'affichage du polynome, c'est-à-dire enlever les 1 devant les monomes supprimer le monome si
            ses coefficients est nul etc...*/
        if (isInteger(p.coeff[i])) {
            if (i != 0 && i != 1) {
                if (p.coeff[i] == 1)
                    printf("x^%d+", i);
                else if (p.coeff[i] == 0)
                    printf("0");
                else if (p.coeff[i] != 0 && p.coeff[i] != 1)
                    printf("%.0fx^%d+", p.coeff[i], i);
            } else if (i == 1) {
                if (p.coeff[i] == 1)
                    printf("x+");
                else if (p.coeff[i] == 0)
                    printf("0");
                else if (p.coeff[i] != 0 && p.coeff[i] != 1)
                    printf("%.0fx+", p.coeff[i]);
            } else {
                if (p.coeff[i] == 0)
                    printf("0");
                else
                    printf("%.0f", p.coeff[i]);
            }

        } else    /*Ici le polynome n'étant pas entier on l'affiche comme un réel, mais en respectants les mêmes optimisations
            que ci dessus*/
        {
            if (i != 0 && i != 1) {
                if (p.coeff[i] == 1)
                    printf("x^%d+", i);
                else if (p.coeff[i] == 0)
                    printf("0");
                else if (p.coeff[i] != 0 && p.coeff[i] != 1)
                    printf("%.2fx^%d+", p.coeff[i], i);
            } else if (i == 1) {
                if (p.coeff[i] == 1)
                    printf("x+");
                else if (p.coeff[i] == 0)
                    printf("0");
                else if (p.coeff[i] != 0 && p.coeff[i] != 1)
                    printf("%.2fx+", p.coeff[i]);
            } else {
                if (p.coeff[i] == 0)
                    printf("0");
                else
                    printf("%.2f", p.coeff[i]);
            }
        }

    }
}

float EvalPoly(pol p, float x) {
    float image = 0, exposant = 0;
    int i = 0;
    for (i = 0; i <= p.degre; i++) {
        exposant = (float) i;/*Pour pouvoir utiliser la fonction puissance avec exposant je le convertis en float*/
        image += (p.coeff[i]) * pow(x, exposant); /*L'image est la somme des images de tous les monomes du polynomes*/
    }
    return image;
}

void AddPoly(pol p1, pol p2, pol *p) {
    int maxDegree, i;
    if (p1.degre > p2.degre)
        maxDegree = p1.degre;
    else
        maxDegree = p2.degre;
    p->degre = maxDegree; /*Le dégré du pôlynomes résultant de la somme est le maximum des dégré des polynomes opérandes*/
    for (i = 0; i <= maxDegree; i++) {
        p->coeff[i] = p1.coeff[i] +
                      p2.coeff[i]; /*Le coefficients du polynomes résultants est la sommes des coefficients des monomes de mêmes dégrés*/
    }
    printf("\nLa somme est:");
    voirPoly(*p);
}

void MultPoly(pol p1, pol p2, pol *p) {
    int i, j;
    p->degre = p1.degre +
               p2.degre;/*Le dégré du pôlynomes résultant de la multiplication est la somme des dégré des polynomes opérandes*/
    for (i = 0; i <= p->degre; i++) {
        for (j = 0; j <= i; j++) {
            p->coeff[i] += p1.coeff[j] * p2.coeff[i - j];/*Le coefficients de chaque monome du polynome résultant
            ici s'obtiens par une somme des produits des coefficients j et i-j*/
        }
    }
    printf("\nLe produit est:");
    voirPoly(*p);
}

int menu() {
    int saisie;
    /*Différents choix du ménu*/
    int choix = 0;
    printf("1-Saisir un nouveau polynome.\n");
    printf("2-Afficher les polynomes enregistre.\n");
    printf("3-Calculer l'image d'un nombre par un polynome\n");
    printf("4-Effectuer une addition de polynome\n");
    printf("5-Effectuer une multiplication de polynome\n");
    printf("6-Quitter\n");
    do {
        saisie = scanf("%d", &choix);
        vidageBuffer();
        if (saisie != 1)
            printf("Choix incorrecte, veuillez reesayer\n");
    } while (saisie != 1 || (choix <= 0 || choix > 6)); /*On s'assure que l'utilisateur effectue un choix correct*/

    return choix;
}

void gestionnaireDeChoix(int choix, pol *p, int taille) {
    static int compteur = 0;/*Compteur static à la fonction pour enrégistrer le nombre de polynomes saisi*/
    int i = 0, j = 0;
    int saisie;/*Variable pour enregistre les retour de scanf*/
    float antecedant = 0;/*variable contenant le nombre dont il faut calculer l'image*/
    pol *resulat = (pol *) calloc(1, sizeof(pol));/*Polynomes resultants des différentes opérations*/
    switch (choix) {
        case 1:
            SaisiePoly(p + compteur);/*On enregistre le pôlynomes saisis à la case suivante à chaque fois*/
            compteur++;/*On incrémente compteur de polynomes à chaque fois que l'utilisateur saisi un polynomes*/
            break;
        case 2:
            if (compteurPolynome)
                afficherListePolynome(p, compteurPolynome);
            else
                printf("Aucun polynome enregistre pour le moment\n");
            break;
        case 3:
            if (compteurPolynome) {
                do {
                    printf("De quelle nombre vouliez vous l'image ?\n");
                    saisie = scanf("%f", &antecedant);
                    vidageBuffer();
                    if (saisie != 1)
                        printf("Saisie incorrecte\n");
                } while (saisie != 1);
                afficherListePolynome(p,
                                      compteurPolynome);/*On affiche la liste des polynomes à l'utilisateur pour ainsi lui permettre de choisir un numéro de pôlynomes*/
                do {
                    printf("\nPar quelle polynome vouliez vous l'image de votre nombre(entrer le numero du polynome)\n");
                    saisie = scanf("%d", &i);
                    vidageBuffer();
                    if (saisie != 1)
                        printf("Saisie incorrecte\n");
                } while (saisie != 1);
                if (isInteger(antecedant))//Optimisation de l'affichage des nombres entier
                    printf("L'image de %d par le polynome ", (int) antecedant);
                else
                    printf("L'image de %.2f par le polynome ", antecedant);
                voirPoly(p[i - 1]);
                printf(" est %.2f ", EvalPoly(p[i - 1], antecedant));
            } else {
                printf("Aucun polynome enregistre pour le moment\n");
            }
            break;
        case 4:
            if (compteurPolynome >= 2) {
                afficherListePolynome(p, compteurPolynome);
                retour() //Macro permettant un retour à la ligne
                do {
                    printf("Quelle est le premier polynome de votre addition:(choissisez son numero)\n");
                    saisie = scanf("%d", &i);
                    vidageBuffer();
                    if (saisie != 1)
                        printf("Saisie incorrecte\n");
                } while (saisie != 1);
                do {
                    printf("Quelle est le second polynome de votre addition:(choissisez son numero)\n");
                    saisie = scanf("%d", &j);
                    vidageBuffer();
                    if (saisie != 1)
                        printf("Saisie incorrecte\n");
                } while (saisie != 1);
                AddPoly(p[i - 1], p[j - 1], resulat);
            } else {
                printf("Veuillez entrer au moins deux polynomes pour effectuer cette operation\n");
            }
            break;
        case 5:
            if (compteurPolynome >= 2) {
                afficherListePolynome(p, compteurPolynome);
                retour() //Macro permettant un retour à la ligne
                do {
                    printf("Quelle est le premier polynome de votre multiplication:(choissisez son numero)\n");
                    saisie = scanf("%d", &i);
                    vidageBuffer();
                    if (saisie != 1)
                        printf("Saisie incorrecte\n");
                } while (saisie != 1);
                do {
                    printf("Quelle est le second polynome de votre multiplication:(choissisez son numero)\n");
                    saisie = scanf("%d", &j);
                    vidageBuffer();
                    if (saisie != 1)
                        printf("Saisie incorrecte\n");
                } while (saisie != 1);
                MultPoly(p[i - 1], p[j - 1], resulat);
            } else {
                printf("Veuillez entrer au moins deux polynomes pour effectuer cette operation\n");
            }
            break;
        case 6:
            printf("Merci d'avoir utilise notre programme\n");

            exit(0);
        default:
            printf("\nChoix invalide\n");
            break;
    }
    free(resulat);
}

void afficherListePolynome(pol *p, int taille) {
    /*affiche la liste de tous les polynomes enrégistré*/
    int i = 0, j = 0;
    while (i < taille) {
        retour()
        for (j = 0; j < 4; j++) {
            if (i < taille) {
                printf("%3d-", i + 1);
                voirPoly(p[i]);
                printf(" ");
                i++;
            }

        }
    }
}

void
vidageBuffer() /*Fonction qui permet de recupérer les données qui n'ont pas été enrégistré par scanf et ont été envoyé au buffer*/
{
    int c = 0;
    while (c != '\n' && c != EOF)/*le \n et EOF signifie qu'on est arrivé à la fin du buffer*/
        c = getchar();
}
