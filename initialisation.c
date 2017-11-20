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
}

// Initialise les ports en sortie avec la valeur par defaut
// Retour : MSG_OK si OK, code d'erreur sinon
int initGPIO()
{
    char resultat[BUFLEN];
    int codeResultat;
    int nbrPort = 0;
    int i = 0;
    codeResultat = RetournerInformationConfig(PARAMETRE_NOMBREINTERRUPTEUR, INITIAL_NOMBREINTERRUPTEUR, resultat);
    if (codeResultat != MSG_OK)
    {
        return codeResultat;
    }
    nbrPort = atoi(resultat);
    while (i < nbrPort)
    {
        sprintf(resultat, "%d", i);
        voCore_gpioInit(resultat);
        i++;
    }
    return MSG_OK;
}

