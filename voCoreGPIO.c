/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "constantes.h"
#include "voCoreGPIO.h"
#include "listecodes.h"

//#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Initialise la direction du port en OUT
// index : Index du port à traiter
// Retour : MSG_OK si OK, code d'erreur sinon
int voCore_gpioDirectionOut(char* index)
{
    FILE* fp;
    char buf[MAXBUF] = "Invalid parameter.";
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

//int voCore_gpioSetValue(char* index, char* value)
