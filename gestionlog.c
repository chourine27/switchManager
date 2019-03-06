/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "configuration.h"
#ifdef VOCORE
#else
#include "fastlogger/fastlogger.h"
#endif
#include "listecodes.h"
#include "tools.h"
#include "gestionlog.h"
#include "initialisation.h"

#include <stdlib.h>

int ecrireMessageDebug (char* origine, const char* message)
{
    return ecrireMessage(origine, message, "DEBUG", FL_DEBUG);
}

int ecrireMessageInfo (char* origine, const char* message)
{
    return ecrireMessage(origine, message, "INFO", FL_EXTRA_INFO);
}

int ecrireMessageAlerte (char* origine, const char* message)
{
    return ecrireMessage(origine, message, "ALERTE", FL_KEY_INFO);
}

int ecrireMessageErreur (char* origine, const char* message)
{
    return ecrireMessage(origine, message, "ERREUR", FL_ERROR);
}

int terminelog()
{
#ifdef VOCORE
#else
    fastlogger_close_thread_local();
    fastlogger_close();
#endif
    return MSG_OK;
}

int ecrireMessage (const char* origine, const char* message, const char* libellePriorite, fastlogger_level_t priorite)
{
#ifdef VOCORE
    printf("%s : %s \n", origine, message);
#elif DEBUG
    printf("%s : %s \n", origine, message);
#else
    initLog();
    Log(priorite, "%s - %s - %s", libellePriorite, origine, message);
    fflush(stdout);
    terminelog();
#endif
    return MSG_OK;
}