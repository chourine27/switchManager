/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   minuterie.h
 * Author: matthieu
 *
 * Created on December 11, 2017, 7:43 AM
 */

#ifndef MINUTERIE_H
#define MINUTERIE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "informationsminuteries.h"
    
#include <signal.h>
#include <time.h>
    
    int ChargerMinuterie();
    int LireMinuterie (char *valeurMinuterie, struct InformationsMinuteries *Minuterie);
    int AjouterMinuterie (char *NomMinuterie, char* InfoMinuterie);
    int ActiverMinuterie ();
    int DesactiverMinuterie ();
    int RetournerDetailMinuterie (char *IndexMinuterie, char *Informations);
    int DelaiPourLeProchain(int *IdentifiantMinuterie);
    void sigMinut_handler( int sig, siginfo_t *si, void *uc );
    int ajouterTimer( char *name, timer_t *timerID, int expireMS, int intervalMS );

#ifdef __cplusplus
}
#endif

#endif /* MINUTERIE_H */

