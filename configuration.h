#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include "constantes.h"
#include "informationsminuteries.h"
//#include log4c.h

struct Configuration
{
    int minuterie;
    struct InformationsMinuteries *infoMinuteries;
//    log4c_category_t* logger;
};

struct Configuration config;

#endif // CONFIGURATION_H_INCLUDED
