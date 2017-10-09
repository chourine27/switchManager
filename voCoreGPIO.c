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
    FILE* fp;
    char cheminComplet[MAXBUF] = RACINECHEMIN;
    
    strcat(cheminComplet, index);
    strcat(cheminComplet, DIRECTIONCHEMIN);
    
    fp = fopen(cheminComplet, "w");
    if (fp == NULL)
    {
        return MSG_NotFound;
    }
    fwrite(DIRECTIONSORTIE, 1, strlen(DIRECTIONSORTIE) + 1, fp);
    fclose(fp);
    return MSG_OK;
}

// Définie la valeur de sortie du port
// index : Index du port à traiter
// valeur : Valeur de sortie à définir
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioSetValue(char* index, char* valeur)
{
    FILE* fp;
    char cheminComplet[MAXBUF] = RACINECHEMIN;
    
    strcat(cheminComplet, index);
    strcat(cheminComplet, VALEURCHEMIN);
    fp = fopen(cheminComplet, "w");
    if (fp == NULL)
    {
        return MSG_NotFound;
    }
    fwrite(valeur, 1, strlen(DIRECTIONSORTIE) + 1, fp);
    fclose(fp);
    return MSG_OK;
}

// Définie la direction et la valeur par defaut d'un port
// Index : Index du port à traiter
// Retour : MSGçOK si OK, code d'erreur sinon
int voCore_gpioInit(char* index)
{
    int retourValeur = voCore_gpioDirectionOut(index);
    if (retourValeur != MSG_OK)
    {
        return retourValeur;
    }
    return voCore_gpioSetValue(index, INITIAL_ETATDEFAUT);
}