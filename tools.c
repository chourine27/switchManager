/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "tools.h"
#include "constantes.h"
#include "listecodes.h"
#include "gestionlog.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    result[i] = NULL;
    return i;
}

/**
 * splitInformationInt
 * Découpe une chaine de caractère en tableau d'entier
 * @param content La chaine de caractère
 * @param result le tableau d'entier
 * @return Le nombre de chaine dans le tableau
 */
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

/**
 * splitInformationString
 * Découpe une chaine de caractère en un tableau de chaine avec le séparateur prédéfini
 * @param content Chaine de caractère à découper
 * @param result Tableau de chaine découpée
 * @return Nombre de valeur dans le tableau
 */
int splitInformationString(char* content, char** result)
{
    return splitString(content, result, SEPARVALEUR);
}

/**
 * VerifierDelai
 * 
 * Identifie une différence un time_t et maintenant
 * @param derniereAction La valeur time_t initiale
 * @return Différence entre 2 time_t
 */
int VerifierDelai(int derniereAction)
{
    return time(NULL) - derniereAction;   
}