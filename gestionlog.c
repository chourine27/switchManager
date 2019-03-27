/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "configuration.h"
#ifdef VOCORE
#else
#include <zlog.h>
#endif
#include "listecodes.h"
#include "tools.h"
#include "gestionlog.h"
#include "initialisation.h"

#include <stdlib.h>

zlog_category_t *c;

int InitLog()
{
    	int rc;
	
	rc = zlog_init("/etc/zlog.conf");
	if (rc) {
		printf("init failed : %d\n", rc);
		return -1;
	}

	c = zlog_get_category("switchmanager");
	if (!c) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

	return MSG_OK;
}

int EcrireMessageDebug (char* origine, const char* message)
{
    zlog_category_t *category = zlog_get_category(origine);
    zlog_debug(category, message);
    return MSG_OK;
    //return ecrireMessage(origine, message, "DEBUG", FL_DEBUG);
}

int EcrireMessageInfo (char* origine, const char* message)
{
    zlog_category_t *category = zlog_get_category(origine);
    zlog_info(category, message);
    return MSG_OK;
    //return ecrireMessage(origine, message, "INFO", FL_EXTRA_INFO);
}

int EcrireMessageAlerte (char* origine, const char* message)
{
    zlog_category_t *category = zlog_get_category(origine);
    zlog_warn(category, message);
    return 0; //return ecrireMessage(origine, message, "ALERTE", FL_KEY_INFO);
}

int EcrireMessageErreur (char* origine, const char* message)
{
    zlog_category_t *category = zlog_get_category(origine);
    zlog_error(category, message);
    return 0; //return ecrireMessage(origine, message, "ERREUR", FL_ERROR);
}

int terminelog()
{
#ifdef VOCORE
#else
    zlog_fini();
#endif
    return MSG_OK;
}
