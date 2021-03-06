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
#include "gestiongpio.h"
#include "listecodes.h"
#include "constantes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Execute la commande et retour le résultat
// commande : Commande reçu avec les arguments
// resultat : Message en retour
// Retour : code résultat d'execution de la methode
int ExecuterCommande(char* commande, char* resultat)
{
    char **argv = NULL;
    char *p = NULL;
    const char *spaceChar = " ";
    char parametreComplet[MAXBUF];
    int codeResultat = MSG_NotImplemented;
    size_t i = 0;
    // Verification si la commande contient des espaces
//    if (strstr(commande, spaceChar) != NULL)
    if (strpbrk(commande, spaceChar) != 0)
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
        // retrait du retour chariot pour le dernier parametre
        if (i > 0)
        {
            argv[i-1][strlen(argv[i-1])-1] = 0;
        }
        argv[i] = NULL;
        
        if (strncmp(argv[0], COMMANDE_CHANGERIMAGESERVEUR, sizeof(COMMANDE_CHANGERIMAGESERVEUR)) == 0)
        {
            strcpy(parametreComplet, PARAMETRE_IMAGESERVEUR);
            strcat(parametreComplet, argv[1]);
            codeResultat = ModifierInformationsConfig(PARAMETRE_IMAGESERVEUR, argv[1]);
        }
        else if (strncmp(argv[0], COMMANDE_NOMBOUTON, sizeof(COMMANDE_NOMBOUTON)) == 0)
        {
            codeResultat = RetournerInformationConfigIndex(PARAMETRE_NOMBOUTON, argv[1], INITIAL_NOMBOUTON, resultat);
        }
        else if (strncmp(argv[0], COMMANDE_IMAGEBOUTON, sizeof(COMMANDE_IMAGEBOUTON)) == 0)
        {
            codeResultat = RetournerInformationConfigIndex(PARAMETRE_IMAGEBOUTON, argv[1], INITIAL_IMAGEBOUTON, resultat);
        }
        else if (strncmp(argv[0], COMMANDE_CHANGERIMAGEBOUTON, sizeof(COMMANDE_CHANGERIMAGEBOUTON)) == 0)
        {
            if (argv[1] == NULL || argv[2] == NULL)
            {
                codeResultat = MSG_RangeUnsatisfiable;
            }
            else
            {
                strcpy(parametreComplet, PARAMETRE_IMAGEBOUTON);
                strcat(parametreComplet, argv[1]);
                codeResultat = ModifierInformationsConfig(parametreComplet, argv[2]);
            }
        }
        else if (strncmp(argv[0], COMMANDE_CHANGERNOMBREINTERRUPTEUR, sizeof(COMMANDE_CHANGERNOMBREINTERRUPTEUR)) == 0)
        {
            codeResultat = ModifierInformationsConfig(PARAMETRE_NOMBREINTERRUPTEUR, argv[1]);
        }
        else if (strncmp(argv[0], COMMANDE_RENOMMERNOMBOUTON, sizeof(COMMANDE_RENOMMERNOMBOUTON)) == 0)
        {
            if (argv[1] == NULL || argv[2] == NULL)
            {
                codeResultat = MSG_RangeUnsatisfiable;
            }
            else
            {
                strcpy(parametreComplet, PARAMETRE_NOMBOUTON);
                strcat(parametreComplet, argv[1]);
                codeResultat = ModifierInformationsConfig(parametreComplet, argv[2]);
            }
        }
        else if (strncmp(argv[0], COMMANDE_RENOMMERSERVEUR, sizeof(COMMANDE_RENOMMERSERVEUR)) == 0)
        {
            codeResultat = ModifierInformationsConfig(PARAMETRE_NOMSERVEUR, argv[1]);
        }
        else if (strncmp(argv[0], COMMANDE_STATUTBOUTON, sizeof(COMMANDE_STATUTBOUTON)) == 0)
        {
            codeResultat = RetournerEtatBouton (atoi(argv[1]), resultat);
        }
        else if (strncmp(argv[0], COMMANDE_CHANGESTATUTBOUTON, sizeof(COMMANDE_CHANGESTATUTBOUTON)) == 0)
        {
            if (argv[1] == NULL || argv[2] == NULL)
            {
                codeResultat = MSG_RangeUnsatisfiable;
            }
            else
            {
                codeResultat = ChangerStatutBouton (atoi(argv[1]), atoi(argv[2]));
            }
        }
        else
        { // Commande inconnue
            codeResultat = MSG_BadRequest;
        }
    }
    else
    { // Commande sans argument
        if (strncmp(commande, COMMANDE_IMAGESERVEUR, sizeof(COMMANDE_IMAGESERVEUR)-2) == 0)
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
        else
        {
            codeResultat = MSG_BadRequest;
        }
    }
    free(argv);
    free(p);
    if (codeResultat != MSG_OK)
        sprintf(resultat, "%d", codeResultat);
    else
    {
        if (strcmp(resultat, "") == 0) //Résultat vide
        {
            sprintf(resultat, "%d", MSG_OK);
        }
    }
    return codeResultat;
}

// Retourne la valeur du parametre
// parametreALire : Nom du paramètre a lire
// valeurDefaut : Valeur par defaut si le parametre est absent
// resultat : retourne la valeur du parametre
int RetournerInformationConfig(char* parametreALire, char* valeurDefaut, char* resultat)
{
    int retourFonction = LireParametre(CONFIG_NOMFICHIER, parametreALire, resultat);
    if (retourFonction != MSG_OK)
        return retourFonction;

    if (strcmp(resultat, "") == 0) //Résultat vide
    {
        retourFonction = ModifierInformationsConfig(parametreALire, valeurDefaut);
        if (retourFonction != MSG_OK)
            return retourFonction;
        strcpy(resultat, valeurDefaut);
    }
    return MSG_OK;
}

// Retourne le contenu d'un parametre ayant un index (lié à une prise)
// parametreALire : Nom du champs à consulter
// index : Index du paramètre à consulter
// valeurParDefaut : Valeur par defaut du parametre si vide
// resultat : Valeur du parametre reel (sortie)
int RetournerInformationConfigIndex (char* parametreALire, char* index, char* valeurDefaut, char* resultat)
{
    int codeRetour;
    char parametreComplet[MAXBUF];
    
    codeRetour = IdentifiantBoutonPlosible(atoi(index));
    if (codeRetour != MSG_OK)
    {
        return codeRetour;
    }
    strcpy(parametreComplet, parametreALire);
    strcat(parametreComplet, index);
    return RetournerInformationConfig(parametreComplet, valeurDefaut, resultat);
}

// Met a jour la valeur d'un parametre avec la valeur définie
// parametreAMettreAJour : Nom du parametre à mettre à jour
// valeurAMettreAJour : Nouvelle valeur du paramètre
int ModifierInformationsConfig (char* parametreAMettreAJour, char* valeurAMettreAJour)
{
    return EcrireParametre(CONFIG_NOMFICHIER, parametreAMettreAJour, valeurAMettreAJour);
}

// Retourne l'état d'un bouton
// identifiantBouton : Identifiant de la prise à consulter
// resultat : Etat du bouton (sortie)
// sortie : code erreur
int RetournerEtatBouton (int identifiantBouton, char* resultat)
{
    int codeRetour = retournerEtatBouton (identifiantBouton);
    if (codeRetour == CONFIG_ALLUME || codeRetour == CONFIG_ETEINT)
    {
        sprintf(resultat, "%d", codeRetour);
        codeRetour = MSG_OK;
    }
    return codeRetour;
}

// [Interne]
// Retourne l'état d'un bouton
// identifiantBouton : Identifiant de la prise à consulter
// Sortie : Etat du bouton / Code erreur
int retournerEtatBouton (int identifiantBouton)
{
    //Verification de l'index va pas faire planter
    int codeRetour = IdentifiantBoutonPlosible(identifiantBouton);
    if (codeRetour != MSG_OK)
    {
        return codeRetour;
    }
    
    return EtatRelai(identifiantBouton);
}

// Change le statut d'une prise
// identifiantBouton : Identifiant de la prise à modifier
// statutBouton : Nouveau statut de la prise
// sortie : code résultat d'execution
int ChangerStatutBouton (int identifiantBouton, int statutBouton)
{
    //Verification de l'index va pas faire planter
    int codeRetour = IdentifiantBoutonPlosible(identifiantBouton);
    if (codeRetour != MSG_OK)
        return codeRetour;
    
    //Verification du statut à assigner
    codeRetour = StatutBoutonPlosible(statutBouton);
    if (codeRetour != MSG_OK)
        return codeRetour;
    
    if (statutBouton == CONFIG_ALLUME)
    {
        codeRetour = ActiverRelai(identifiantBouton);
    }
    else if (statutBouton == CONFIG_ETEINT)
    {
        codeRetour = DesactiverRelai(identifiantBouton);
    }
    else
    {
        return MSG_NotAcceptable;
    }

    return codeRetour;
}

// Contrôle si l'index de la prise n'est pas en dehors des limites
// identifiantBouton : Identifiant de la prise à contrôler
// sortie : Code erreur
int IdentifiantBoutonPlosible (int identifiantBouton)
{
    char nbrMax[2];
    int indexMax;
    
    if (LireParametre(CONFIG_NOMFICHIER, PARAMETRE_NOMBREINTERRUPTEUR, nbrMax) != MSG_OK)
    {
        return MSG_BandwidthLimit;
    }
    indexMax = atoi(nbrMax);
    if (identifiantBouton > indexMax)
    {
        return MSG_RangeUnsatisfiable;
    }
    if (identifiantBouton < 1)
    {
        return MSG_Forbidden;
    }
    return MSG_OK;    
}

// Controle si le statut du bouton est eligible
// statutBouton : valeur du statut
// sorite : Code erreur
int StatutBoutonPlosible (int statutBouton)
{
    if (statutBouton == CONFIG_ALLUME || statutBouton == CONFIG_ETEINT)
    {
        return MSG_OK;
    }
    else
    {
        return MSG_BadRequest;
    }
}
