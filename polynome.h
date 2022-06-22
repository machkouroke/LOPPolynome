/*
polynome.h

Par Machkour Oke
Role:Contient les prototype  des fonctions et les declaration des structrure sur les pôlynomes de l'exercice 1
*/
#ifndef POLYNOME_H_INCLUDED
#define POLYNOME_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define DegreMax 20

typedef struct Polynome
{
    int degre;/*-1pour le polynome nul*/
    float coeff[DegreMax+1];
}pol;
int isInteger(float a);
void NulPoly(pol *p);
void SaisiePoly(pol *p);
void voirPoly(pol p);
float EvalPoly(pol p,float x);
void AddPoly(pol p1,pol p2,pol *p);
void MultPoly(pol p1,pol p2,pol *p);
int menu();
void gestionnaireDeChoix(int choix,pol *p,int taille);
void afficherListePolynome(pol *p,int taille);
void vidageBuffer();
#endif // POLYNOME_H_INCLUDED
