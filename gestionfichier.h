#ifndef GESTIONFICHIER_H_INCLUDED
#define GESTIONFICHIER_H_INCLUDED

#include "informationsminuteries.h"
#include <stdio.h>
#include <stdbool.h>

bool isEmpty(FILE *file);
int copieTexteDeConfig(char* Parametre, char* Ligne, char* ConfigParam);
int copieEntierDeConfig(char* Parametre, char* Ligne, int* ConfigParam, int Valeur);
FILE* OuvrirFichier(char* NomFichier);
void FermerFichier(FILE* Fichier);
int InitialiseValeur(char* NomFichier, char* Parametre, char* Valeur);
int LireParametre(char *NomFichier, char *Parametre, char *Valeur);
int EcrireParametre(char* NomFichier, char* Parametre, char* Valeur);
int EffacerParametre(char* NomFichier, char* Parametre);
int traitementParametre(char* NomFichier, char* Parametre, char* Valeur);

#endif // GESTIONFICHIER_H_INCLUDED
