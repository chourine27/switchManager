/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifdef REMOTE

#include "clientudp.h"
#include "constantes.h"
#include "gestionlog.h"
#include "listecodes.h"
#include "raspberryGPIO.h"
#include "tools.h"

#include <wiringPi.h>

#define BoutonAGerer 1
#define GPIONiveauBas 0
#define GPIONiveauHaut 7

static int SuiviGPIO = 0;

void InitRaspberryGPIO()
{
    wiringPiSetup();
    wiringPiISR(GPIONiveauBas, INT_EDGE_FALLING, EvenementCouperInterrupteur);
    wiringPiISR(GPIONiveauHaut, INT_EDGE_RISING, EvenementAllumerInterrupteur);
}

void EvenementCouperInterrupteur()
{
    // Coupure uniquement si le niveau haut est aussi trop bas... Eviter les coupures inutiles
    if (digitalRead(GPIONiveauHaut) == LOW)
    {
        ecrireMessageDebug("raspberryGPIO", "EvenementCouperInterrupteur");
        EnvoyerCommande(BoutonAGerer, CONFIG_ETEINT);
    }
}

void EvenementAllumerInterrupteur()
{
    ecrireMessageDebug("raspberryGPIO", "EvenementAllumerInterrupteur");
    EnvoyerCommande(BoutonAGerer, CONFIG_ALLUME);
}

int EnvoyerCommande(int index, int etat)
{
    char commande[MAXBUF];
    
    if (SuiviGPIO > 0)
        return MSG_OK;
    else
        SuiviGPIO++;
    
    
    piLock(0);
    sprintf(commande, "%s %d %d\n", COMMANDE_CHANGESTATUTBOUTON, index, etat);
    ecrireMessageDebug("raspberryGPIO", commande);
    sendData(commande);
    ecrireMessageInfo("raspberryGPIO", "Traitement evènement transmis\n");
    piUnlock(0);
    
    SuiviGPIO = 0;
}

#endif