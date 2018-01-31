/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "gestionfichier.h"
#include "minuterie.h"
#include "constantes.h"
#include "listecodes.h"
#include "configuration.h"
#include "informationsminuteries.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>


int ChargerMinuterie()
{
    int i=0;
    int result;
    char param[MAXBUF];
    char ligne[MAXBUF];
    char valeurMinuterie[MAXBUF];
    struct InformationsMinuteries infoMinuterie, *temp;
    
    FILE *fichierConfig = OuvrirFichier(CONFIG_NOMFICHIER);
    
    //Init du nom du paramètre minuterire
    sprintf(param, "%s%d", PARAMETRE_MINUTERIE, i);
    
    while (fgets(ligne, sizeof(ligne), fichierConfig) != NULL)
    {
        if(strncmp("#", ligne, strlen("#")) == 0 || strncmp("\n", ligne, strlen("\n")) == 0)
        {
            continue;
        }
       
        if(copieTexteDeConfig(param, ligne, valeurMinuterie) == MSG_OK)
        {
            //Convertion de la ligne paramètre en structure infoMinuterie
            // L'identifiant de la minuterie
            temp = realloc(config.infoMinuteries, sizeof(struct InformationsMinuteries) * ++i);
            if (temp == NULL)
            {
                return MSG_InsufficientStorage;
            }
            config.infoMinuteries = temp;
            config.infoMinuteries[i-1].id = malloc(sizeof(char *) * strlen(param));
            strcpy(config.infoMinuteries[i-1].id, param);
            // Tous les autres paramètres
            result = LireMinuterie(valeurMinuterie, config.infoMinuteries +(i-1));
            if (result != MSG_OK)
            {
                // TODO : tracer l'erreur 
                continue;
            }
            //Mise à jour du paramètre minuterie comme le compteur évolue.
            sprintf(param, "%s%d", PARAMETRE_MINUTERIE, i);
        }
    }
    config.minuterie = i;
    FermerFichier(fichierConfig);
    return MSG_OK;    
}

int LireMinuterie(char* valeurMinuterie, struct InformationsMinuteries* Minuterie)
{
    char **donneesMinuterie= malloc(sizeof(char *) * MAXARG);
    int codeRestult = MSG_NotImplemented;
    // Verification si la minuterie contient des espaces
    if (strpbrk(valeurMinuterie, SEPARINFO) != 0)
    {
        codeRestult = splitLine(valeurMinuterie, donneesMinuterie);
        if (codeRestult != 6)
        {
            return MSG_BadMapping;
        }
        Minuterie->seconde = atoi((char*) donneesMinuterie[0]);
        Minuterie->minute = atoi((char*) donneesMinuterie[1]);
        Minuterie->heure = atoi((char*) donneesMinuterie[2]);
        Minuterie->jour = atoi((char*) donneesMinuterie[3]);
        Minuterie->etat = atoi((char*) donneesMinuterie[4]);
        Minuterie->bouton = malloc(sizeof(char) * (strlen(donneesMinuterie[5])));
        strcpy(Minuterie->bouton, donneesMinuterie[5]);
    }
    return MSG_OK;
}

int EcrireMinuterie(char *NomFichier, struct InformationsMinuteries Minuterie)
{
    return MSG_NotImplemented;
}

int ajouterTimer( char *name, timer_t *timerID, int expireMS, int intervalMS )
{
    struct sigevent         te;
    struct itimerspec       its;
    struct sigaction        sa;
    int                     sigNo = SIGRTMIN;

    /* Set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigMinut_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(sigNo, &sa, NULL) == -1)
    {
        //fprintf(stderr, "%s: Failed to setup signal handling for %s.\n", PROG, name);
        return(-1);
    }

    /* Set and enable alarm */
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = sigNo;
    te.sigev_value.sival_ptr = timerID;
//    timer_create(CLOCK_REALTIME, &te, timerID);

    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = intervalMS * 1000000;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = expireMS * 1000000;
//    timer_settime(*timerID, 0, &its, NULL);

    return(0);
}

void sigMinut_handler( int sig, siginfo_t *si, void *uc )
{
    timer_t *tidp;
    tidp = si->si_value.sival_ptr;

    /* if ( *tidp == firstTimerID )
        firstCB(sig, si, uc);
    else if ( *tidp == secondTimerID )
        secondCB(sig, si, uc);
    else if ( *tidp == thirdTimerID )
        thirdCB(sig, si, uc); */
}