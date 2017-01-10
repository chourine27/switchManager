#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include "constantes.h"

struct Configuration
{
    int Charge;
    char nomServeur[MAXBUF];
    char imageServeur[MAXBUF];
    int portServeur;
    char nombreInterrupteur[MAXBUF];
};

struct Configuration config;

#endif // CONFIGURATION_H_INCLUDED
