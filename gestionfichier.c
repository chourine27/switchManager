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

// Control si le fichier est vide
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

// Extrait la valeur du parametre demande
// parametre : nom du parametre
// ligne : ligne contenant un parametre et une valeur
// configParam : valeur du parametre
// Retour : 0 si OK
int copieTexteDeConfig(char* parametre, char* ligne, char* configParam)
{
    char *valeurDansLaLigne;
    if(strncmp(parametre, ligne, strlen(parametre)) == 0 )
    {
        valeurDansLaLigne = strstr((char *)ligne, DELIM);
        valeurDansLaLigne = valeurDansLaLigne + strlen(DELIM);

        strcpy(configParam, valeurDansLaLigne);
        return MSG_OK;
    }
    return MSG_NotFound;
}

int copieEntierDeConfig(char* parametre, char* ligne, int* configParam, int valeur)
{
    if(strncmp(parametre, ligne, strlen(parametre)) == 0 )
    {
        *configParam = valeur;
        return MSG_OK;
    }
    return MSG_NotFound;
}

// Ouverture du fichier
// NomFichier : Nom du fichier a ouvrir
// Retour : Fichier si OK, NULL si probleme a ouverture
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

// Ferme le fichier
void FermerFichier(FILE* fichier)
{
  if (fichier == NULL)
  {
    printf("FermerFichier - Fichier non ouvert");
    return;
  }
  fclose(fichier);
}

/*int ChargerConfiguration(FILE* fichier)
{
    char ligne[MAXBUF];
    int i=0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        char *cfligne;
        cfligne = strstr((char *)ligne, DELIM);
        cfligne = cfligne + strlen(DELIM);

        if(strncmp("#", ligne, strlen("#")) == 0 || strncmp("\n", ligne, strlen("\n")) == 0)
        {
            continue;
        }
        if(copieTexteDeConfig(PARAMETRE_NOMSERVEUR, ligne, config.nomServeur) == MSG_OK)
        {
            continue;
        }
        if(copieEntierDeConfig(PARAMETRE_PORTSERVEUR, ligne, &config.portServeur, atoi(cfligne)) == MSG_OK)
        {
            continue;
        }
    }
    config.parametre = 1;
    return MSG_OK;
}*/

int LireParametre(char *NomFichier, char *Parametre, char *valeur)
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
            if(copieTexteDeConfig(Parametre, ligne, valeur) == MSG_OK)
                return MSG_OK;
            return MSG_NotAcceptable;
        }
    }
    FermerFichier(fichier);
    // Recherche sans avoir trouve le parametre
    return InitialiseValeur(NomFichier, Parametre, valeur);
}

// Initialise la valeur du parametre demande
// nomFichier : Nom du fichier dans leauel enregistrer la valeur
// parametre : Nom du parametre a initialiser
// valeur : valeur du parametre initialise
int InitialiseValeur(char* nomFichier, char* parametre, char* valeur)
{
    if(strncmp(parametre, PARAMETRE_ETATDEFAUT, strlen(PARAMETRE_ETATDEFAUT)) == 0 )
    {
        strcpy(valeur, "0");
    }
    else if(strncmp(parametre, PARAMETRE_IMAGEBOUTON, strlen(PARAMETRE_IMAGEBOUTON)) == 0 )
    {
        strcpy(valeur, INITIAL_IMAGEBOUTON);
    }
    else if(strncmp(parametre, PARAMETRE_IMAGESERVEUR, strlen(PARAMETRE_IMAGESERVEUR)) == 0 )
    {
        strcpy(valeur, INITIAL_IMAGESERVEUR);
    }
    else if(strncmp(parametre, PARAMETRE_MINUTERIEACTIVE, strlen(parametre)) == 0 )
    {
        strcpy(valeur, INITIAL_MINUTERIEACTIVE);
    }
    else if(strncmp(parametre, PARAMETRE_NOMBOUTON, strlen(PARAMETRE_NOMBOUTON)) == 0 )
    {
        strcpy(valeur, INITIAL_NOMBOUTON);
    }
    else if(strncmp(parametre, PARAMETRE_NOMBREINTERRUPTEUR, strlen(parametre)) == 0 )
    {
        strcpy(valeur, INITIAL_NOMBREINTERRUPTEUR);
    }
    else if(strncmp(parametre, PARAMETRE_NOMSERVEUR, strlen(parametre)) == 0 )
    {
        strcpy(valeur, INITIAL_NOMSERVEUR);
    }
    else if(strncmp(parametre, PARAMETRE_PORTSERVEUR, strlen(parametre)) == 0 )
    {
        strcpy(valeur, INITIAL_PORTSERVEUR);
    }
    else
    {
        // Parametre inconnu
        return MSG_Unknow;
    }
    return EcrireParametre(nomFichier, parametre, valeur);
}

int EcrireParametre(char* NomFichier, char* parametre, char* valeur)
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

    //Fichier vide
    if (isEmpty(fichier))
    {
        fprintf(fichierMiseAJour, "%s=%s\n", parametre, valeur);
    }
    else
    {
        //Lecture ligne par ligne
        while (fgets(ligne, sizeof(ligne), fichier) != NULL)
        {
            printf("%s\n", ligne);
            //Refaire le fichier
            //Est se ce param�tre
            if (strncmp(parametre, ligne, strlen(parametre)) == 0)
            {
                // mise a jour du parametre
                fprintf(fichierMiseAJour, "%s=%s\n", parametre, valeur);
                found = true;
            }
            else
            {
                fputs(ligne, fichierMiseAJour);
            }
        }
        if (!found)
        {
            fprintf(fichierMiseAJour, "%s=%s\n", parametre, valeur);
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
        printf("EcritureParametre - Erreur en renommanr le fichier temporaire");
        return -1;
    }
    return MSG_OK;
}

