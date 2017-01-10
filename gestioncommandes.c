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
    if (strncmp(commande, COMMANDE_IMAGEBOUTON, sizeof(COMMANDE_IMAGEBOUTON)-2) == 0)
    {
        return RetournerInformationConfigIndex(PARAMETRE_IMAGEBOUTON, commande, INITIAL_IMAGEBOUTON, resultat);
    }
    else if (strncmp(commande, COMMANDE_IMAGESERVEUR, sizeof(COMMANDE_IMAGESERVEUR)-2) == 0)
    {
        return RetournerInformationConfig(PARAMETRE_IMAGESERVEUR, INITIAL_IMAGESERVEUR, resultat);
    }
    else if (strncmp(commande, COMMANDE_NOMBREINTERRUPTEUR, sizeof(COMMANDE_NOMBREINTERRUPTEUR)-2) == 0)
    {
        return RetournerInformationConfig(PARAMETRE_NOMBREINTERRUPTEUR, INITIAL_NOMBREINTERRUPTEUR, resultat);
    }
    else if (strncmp(commande, COMMANDE_NOMSERVEUR, sizeof(COMMANDE_NOMSERVEUR)-2) == 0)
    {
        return RetournerInformationConfig(PARAMETRE_NOMSERVEUR, INITIAL_NOMSERVEUR, resultat);
    }
    else /* default: */
    {
        return MSG_NotImplemented;
    }
}

int RetournerInformationConfig(char* parametreALire, char* valeurDefaut, char* resultat)
{
    int retourFonction = LireParametre(CONFIG_NOMFICHIER, parametreALire, resultat);
    if (retourFonction != MSG_OK)
        return retourFonction;

    if (strcmp(resultat, "") == 0) //Resultat vide
    {
        retourFonction = EcrireParametre(CONFIG_NOMFICHIER, parametreALire, valeurDefaut);
        if (retourFonction != MSG_OK)
            return retourFonction;
        memcpy(resultat, valeurDefaut, strlen(valeurDefaut));
    }
    return MSG_OK;
}

int RetournerInformationConfigIndex (char* parametreALire, char* commande, char* valeurDefaut, char* resultat)
{
    char nbrMax[2];
    char parametreComplet[MAXBUF];
    char* index = strstr((char *)commande, "_");
    index = index + strlen("_");
    if (LireParametre(CONFIG_NOMFICHIER, PARAMETRE_NOMBREINTERRUPTEUR, nbrMax) != MSG_OK)
    {
        return MSG_InternalServerError;
    }
    if (atoi(index) > atoi(nbrMax))
    {
        return MSG_NoContent;
    }
    strcpy(parametreComplet, parametreALire);
    strcat(parametreComplet, index);
    return RetournerInformationConfig(parametreComplet, valeurDefaut, resultat);
}
