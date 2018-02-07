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
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>


/**
 * ChargerMinuterie
 * 
 * Charge tous les paramètres du fichier de configuration
 * @return 
 */
int ChargerMinuterie()
{
    int codeResultat;
    char param[MAXBUF];
    char ligne[MAXBUF];
    char valeurMinuterie[MAXBUF];
    
    FILE *fichierConfig = OuvrirFichier(CONFIG_NOMFICHIER);
    
    config.minuterie = 0;
    //Init du nom du paramètre minuterire
    sprintf(param, "%s%d", PARAMETRE_MINUTERIE, config.minuterie);
    
    while (fgets(ligne, sizeof(ligne), fichierConfig) != NULL)
    {
        if(strncmp("#", ligne, strlen("#")) == 0 || strncmp("\n", ligne, strlen("\n")) == 0)
        {
            continue;
        }
       
        if(copieTexteDeConfig(param, ligne, valeurMinuterie) == MSG_OK)
        {
            codeResultat = AjouterMinuterie(param, valeurMinuterie); 
            if (codeResultat != MSG_OK)
            {
                // TODO : tracer l'erreur 
                continue;
            }
            //Mise à jour du paramètre minuterie comme le compteur évolue.
            sprintf(param, "%s%d", PARAMETRE_MINUTERIE, config.minuterie);
        }
    }
    FermerFichier(fichierConfig);
    return MSG_OK;    
}

/**
 * LireMinuterie
 * 
 * Charge en cache les valeurs de la minuterie
 * @param valeurMinuterie : ensemble des valeurs de la minuterie
 * @param @out Minuterie : struct Minuterie remplie
 * @return : Code erreur de la méthode
 */
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
        Minuterie->seconde = malloc(sizeof(int));
        Minuterie->nbSeconde = splitInformationInt(donneesMinuterie[0], Minuterie->seconde);
        if (Minuterie->nbSeconde == 0)
        {
            return MSG_MethodFailure;
        }
        Minuterie->minute = malloc(sizeof(int));
        Minuterie->nbMinute = splitInformationInt(donneesMinuterie[1], Minuterie->minute);
        if (Minuterie->nbMinute == 0)
        {
            return MSG_MethodFailure;
        }
        Minuterie->heure = malloc(sizeof(int));
        Minuterie->nbHeure = splitInformationInt(donneesMinuterie[2], Minuterie->heure);
        if (Minuterie->nbHeure == 0)
        {
            return MSG_MethodFailure;
        }
        Minuterie->jour = malloc(sizeof(int));
        Minuterie->nbJour = splitInformationInt(donneesMinuterie[3], Minuterie->jour);
        if (Minuterie->nbJour == 0)
        {
            return MSG_MethodFailure;
        }
        Minuterie->etat = atoi((char*) donneesMinuterie[4]);
        Minuterie->bouton = malloc(sizeof(char *) * MAXARG);
        Minuterie->nbrBouton = splitInformationString(donneesMinuterie[5], Minuterie->bouton);
        if (Minuterie->nbrBouton == 0)
        {
            return MSG_MethodFailure;
        }
    }
    return MSG_OK;
}

/**
 * SupprimerMinuteries
 * 
 * Supprimer du cache les minuteries et recharge les nouvelles
 * @return : Code erreur de la méthode
 */
int SupprimerMinuteries ()
{
    struct InformationsMinuteries *temp;
    int codeResultat = MSG_MethodFailure;
    if (config.minuterie > 0)
    {
        for(int i = 0; i < config.minuterie; i++)
        {
            // Efface du fichier de config et passe à l'index suivant
            codeResultat = EffacerParametre(CONFIG_NOMFICHIER, config.infoMinuteries[i].id);
            if (codeResultat != MSG_OK)
            {
                //TODO Log Erreur
                printf("Impossible de supprimer la minuterie %s. Erreur : %d", config.infoMinuteries[i].id, codeResultat);
            }
        }
        config.infoMinuteries = NULL;
        config.minuterie = 0;
    }
    return MSG_OK;
}

/**
 * AjouterMinuterie
 * 
 * Ajoute une minuterie à la suite dans le cache
 * @param NomMinuterie : Nom de la minuterie à ajouter
 * @param InfoMinuterie : information liés à la minuterie
 * @return : Code erreur de la méthode
 */
int AjouterMinuterie(char* NomMinuterie, char* InfoMinuterie)
{
    int codeResultat = MSG_MethodFailure;
    struct InformationsMinuteries *temp;
    
    //Convertion de la ligne paramètre en structure infoMinuterie
    // L'identifiant de la minuterie
    temp = realloc(config.infoMinuteries, sizeof(struct InformationsMinuteries) * (config.minuterie+1));
    if (temp == NULL)
    {
        return MSG_InsufficientStorage;
    }
    config.infoMinuteries = temp;
    config.infoMinuteries[config.minuterie].id = malloc(sizeof(char) * strlen(NomMinuterie));
    strcpy(config.infoMinuteries[config.minuterie].id, NomMinuterie);
    // Tous les autres paramètres
    codeResultat = LireMinuterie(InfoMinuterie, config.infoMinuteries +(config.minuterie));
    if (codeResultat == MSG_OK)
    {
        config.minuterie++;
    }
    return codeResultat;
}

/**
 * RetournerDetailMinuterie
 * 
 * Retourne les informations d'une minuterie
 * @param IndexMinuterie : Numéro de la minuterie à retourner
 * @param @out Informations : Informations en ligne d'une minuterie
 * @return : Code erreur de la méthode
 */
int RetournerDetailMinuterie (char *IndexMinuterie, char *Informations)
{
    char *parametre = malloc(sizeof(char) * (strlen(PARAMETRE_MINUTERIE) + strlen(IndexMinuterie)));
    sprintf(parametre, "%s%s", PARAMETRE_MINUTERIE, IndexMinuterie);
    return LireParametre(CONFIG_NOMFICHIER, parametre, Informations);
}

int DelaiPourLeProchain(int *IdentifiantMinuterie)
{
    int delai = 1000000;
    int current_delai;
    time_t now;
    struct tm *current_time;
    now = time(NULL);
    current_time = localtime(&now);    

    for(int i=0; i < config.minuterie; i++)
    {
        for(int j=0; j < config.infoMinuteries[i].nbSeconde; j++)
        {
            if (config.infoMinuteries[i].seconde[j] == 0)
            {
                current_delai = 1;
            }
            else
            {
                current_delai = config.infoMinuteries[i].seconde[j] - current_time->tm_sec;
                if (current_delai < 0)
                {
                    current_delai += 60;
                }
            }
            if (delai > current_delai)
            {
                delai = current_delai;
                IdentifiantMinuterie[0] = i;
            }
        } 
    }
    printf("Prochain délai : %d\n", delai);
    return delai;
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