/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "constantes.h"
#include "voCoreGPIO.h"
#include "listecodes.h"

#include <stdio.h>
#include <string.h>
//#include <c++/6/bits/regex.h>

// Initialise la direction du port en OUT
// index : Index du port à traiter
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioDirectionOut(char* index)
{
    return voCore_writeFile(DIRECTIONCHEMIN, index, DIRECTIONSORTIE);
}

// Définie la valeur de sortie du port
// index : Index du port à traiter
// valeur : Valeur de sortie à définir
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioSetValueByIndex(int index, int valeur)
{
    char indexChar[10];
    char valeurChar[10];
    sprintf(indexChar, "%d", index);
    sprintf(valeurChar, "%d", valeur);
    return voCore_gpioSetValue(indexChar, valeurChar);
}

// Définie la valeur de sortie du port
// index : Index du port à traiter en char
// valeur : Valeur de sortie à définir
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioSetValue(char* index, char* valeur)
{
    return voCore_writeFile(VALEURCHEMIN, index, valeur);
}

// Ecrit dans un fichier specifique au GPIO
// cheminFichier : Chemin du fichier à traiter
// index : Index de la GPIO
// valeur : valeur à écrire dans le fichier
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_writeFile(char* cheminFichier, char* index, char* valeur)
{
    FILE* fp;
    char cheminComplet[MAXBUF] = RACINECHEMIN;
    
    strcat(cheminComplet, index);
    strcat(cheminComplet, cheminFichier);
    fp = fopen(cheminComplet, "w");
    if (fp == NULL)
    {
        return MSG_NotFound;
    }
    fwrite(valeur, 1, strlen(valeur) + 1, fp);
    fclose(fp);
    fp=NULL;
    return MSG_OK;
}

// Définie la direction et la valeur par defaut d'un port
// Index : Index du port à traiter
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioInit(char* index)
{
    int retourValeur = voCore_gpioDirectionOut(index);
    if (retourValeur != MSG_OK)
    {
        return retourValeur;
    }
    return voCore_gpioSetValue(index, INITIAL_ETATDEFAUT);
}