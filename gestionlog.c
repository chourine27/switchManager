/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "configuration.h"
#include "fastlogger/fastlogger.h"
#include "listecodes.h"

#include <stdlib.h>

int ecrireMessageDebug (char* origine, const char* message)
{
    return ecrireMessage(origine, message, FL_DEBUG);
}

int ecrireMessageInfo (char* origine, const char* message)
{
    return ecrireMessage(origine, message, FL_EXTRA_INFO);
}

int ecrireMessageAlerte (char* origine, const char* message)
{
    return ecrireMessage(origine, message, FL_KEY_INFO);
}

int ecrireMessageErreur (char* origine, const char* message)
{
    return ecrireMessage(origine, message, FL_ERROR);
}

int terminelog()
{
    fastlogger_close_thread_local();
    fastlogger_close();
}

int ecrireMessage (const char* origine, const char* message, fastlogger_level_t priorite)
{
    fastlogger_set_min_log_level(origine, FL_DEBUG);
    FastLoggerNS_t nom = FASTLOGGERNS_INIT(origine);
    LogNS(nom, priorite, "%s", message);
    //Log(FL_KEY_INFO, "%s", message);
    return MSG_OK;
}