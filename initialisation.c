/* ========================================================================== */
/*                                                                            */
/*   initialisation.c                                                         */
/*   Matthieu CHARQUET                                                        */
/*                                                                            */
/*   Description                                                              */
/*   Initialisation au démarrage ou après évolution materiel                  */
/* ========================================================================== */


#include "initialisation.h"
#include "constantes.h"
#include "gestioncommandes.h"
#include "listecodes.h"
#include "voCoreGPIO.h"
#include "minuterie.h"
#include "configuration.h"
#include "gestionlog.h"
#include "gestionfichier.h"
#include "raspberryGPIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Initilise le fichier de config si il n'existe pas
// Retour : MSG_OK si OK, code d'erreur sinon
int initConfig()
{
    char resultat[BUFLEN];
    int codeResultat;

    codeResultat = RetournerInformationConfig(PARAMETRE_NOMSERVEUR, INITIAL_NOMSERVEUR, resultat);
    codeResultat = RetournerInformationConfig(PARAMETRE_NOMBREINTERRUPTEUR, INITIAL_NOMBREINTERRUPTEUR, resultat);
    
    //Pour pouvoir utiliser tout le temps realloc, init à NULL
    config.infoMinuteries = NULL;
    codeResultat = ChargerMinuterie();
    
    for (int i=0; i< MAXBOUTON; i++)
    {
        DerniereCommandeSurBouton[i] = time(NULL);
    }
}

// Initialise les ports en sortie avec la valeur par defaut
// Retour : MSG_OK si OK, code d'erreur sinon
int initGPIO()
{
    char resultat[BUFLEN];
    char index[BUFLEN];
    int codeResultat;
    int nbrPort = 0;
    codeResultat = RetournerInformationConfig(PARAMETRE_NOMBREINTERRUPTEUR, INITIAL_NOMBREINTERRUPTEUR, resultat);
    if (codeResultat != MSG_OK)
    {
        return codeResultat;
    }
    nbrPort = atoi(resultat);
    EcrireMessageDebug("initialisation", "Chargement du nombre de bouton OK");
#ifdef VOCORE
    voCore_Init();
#elif REMOTE
    InitWiringPiGPIO();
    EcrireMessageDebug("initialisation", "InitWiringPiGPIO OK");
    EcrireMessageDebug("initialisation", resultat);
#endif
    for(int i=0; i<nbrPort; i++)
    {
        sprintf(index, "%d", i+1);
        //Initialise le port en sortie avec la valeur par défaut
#ifdef VOCORE
        voCore_gpioInit(i);
#endif
        EcrireMessageDebug("initialisation", index);
        //Initialise le fichier de configuration avec le nom du bouton
        RetournerInformationConfigIndex(PARAMETRE_NOMBOUTON, index, INITIAL_NOMBOUTON, resultat);
        EcrireMessageDebug("initialisation", "Initialisation du nom du bouton");
        //Initialise le fichier de configuration avec l'image du bouton
        RetournerInformationConfigIndex(PARAMETRE_IMAGEBOUTON, index, INITIAL_IMAGEBOUTON, resultat);
        EcrireMessageDebug("initialisation", "Initialisation du nom de l'image du bouton");
        //Initialise le statut par defaut d'un bouton ou initialise le fichier de configuration avec la valeur par defaut du bouton
        codeResultat = RetournerInformationConfigIndex(PARAMETRE_STATUTDEFAUTBOUTON, index, INITIAL_STATUTDEFAUTBOUTON, resultat);
        EcrireMessageDebug("initialisation", "Valeur par defaut du bouton chargée");
        if (codeResultat == MSG_OK)
        {
            ChangerStatutBouton(i, atoi(resultat));
            EcrireMessageDebug("initialisation", "Valeur par defaut du bouton initialisée");
        }
        else
        {
            EcrireMessageErreur("initialisation", "Erreur à l'initialisation des valeurs par defaut");
            EcrireMessageDebug("initialisation", resultat);
        }
    }
#if REMOTE
    InitWiringPiGPIOEvent();
#endif
    return MSG_OK;
}

int initMinuterie()
{
    int *numeroMinuterie = malloc(sizeof(int));
    if (config.minuterie ==0)
    {   
        EcrireMessageErreur("initialisation", "Pas de minuterie configurée");
        return MSG_NoContent;
    }
    int delai = DelaiPourLeProchain(numeroMinuterie);
    AjouterTimer(delai, numeroMinuterie[0]);
    return MSG_OK;
}
