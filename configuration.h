#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include "constantes.h"
#include "informationsminuteries.h"

struct Configuration
{
    int minuterie;
    struct InformationsMinuteries *infoMinuteries;
};

struct Configuration config;

#endif // CONFIGURATION_H_INCLUDED
