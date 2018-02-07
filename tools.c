/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "tools.h"
#include "constantes.h"
#include "listecodes.h"

#include <stdlib.h>
#include <string.h>

// Découpage d'une chaine de caractère avec suppression du caractère fin de ligne
// content : Contenu de la ligne à découper
// result : tableau de chaque information
// Retour : Nombre d'information dans le tableau
int splitLine(char* content, char** result)
{
    return splitString(content, result, SEPARINFO);
}

/**
 * splitString
 * 
 * Découpe une chaine de caractère en tableau de chaine
 * @param content Le contenu à découper
 * @param result Le tableau de résultat
 * @param separator le séparateur de chaine
 * @return Le nombre de chaine dans le tableau
 */
int splitString(char* content, char** result, char *separator)
{
    char *p;
    size_t i=0;
    // retire les caractères spéciaux de fin de ligne
    if (content[strlen(content)-1] == '\n')
        {
            content[strlen(content)-1] = '\0';
            //content = realloc(content, sizeof(char) * (strlen(content) - 1));
        } 
    // Récuperation de la commande
    p = strtok(content, separator);
    while(p != NULL)
    {
       // p est un pointeur sur une chaine qui contient exactement l'argument i
       if(i < MAXARG)
       {
          result[i] = malloc(sizeof(char) * (strlen(p)));
          strcpy(result[i], p);
          i++;
       }
       else
          break; // Trop d'arguments
        // Nouvel appel avec 1er argument NULL afin de poursuivre le découpage
        // Possible de changer de délimiteur
       p = strtok(NULL, separator);
    }
    // retrait du retour chariot pour le dernier parametre
    if (i > 0)
    {
/*        if (result[i-1][strlen(result[i-1])-1] == '\n' || result[i-1][strlen(result[i-1])-1] == '\\')
        {
            result[i-1][strlen(result[i-1])-1] = 0;
            result[i-1] = realloc(result[i-1], sizeof(char) * (strlen(result[i-1]) - 1));
        } */
    }
    result[i] = NULL;
    return i;
}

int splitInformationInt(char *content, int *result)
{
    char *p;
    size_t i=0;
    p = strtok(content, SEPARVALEUR);
    while(p != NULL)
    {
       // p est un pointeur sur une chaine qui contient les valeurs
       if(i < MAXARG)
       {
          result = realloc(result, sizeof(int) * (i+1));
          if (result == NULL)
          {
              return MSG_UnprocessableEntity;
          }
          result[i] = atoi(p);
          i++;
       }
       else
          break; // Trop d'arguments
        // Nouvel appel avec 1er argument NULL afin de poursuivre le découpage
        // Possible de changer de délimiteur
       p = strtok(NULL, SEPARVALEUR);
    }
    return i;    
}

int splitInformationString(char* content, char** result)
{
    return splitString(content, result, SEPARVALEUR);
}