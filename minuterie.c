/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "gestionfichier.h"
#include "gestiongpio.h"
#include "minuterie.h"
#include "constantes.h"
#include "listecodes.h"
#include "configuration.h"
#include "informationsminuteries.h"
#include "tools.h"
#include "clientudp.h"
#include "gestionlog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>


static int indexMinuterie;

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
    char contenuString[MAXBUF];
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
                sprintf(contenuString, "Erreur dans copieTextDeConfig : %d\n", codeResultat);
                ecrireMessageErreur("minuterie", contenuString);
                continue;
            }
            //Mise à jour du paramètre minuterie comme le compteur évolue.
            sprintf(param, "%s%d", PARAMETRE_MINUTERIE, config.minuterie);
            sprintf(contenuString, "Minuterie chargée : %d\n", config.minuterie);
            ecrireMessageErreur("minuterie", contenuString);
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
                char contenuString[MAXBUF];
                sprintf(contenuString, "Impossible de supprimer la minuterie %s : Erreur %d\n", config.infoMinuteries[i].id, codeResultat);
                ecrireMessageErreur("minuterie", contenuString);
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
    int delai, less_delai = 1000000;
    int current_delai, temp_delai, secondePlus, minutePlus, heurePlus, delaiSecondePlus, delaiMinutePlus, delaiHeurePlus;
    char contenuString[MAXBUF];
    time_t now;
    struct tm *current_time;
    now = time(NULL);
    current_time = localtime(&now);    

    for(int i=0; i < config.minuterie; i++)
    {
        sprintf(contenuString, "Analyse de la minuterie : %d\n", i);
        ecrireMessageDebug("minuterie", contenuString);

        delai = 1000000;
        for(int s=0; s < config.infoMinuteries[i].nbSeconde; s++)
        {
            secondePlus = 0;
            if (config.infoMinuteries[i].seconde[s] == -1)
            {
                current_delai = 1;
                ecrireMessageDebug("minuterie", "-1 -> chaque seconde\n");
            }
            else
            {
                current_delai = config.infoMinuteries[i].seconde[s] - current_time->tm_sec;
                if (current_delai < 0)
                {
                    current_delai += 60;
                    secondePlus = 1;
                    ecrireMessageDebug("minuterie", "Ajout 60 secondes\n");
                }
            }
            if (delai > current_delai)
            {
                delai = current_delai;
                delaiSecondePlus = secondePlus;
            }
        } 
        temp_delai = delai;
        sprintf(contenuString, "Delai après les secondes : %d\n", temp_delai);
        ecrireMessageDebug("minuterie", contenuString);
        delai = 1000000;
        for(int m=0; m < config.infoMinuteries[i].nbMinute; m++)
        {
            minutePlus = 0;
            if (config.infoMinuteries[i].minute[m] == -1)
            {
                current_delai = 0;
                ecrireMessageDebug("minuterie", "-1 -> chaque minutes\n");
            }
            else
            {
                current_delai = (config.infoMinuteries[i].minute[m] - current_time->tm_min - delaiSecondePlus) * 60;
                if (current_delai < 0)
                {
                    minutePlus = 1;
                    current_delai += 3600;
                    ecrireMessageDebug("minuterie", "Ajout 60 minutes\n");
                }
            }
            if (delai > current_delai)
            {
                delai = current_delai;
                delaiMinutePlus = minutePlus;
            }
        }
        temp_delai += delai;
        sprintf(contenuString, "Delai après les minutes : %d\n", temp_delai);
        ecrireMessageDebug("minuterie", contenuString);        
        delai = 1000000;
        for(int h=0; h < config.infoMinuteries[i].nbHeure; h++)
        {
            heurePlus = 0;
            if (config.infoMinuteries[i].heure[h] == -1)
            {
                current_delai = 0;
            }
            else
            {
                current_delai = (config.infoMinuteries[i].heure[h] - current_time->tm_hour - delaiMinutePlus) * 3600;
                if (current_delai < 0)
                {
                    heurePlus = 1;
                    current_delai += 86400;
                    ecrireMessageDebug("minuterie", "Ajout 24 heures\n");
                }
            }
            if (delai > current_delai)
            {
                delai = current_delai;
                delaiHeurePlus = heurePlus;
            }
        }
        temp_delai += delai;
        sprintf(contenuString, "Delai après les heures : %d\n", temp_delai);
        ecrireMessageDebug("minuterie", contenuString);        
        delai = 1000000;
        for(int j=0; j < config.infoMinuteries[i].nbJour; j++)
        {
            if (config.infoMinuteries[i].jour[j] == -1)
            {
                current_delai = 0;
                ecrireMessageDebug("minuterie", "-1 -> chaque jour\n");
            }
            else
            {
                //jour dans minuterie est de 1 à 7 pour dimanche à samedi. coté time c'est de 0 à 6
                current_delai = (config.infoMinuteries[i].jour[j] -1 - current_time->tm_wday - delaiHeurePlus) * 86400;
                if (current_delai < 0)
                {
                    current_delai += 604800;
                    ecrireMessageDebug("minuterie", "Ajout 7 jours\n");
                }
            }
            if (delai > current_delai)
            {
                delai = current_delai;
            }
        }
        temp_delai += delai;
        sprintf(contenuString, "Delai après les jours : %d\n", temp_delai);
        ecrireMessageDebug("minuterie", contenuString);
        if (less_delai > temp_delai)
        {
            less_delai = temp_delai;
            IdentifiantMinuterie[0] = i;
        }
    }
    if (less_delai == 0)
        less_delai++;
    sprintf(contenuString, "Delai avant la prochaine alarme : %d\n", less_delai);
    ecrireMessageDebug("minuterie", contenuString);
    sprintf(contenuString, "Numéro minuterie %d\n", IdentifiantMinuterie[0]);
    ecrireMessageDebug("minuterie", contenuString);    
    return less_delai;
}
 
int AjouterTimer(int delai, int numMinuterie)
{
    signal(SIGALRM, ALARMhandler);
    alarm(delai);
    indexMinuterie = numMinuterie;
    return MSG_OK;
}

int TraiterMinuterie (int index)
{
    char commande[MAXBUF];
    sprintf(commande, "%s %s %d\n", COMMANDE_CHANGESTATUTBOUTON, config.infoMinuteries[index].bouton[0], config.infoMinuteries[index].etat);
    sendData(commande);
    ecrireMessageInfo("minuterie", "TraitementMinuterie commande transmise\n");
}

void  ALARMhandler(int sig)
{
    signal(SIGALRM, SIG_IGN);          /* ignore this signal       */

    int *numeroMinuterie = malloc(sizeof(int));
    if (config.minuterie ==0)
        return MSG_NoContent;
    TraiterMinuterie(indexMinuterie);
    int delai = DelaiPourLeProchain(numeroMinuterie);
    AjouterTimer(delai, numeroMinuterie[0]);
}