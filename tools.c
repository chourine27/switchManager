/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "tools.h"
#include "constantes.h"
#include "listecodes.h"

#include <stdlib.h>

// Découpage d'une chaine de caractère avec suppression du caractère fin de ligne
// content : Contenu de la ligne à découper
// result : tableau de chaque information
// Retour : Nombre d'information dans le tableau
int splitLine(char* content, char** result)
{
    char *p;
    size_t i=0;
    // Decoupage de la commande et des arguments
    //result = malloc(sizeof(char *) * MAXARG);
    // Récuperation de la commande
    p = strtok(content, SEPARINFO);
    while(p != NULL)
    {
       // p est un pointeur sur une chaine qui contient exactement l'argument i
       if(i < MAXARG)
       {
          result[i] = malloc(sizeof(char) * (1+strlen(p)));
          strcpy(result[i], p);
          i++;
       }
       else
          break; // Trop d'arguments
        // Nouvel appel avec 1er argument NULL afin de poursuivre le découpage
        // Possible de changer de délimiteur
       p = strtok(NULL, SEPARINFO);
    }
    // retrait du retour chariot pour le dernier parametre
    if (i > 0)
    {
        result[i-1][strlen(result[i-1])-1] = 0;
    }
    result[i] = NULL;
    return i;
}