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
#include "fastlogger/fastlogger.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <x86_64-linux-gnu/bits/signum-generic.h>

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
}

// Initialise les ports en sortie avec la valeur par defaut
// Retour : MSG_OK si OK, code d'erreur sinon
int initGPIO()
{
    char resultat[BUFLEN];
    int codeResultat;
    int nbrPort = 0;
    codeResultat = RetournerInformationConfig(PARAMETRE_NOMBREINTERRUPTEUR, INITIAL_NOMBREINTERRUPTEUR, resultat);
    if (codeResultat != MSG_OK)
    {
        return codeResultat;
    }
    nbrPort = atoi(resultat);
    for(int i=0; i<nbrPort; i++)
    {
        sprintf(resultat, "%d", i);
        //Initialise le port en sortie avec la valeur par défaut
        voCore_gpioInit(resultat);
        //Initialise le fichier de configuration avec le nom du bouton
        RetournerInformationConfig(PARAMETRE_NOMBOUTON, INITIAL_NOMBOUTON, resultat);
        //Initialise le fichier de configuration avec l'image du bouton
        RetournerInformationConfig(PARAMETRE_IMAGEBOUTON, INITIAL_IMAGEBOUTON, resultat);
    }
    return MSG_OK;
}

int initMinuterie()
{
    int *numeroMinuterie = malloc(sizeof(int));
    if (config.minuterie ==0)
    {   
        ecrireMessageErreur("initialisation", "Pas de minuterie configurée");
        return MSG_NoContent;
    }
    int delai = DelaiPourLeProchain(numeroMinuterie);
    AjouterTimer(delai, numeroMinuterie[0]);
    return MSG_OK;
}

int initLog()
{
    char* str =  fastlogger_thread_local_file_name(LOG_NOMFICHIER,0);
    //free(str);
    fastlogger_set_log_filename(LOG_NOMFICHIER);
    fastlogger_set_min_default_log_level(FL_DEBUG);
    fastlogger_separate_log_per_thread(1);
    return MSG_OK;
}