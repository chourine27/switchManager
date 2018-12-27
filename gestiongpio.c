/* ========================================================================== */
/*                                                                            */
/*   gestiongpio.c                                                            */
/*   Matthieu CHARQUET                                                        */
/*                                                                            */
/*   Description                                                              */
/*   Gestion des communications avec le GPIO                                  */
/* ========================================================================== */

#include "gestiongpio.h"
#include "listecodes.h"
#include "constantes.h"
#include "voCoreGPIO.h"
#include "USBRelais.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Retourne l'etat d'un relai
// index : index du relai à vérifier
// Retour : 1 si actif, 0 sinon
int EtatRelai(int index)
{
    return CONFIG_ALLUME;
}

// Active un relai
// index : Index du relai à activer
// Retour : MSG_OK si OK, code d'erreur sinon
int ActiverRelai(int index)
{
#ifdef VOCORE
    return voCore_gpioSetValueByIndex(index, CONFIG_ALLUME);
#endif
#ifdef RASPBERRY
    return USBRelais_gpioSetValue(index, CONFIG_ALLUME);
#endif
}

// Désactive un relai
// index : Index du relai à désactiver
// Retour : MSG_OK si OK, code d'erreur sinon
int DesactiverRelai (int index)
{
#ifdef VOCORE
    return voCore_gpioSetValueByIndex(index, CONFIG_ETEINT);
#endif
#ifdef RASPBERRY
    return USBRelais_gpioSetValue(index, CONFIG_ETEINT);
#endif
}
