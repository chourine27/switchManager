/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "constantes.h"
#include "voCoreGPIO.h"
#include "listecodes.h"
#include "gestionlog.h"

#include <stdio.h>
#include <string.h>

static int correspondanceIndexGPIO[16];

// Initialise la direction du port en OUT
// index : Index du port à traiter
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioDirectionOut(char* index)
{
    int valeurRetour = 0;
    char indexChar[10];
    sprintf(indexChar, "/gpio%s", index);
    valeurRetour = voCore_writeFile("", EXPORTCHEMIN, index);
    if (valeurRetour != MSG_OK)
    {
        return valeurRetour;
    }
    return voCore_writeFile(DIRECTIONCHEMIN, indexChar, DIRECTIONSORTIE);
}

// Définie la valeur de sortie du port
// index : Index du port à traiter
// valeur : Valeur de sortie à définir
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioSetValueByIndex(int index, int valeur)
{
    char indexChar[10];
    char valeurChar[10];
    sprintf(indexChar, "/gpio%d", correspondanceIndexGPIO[index - 1]);
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
    EcrireMessageDebug("Valeur a ecrire dans VoCore", cheminComplet);
    EcrireMessageDebug(" avec valeur ", valeur);
    EcrireMessageDebug(" index etait ", index);
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
// Index : Index du bouton à traiter
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioInit(int index)
{
    char valeurIndex[10];
        
    sprintf(valeurIndex, "%d", correspondanceIndexGPIO[index - 1]);
    EcrireMessageDebug("Valeur index ", valeurIndex);
    sprintf(valeurIndex, "%d", correspondanceIndexGPIO[0]);
    EcrireMessageDebug("Valeur dans tableau 0", valeurIndex);
    int retourValeur = voCore_gpioDirectionOut(valeurIndex);
    if (retourValeur != MSG_OK)
    {
        return retourValeur;
    }
    return voCore_gpioSetValue(valeurIndex, INITIAL_STATUTDEFAUTBOUTON);
}

/**
 * Initialise la configuration propre au VoCore
 * @return  MSG_OK si OK, code d'erreur sinon
 */
int voCore_Init()
{
    correspondanceIndexGPIO[0] = 37;
    correspondanceIndexGPIO[1] = 38;
    correspondanceIndexGPIO[2] = 39;
    correspondanceIndexGPIO[3] = 40;
    correspondanceIndexGPIO[4] = 41;
    correspondanceIndexGPIO[5] = 42;
    correspondanceIndexGPIO[6] = 43;
    correspondanceIndexGPIO[7] = 44;
    correspondanceIndexGPIO[8] = 45;
    correspondanceIndexGPIO[9] = 46;
    correspondanceIndexGPIO[10] = 47;
    correspondanceIndexGPIO[11] = 48;
    correspondanceIndexGPIO[12] = 49;
    correspondanceIndexGPIO[13] = 50;
    correspondanceIndexGPIO[14] = 51;
    correspondanceIndexGPIO[15] = 52;
    EcrireMessageDebug("voCoreGPIO", "Correspondances GPIO initialisées");
    return MSG_OK;
}