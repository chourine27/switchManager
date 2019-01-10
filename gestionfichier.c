/* ========================================================================== */
/*                                                                            */
/*   gestionfichier.c                                                         */
/*   Matthieu CHARQUET                                                        */
/*                                                                            */
/*   Description                                                              */
/*   Gestion du fichier de parametre                                          */
/* ========================================================================== */
#include "gestionfichier.h"
#include "constantes.h"
#include "configuration.h"
#include "listecodes.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * isEmpty
 * 
 * Control si le fichier est vide
 * @param file : fichier ouvert
 * @return : Vrai si vide, Faux sinon
 */
bool isEmpty(FILE *file)
{
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0)
    {
        return true;
    }

    fseek(file, savedOffset, SEEK_SET);
    return false;
}

/**
 * copieTexteDeConfig
 * 
 * Extrait la valeur du parametre demande
 * @param Parametre : nom du parametre
 * @param Ligne : ligne contenant un parametre et une valeur
 * @param @out ConfigParam : valeur du parametre
 * @return : Code résultat d'execution
 */
int copieTexteDeConfig(char* Parametre, char* Ligne, char* ConfigParam)
{
    char *valeurDansLaLigne;
    if(strncmp(Parametre, Ligne, strlen(Parametre)) == 0 )
    {
        valeurDansLaLigne = strstr((char *)Ligne, DELIM);
        valeurDansLaLigne = valeurDansLaLigne + strlen(DELIM);

        strcpy(ConfigParam, valeurDansLaLigne);
        return MSG_OK;
    }
    return MSG_NotFound;
}

/**
 * OuvrirFichier
 * 
 * Ouvre le fichier de config
 * @param NomFichier : Nom du fichier de configuration à ouvrir
 * @return Fichier de config ouvert ou NULL si erreur
 */
FILE* OuvrirFichier(char* NomFichier)
{
    FILE* fichier = NULL;
    if (NomFichier == NULL)
    {
        printf("OuverirFichier - Nom de fichier non d�fini");
        return NULL;
    }
    fichier = fopen(NomFichier, "a+");
    if (fichier != NULL)
    {
        rewind(fichier);
        return fichier;
    }
    else
    {
        printf("OuvrirFichier - Erreur � l'ouverture du fichier : %s", NomFichier);
        return NULL;
    }
}

/**
 * FermerFichier
 * 
 * Ferme le fichier ouvert
 * @param Fichier : Fichier à fermer
 */
void FermerFichier(FILE* Fichier)
{
  if (Fichier == NULL)
  {
    printf("FermerFichier - Fichier non ouvert");
    return;
  }
  fclose(Fichier);
}

/**
 * LireParametre
 * 
 * Lecture d'un paramètre dans le fichier de config
 * @param NomFichier : Nom du fichier de config
 * @param Parametre : Nom du paramètre à chercher
 * @param @out Valeur : Valeur du paramètre
 * @return : Code résultat d'execution
 */
int LireParametre(char *NomFichier, char *Parametre, char *Valeur)
{
    FILE* fichier = OuvrirFichier(NomFichier);
    char ligne[MAXBUF];
    int i=0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        if(strncmp("#", ligne, strlen("#")) == 0 || strncmp("\n", ligne, strlen("\n")) == 0)
        {
            continue;
        }
        if (strncmp(Parametre, ligne, strlen(Parametre)) == 0)
        {
            if(copieTexteDeConfig(Parametre, ligne, Valeur) == MSG_OK)
                return MSG_OK;
            return MSG_NotAcceptable;
        }
    }
    FermerFichier(fichier);
    // Recherche sans avoir trouve le parametre
    return InitialiseValeur(NomFichier, Parametre, Valeur);
}

/**
 * InitialiseValeur
 * 
 * Initialise la valeur du parametre demande
 * @param NomFichier : Nom du fichier dans leauel enregistrer la valeur
 * @param Parametre : Nom du parametre a initialiser
 * @param @out Valeur : Valeur du parametre initialise
 * @return : Code résultat d'execution
 */
int InitialiseValeur(char* NomFichier, char* Parametre, char* Valeur)
{
    if(strncmp(Parametre, PARAMETRE_ETATDEFAUT, strlen(PARAMETRE_ETATDEFAUT)) == 0 )
    {
        strcpy(Valeur, "0");
    }
    else if(strncmp(Parametre, PARAMETRE_IMAGEBOUTON, strlen(PARAMETRE_IMAGEBOUTON)) == 0 )
    {
        strcpy(Valeur, INITIAL_IMAGEBOUTON);
    }
    else if(strncmp(Parametre, PARAMETRE_IMAGESERVEUR, strlen(PARAMETRE_IMAGESERVEUR)) == 0 )
    {
        strcpy(Valeur, INITIAL_IMAGESERVEUR);
    }
    else if(strncmp(Parametre, PARAMETRE_MINUTERIEACTIVE, strlen(Parametre)) == 0 )
    {
        strcpy(Valeur, INITIAL_MINUTERIEACTIVE);
    }
    else if(strncmp(Parametre, PARAMETRE_NOMBOUTON, strlen(PARAMETRE_NOMBOUTON)) == 0 )
    {
        strcpy(Valeur, INITIAL_NOMBOUTON);
    }
    else if(strncmp(Parametre, PARAMETRE_NOMBREINTERRUPTEUR, strlen(Parametre)) == 0 )
    {
        strcpy(Valeur, INITIAL_NOMBREINTERRUPTEUR);
    }
    else if(strncmp(Parametre, PARAMETRE_NOMSERVEUR, strlen(Parametre)) == 0 )
    {
        strcpy(Valeur, INITIAL_NOMSERVEUR);
    }
    else if(strncmp(Parametre, PARAMETRE_PORTSERVEUR, strlen(Parametre)) == 0 )
    {
        strcpy(Valeur, INITIAL_PORTSERVEUR);
    }
    else if(strncmp(Parametre, PARAMETRE_NIVEAULOG, strlen(Parametre)) == 0 )
    {
        strcpy(Valeur, INITIAL_NIVEAULOG);
    }
    else
    {
        // Parametre inconnu
        return MSG_Unknow;
    }
    return EcrireParametre(NomFichier, Parametre, Valeur);
}

/**
 * EcrireParametre
 * 
 * Ajoute ou met à jour la valeur d'un paramètre pour le sauvegarder dans le fichier de config
 * @param NomFichier : Nom du fichier de config à traiter
 * @param Parametre : Paramètre à mettre à jour
 * @param Valeur : Valeur du paramètre à sauvegarder
 * @return : Code résultat d'execution
 */
int EcrireParametre(char* NomFichier, char* Parametre, char* Valeur)
{
    return traitementParametre(NomFichier, Parametre, Valeur);
}

/**
 * EffacerParametre
 * 
 * Efface un paramètre du fichier de configuration
 * @param NomFichier : Nom du fichier de configuration à traiter
 * @param parametre : Paramètre à retire
 * @return : code résultat d'execution
 */
int EffacerParametre(char* NomFichier, char* parametre)
{
    return traitementParametre(NomFichier, parametre, 0);
}

/**
 * traitementParametre
 * 
 * Permet d'ajouter, modifier, supprimer un paramètre dans le fichier de configuration
 * @param NomFichier : Nom du fichier de configuration à mettre à jour
 * @param Parametre : Nom du paramètre à traiter
 * @param Valeur : Valeur à mettre à jour (mettre 0 si suppression)
 * @return code résultat d'execution
 */
int traitementParametre(char* NomFichier, char* Parametre, char* Valeur)
{
    FILE* fichier = OuvrirFichier(NomFichier);
    FILE* fichierMiseAJour = OuvrirFichier(FICHIERTEMPORAIRE);
    char ligne[MAXBUF];
    char** contenuLigne;
    size_t len = 0;
    ssize_t read;
    bool found = false;

    if (fichier == NULL)
    {
        printf("EcrireParametre - Problème d'ouverture du fichier : %s", NomFichier);
        return -1;
    }

    //Fichier vide et Traitement n'est pas de supprimer un paramètre
    if (isEmpty(fichier) && Valeur != 0)
    {
        fprintf(fichierMiseAJour, "%s%s%s\n", Parametre, DELIM, Valeur);
    }
    else
    {
        //Lecture ligne par ligne
        while (fgets(ligne, sizeof(ligne), fichier) != NULL)
        {
            printf("%s", ligne);
            //Refaire le fichier
            //Est se ce paramètre et sauvegarde pas déjà faite
            if (!found && strncmp(Parametre, ligne, strlen(Parametre)) == 0)
            {
                if (Valeur == 0) // Il faut supprimer la ligne
                {
                    continue;
                }
                else // Il faut mettre à jour le paramètre
                {
                    fprintf(fichierMiseAJour, "%s%s%s\n", Parametre, DELIM, Valeur);
                }
                found = true;
            }
            else
            {
                fputs(ligne, fichierMiseAJour);
            }
        }
        if (!found && Valeur != 0) // C'est un nouveau paramètre, il faut l'ajouter
        {
            fprintf(fichierMiseAJour, "%s%s%s\n", Parametre, DELIM, Valeur);
        }
    }
    FermerFichier(fichier);
    FermerFichier(fichierMiseAJour);
    if(remove(NomFichier) != 0)
    {
        printf("EcritureParametre - Erreur a la suppression du fichier origine");
        return -1;
    }
    if(rename(FICHIERTEMPORAIRE, NomFichier) != 0)
    {
        printf("EcritureParametre - Erreur en rennomant le fichier temporaire");
        return -1;
    }
    return MSG_OK;
}