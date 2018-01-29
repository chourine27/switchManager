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

#include <stdio.h>
#include <stdlib.h>

// Initilise le fichier de config si il n'existe pas
// Retour : MSG_OK si OK, code d'erreur sinon
int initConfig()
{
    char resultat[BUFLEN];
    int codeResultat;
    
    codeResultat = RetournerInformationConfig(PARAMETRE_NOMSERVEUR, INITIAL_NOMSERVEUR, resultat);
    codeResultat = RetournerInformationConfig(PARAMETRE_NOMBREINTERRUPTEUR, INITIAL_NOMBREINTERRUPTEUR, resultat);
    
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
    return MSG_NotImplemented;
}