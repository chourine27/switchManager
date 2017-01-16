/* ========================================================================== */
/*                                                                            */
/*   gestioncommandes.c                                                       */
/*   Matthieu CHARQUET                                                        */
/*                                                                            */
/*   Description                                                              */
/*   Gestion des commandes recu et envoi de la reponse                        */
/* ========================================================================== */

#include "gestioncommandes.h"
#include "gestionfichier.h"
#include "listecodes.h"
#include "constantes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ExecuterCommande(char* commande, char* resultat)
{
    char **argv = NULL;
    char *p = NULL;
    char spaceChar[1] = " ";
    int codeResultat = MSG_NotImplemented;
    size_t i = 0;
    // Verification si la commande contient des espaces
    if (strstr(commande, spaceChar) != NULL)
    {
        // Decoupage de la commande et des arguments
        argv = malloc(sizeof(char *) * MAXARG);
        // Récuperation de la commande
        p = strtok(commande, spaceChar);
        while(p != NULL)
        {
           // p est un pointeur sur une chaine qui contient exactement l'argument i
           if(i < MAXARG)
           {
              argv[i] = malloc(sizeof(char) * (1+strlen(p)));
              strcpy(argv[i], p);
              i++;
           }
           else
              break; // Trop d'arguments
            // Nouvel appel avec 1er argument NULL afin de poursuivre le découpage
            // Possible de changer de délimiteur
           p = strtok(NULL, " ");
        }
        argv[i] = NULL;
        
        if (strncmp(argv[0], COMMANDE_RENOMMERSERVEUR, sizeof(COMMANDE_RENOMMERSERVEUR)-2) == 0)
        {
            codeResultat = ModifierInformationsConfig(PARAMETRE_NOMSERVEUR, argv[1]);
            strcpy(resultat, "BIP");
        }
    }
    else
    {
        if (strncmp(commande, COMMANDE_IMAGEBOUTON, sizeof(COMMANDE_IMAGEBOUTON)-2) == 0)
        {
            codeResultat = RetournerInformationConfigIndex(PARAMETRE_IMAGEBOUTON, commande, INITIAL_IMAGEBOUTON, resultat);
        }
        else if (strncmp(commande, COMMANDE_IMAGESERVEUR, sizeof(COMMANDE_IMAGESERVEUR)-2) == 0)
        {
            codeResultat = RetournerInformationConfig(PARAMETRE_IMAGESERVEUR, INITIAL_IMAGESERVEUR, resultat);
        }
        else if (strncmp(commande, COMMANDE_NOMBREINTERRUPTEUR, sizeof(COMMANDE_NOMBREINTERRUPTEUR)-2) == 0)
        {
            codeResultat = RetournerInformationConfig(PARAMETRE_NOMBREINTERRUPTEUR, INITIAL_NOMBREINTERRUPTEUR, resultat);
        }
        else if (strncmp(commande, COMMANDE_NOMSERVEUR, sizeof(COMMANDE_NOMSERVEUR)-2) == 0)
        {
            codeResultat = RetournerInformationConfig(PARAMETRE_NOMSERVEUR, INITIAL_NOMSERVEUR, resultat);
        }
    }
    free(argv);
    free(p);
    return codeResultat;
}

int RetournerInformationConfig(char* parametreALire, char* valeurDefaut, char* resultat)
{
    int retourFonction = LireParametre(CONFIG_NOMFICHIER, parametreALire, resultat);
    if (retourFonction != MSG_OK)
        return retourFonction;

    if (strcmp(resultat, "") == 0) //Resultat vide
    {
        retourFonction = ModifierInformationsConfig(parametreALire, valeurDefaut);
        if (retourFonction != MSG_OK)
            return retourFonction;
        //memcpy(resultat, valeurDefaut, strlen(valeurDefaut));
        strcpy(resultat, valeurDefaut);
    }
    return MSG_OK;
}

// Retourne le contenu d'un parametre ayant un index (lié à une prise)
// parametreALire : Nom du champs à consulter
// commande : Commande qui a été executé
// valeurParDefaut : Valeur par defaut du parametre si vide
// resultat : Valeur du parametre reel (sortie)
int RetournerInformationConfigIndex (char* parametreALire, char* commande, char* valeurDefaut, char* resultat)
{
    char nbrMax[2];
    char parametreComplet[MAXBUF];
    char* index = strstr((char *)commande, "_");
    index = index + strlen("_");
    if (LireParametre(CONFIG_NOMFICHIER, PARAMETRE_NOMBREINTERRUPTEUR, nbrMax) != MSG_OK)
    {
        return MSG_BandwidthLimit;
    }
    if (atoi(index) > atoi(nbrMax))
    {
        return MSG_NoContent;
    }
    strcpy(parametreComplet, parametreALire);
    strcat(parametreComplet, index);
    return RetournerInformationConfig(parametreComplet, valeurDefaut, resultat);
}

// Met a jour la valeur d'un parametre avec la valeur définie
int ModifierInformationsConfig (char* parametreAMettreAJour, char* valeurAMettreAJour)
{
    return EcrireParametre(CONFIG_NOMFICHIER, parametreAMettreAJour, valeurAMettreAJour);
}