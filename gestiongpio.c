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
    return MSG_NotImplemented;
}

// Désactive un relai
// index : Index du relai à désactiver
// Retour : MSG_OK si OK, code d'erreur sinon
int DesactiverRelai (int index)
{
    return MSG_NotImplemented;
}
