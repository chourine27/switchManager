/* ========================================================================== */
/*                                                                            */
/*   gestioncommandes.c                                                       */
/*   Matthieu CHARQUET                                                        */
/*                                                                            */
/*   Description                                                              */
/*   Gestion des commandes recu et envoi de la reponse                        */
/* ========================================================================== */

#include "configuration.h"
#include "constantes.h"
#include "gestioncommandes.h"
#include "gestionfichier.h"
#include "gestiongpio.h"
#include "listecodes.h"
#include "minuterie.h"
#include "tools.h"
#include "gestionlog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Execute la commande et retour le résultat
 * @param commande Commande reçu avec les arguments
 * @param[out] resultat Message en retour
 * @return Code résultat d'execution de la methode
 */
int ExecuterCommande(char* commande, char* resultat)
{
    char **argv = NULL;
    char *p = NULL;
    const char *spaceChar = " ";
    char parametreComplet[MAXBUF];
    int codeResultat = MSG_NotImplemented;
    // Verification si la commande contient des espaces donc des arguments
    if (strpbrk(commande, spaceChar) != 0)
    {
        // Initialise le tableau d'arguments
        argv = malloc(sizeof(char *) * MAXARG);
        codeResultat = splitLine(commande, argv);
        if (codeResultat > 9)
        {
            return MSG_BadMapping;
        }
        
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
        else if (strncmp(argv[0], COMMANDE_STATUTDEFAUTBOUTON, sizeof(COMMANDE_STATUTDEFAUTBOUTON)) == 0)
        {
            codeResultat = RetournerInformationConfigIndex(PARAMETRE_STATUTDEFAUTBOUTON, argv[1], INITIAL_STATUTDEFAUTBOUTON, resultat);
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
            if (atoi(argv[1]) > MAXBOUTON)
            {
                codeResultat = MSG_RangeUnsatisfiable;
            }
            else
            {
                codeResultat = ModifierInformationsConfig(PARAMETRE_NOMBREINTERRUPTEUR, argv[1]);
            }
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
                //Verification qu'une commande n'a pas été envoyé dans un délai pour ne pas en envoyer une nouvelle
                if(VerifierDelai(DerniereCommandeSurBouton[atoi(argv[1])]) > MINIDELAIAVANTNOUVELLECOMMANDE)
                {
                    DerniereCommandeSurBouton[atoi(argv[1])] = time(NULL);
                    codeResultat = ChangerStatutBouton (atoi(argv[1]), atoi(argv[2]));
                }
                else
                {
                    EcrireMessageInfo("gestioncommandes", "Précédente commande envoyée il y a trop peu de temps. Commande annulée");
                    codeResultat = MSG_OK;
                }
            }
        }
        else if (strncmp(argv[0], COMMANDE_SAUVEGARDERMINUTERIE, sizeof(COMMANDE_SAUVEGARDERMINUTERIE)) == 0)
        {
            if (argv[1] == NULL || argv[2] == NULL)
            {
                codeResultat = MSG_RangeUnsatisfiable;
            }
            else
            {
                // Identification de la minuterie
                strcpy(parametreComplet, PARAMETRE_MINUTERIE);
                strcat(parametreComplet, argv[1]);
                // Récupère tous les arguments déjà découpé
                char arguments[MAXBUF];
                int i=2; // 1er c'est la commande, 2ème c'est le numéro de la minuterie
                int index = 0;
                while (argv[i] != 0)
                {
                    for(int j=0; j< strlen(argv[i]); j++)
                    {
                        arguments[index++] = argv[i][j];
                    }
                    arguments[index++] = ' ';
                    i++;
                }
                // Suppression du dernier espace
                arguments[--index] = 0;
                // Sauvegarde des informations                
                codeResultat = ModifierInformationsConfig(parametreComplet, arguments);
                if (codeResultat != MSG_OK)
                {
                    return codeResultat;
                }
                //Mise à jour du cache Minuterie
                AjouterMinuterie(argv[1], arguments);
            }
            // Mise à jour de la config en mémoire
            
            // Relancer le traitement de la minuterie
        }        
        else if (strncmp(argv[0], COMMANDE_DETAILMINUTERIE, sizeof(COMMANDE_DETAILMINUTERIE)) == 0)
        {
            codeResultat = RetournerDetailMinuterie(argv[1], resultat);
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
        else if (strncmp(commande, COMMANDE_PURGERMINUTERIE, sizeof(COMMANDE_PURGERMINUTERIE)-2) == 0)
        {
            codeResultat = PurgerMinuteriesConfig();
        }
        else if (strncmp(commande, COMMANDE_NOMBREMINUTERIE, sizeof(COMMANDE_NOMBREMINUTERIE)-2) == 0)
        {
            if (sprintf(resultat, "%d", config.minuterie) < 0)
            {
                codeResultat = MSG_NotAcceptable;
            }
            else
            {
                codeResultat = MSG_OK;
            }
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

// 
// parametreALire : 
// valeurDefaut : 
// resultat : 
/**
 * Retourne la valeur du parametre
 * @param parametreALire    Nom du paramètre a lire
 * @param valeurDefaut      Valeur par defaut si le parametre est absent
 * @param[out] resultat     Retourne la valeur du parametre
 * @return                  Code résultat d'execution de la methode
 */
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

/**
 * Retourne le contenu d'un parametre ayant un index (lié à une prise)
 * @param parametreALire    Nom du champs à consulter
 * @param index             Index du paramètre à consulter
 * @param valeurDefaut      Valeur par defaut du parametre si vide
 * @param[out] resultat     Valeur du parametre reel
 * @return                  Code résultat d'execution de la methode 
 */
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

/**
 * Met a jour la valeur d'un parametre avec la valeur définie
 * @param parametreAMettreAJour Nom du parametre à mettre à jour
 * @param valeurAMettreAJour    Nouvelle valeur du paramètre
 * @return                      Code résultat d'execution de la methode
 */
int ModifierInformationsConfig (char* parametreAMettreAJour, char* valeurAMettreAJour)
{
    return EcrireParametre(CONFIG_NOMFICHIER, parametreAMettreAJour, valeurAMettreAJour);
}

/**
 * Retourne l'état d'un bouton
 * @param identifiantBouton Identifiant de la prise à consulter
 * @param[out] resultat     Etat du bouton
 * @return                  Code résultat d'execution de la methode
 */
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

/**
 * @Interne Retourne l'état d'un bouton
 * @param identifiantBouton Identifiant de la prise à consulter
 * @return                  Etat du bouton / Code erreur
 */
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

/**
 * Change le statut d'une prise
 * @param identifiantBouton Identifiant de la prise à modifier
 * @param statutBouton      Nouveau statut de la prise
 * @return                  Code résultat d'execution de la methode
 */
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

/**
 * Contrôle si l'index de la prise n'est pas en dehors des limites
 * @param identifiantBouton Identifiant de la prise à contrôler
 * @return                  Code résultat d'execution de la methode
 */
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

/**
 * Controle si le statut du bouton est eligible
 * @param statutBouton  Valeur du statut
 * @return              Code résultat d'execution de la methode
 */
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

/**
 * Efface les informations de minuterie dans le fichier et en cache
 * @return : code résultat d'execution
 */
int PurgerMinuteriesConfig()
{
    return SupprimerMinuteries();
}
