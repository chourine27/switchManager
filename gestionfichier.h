#ifndef GESTIONFICHIER_H_INCLUDED
#define GESTIONFICHIER_H_INCLUDED

#include "informationsminuteries.h"
#include <stdio.h>
#include <stdbool.h>

bool isEmpty(FILE *file);
int copieTexteDeConfig(char* parametre, char* ligne, char* configParam);
int copieEntierDeConfig(char* parametre, char* ligne, int* configParam, int valeur);
FILE* OuvrirFichier(char* NomFichier);
void FermerFichier(FILE* fichier);
//int ChargerConfiguration(FILE* fichier);
int InitialiseValeur(char* nomFichier, char* parametre, char* valeur);
int LireParametre(char *NomFichier, char *Parametre, char *valeur);
int EcrireParametre(char* NomFichier, char* Parametre, char* Valeur);

#endif // GESTIONFICHIER_H_INCLUDED
