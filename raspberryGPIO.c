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
#define GPIO1 6  
#define GPIO2 13
#define GPIO3 12
#define GPIO4 5
#define GPIO5 4
#define GPIO6 3
#define GPIO7 2
#define GPIO8 1

static int SuiviGPIO = 0;
int correspondanceIndexWiringPiGPIO[MAXBOUTON];

void InitWiringPiGPIO()
{
    correspondanceIndexWiringPiGPIO[0] = GPIO1;
    correspondanceIndexWiringPiGPIO[1] = GPIO2;
    correspondanceIndexWiringPiGPIO[2] = GPIO3;
    correspondanceIndexWiringPiGPIO[3] = GPIO4;
    correspondanceIndexWiringPiGPIO[4] = GPIO5;
    correspondanceIndexWiringPiGPIO[5] = GPIO6;
    correspondanceIndexWiringPiGPIO[6] = GPIO7;
    correspondanceIndexWiringPiGPIO[7] = GPIO8;
    correspondanceIndexWiringPiGPIO[8] = GPIO8;
    correspondanceIndexWiringPiGPIO[9] = GPIO8;
    wiringPiSetup();
    EcrireMessageDebug("raspberryGPIO", "Chargement wiringPiSetup OK");
    for (int i=0; i < 8; i++)
    {
        pinMode(correspondanceIndexWiringPiGPIO[i], OUTPUT);
        //digitalWrite(correspondanceIndexWiringPiGPIO[i], LOW);
        EcrireMessageDebug("raspberryGPIO", "La GPIO est configurée en OUT et Allumé");
    }
}

void InitWiringPiGPIOEvent()
{
    wiringPiISR(GPIONiveauBas, INT_EDGE_FALLING, EvenementCouperInterrupteur);
    wiringPiISR(GPIONiveauHaut, INT_EDGE_RISING, EvenementAllumerInterrupteur);
    EcrireMessageDebug("raspberryGPIO", "Configuration des evènements OK");

}

void EvenementCouperInterrupteur()
{
    // Coupure uniquement si le niveau haut est aussi trop bas... Eviter les coupures inutiles
    if (digitalRead(GPIONiveauHaut) == LOW)
    {
        EcrireMessageDebug("raspberryGPIO", "EvenementCouperInterrupteur");
        EnvoyerCommande(BoutonAGerer, CONFIG_ETEINT);
    }
}

void EvenementAllumerInterrupteur()
{
    EcrireMessageDebug("raspberryGPIO", "EvenementAllumerInterrupteur");
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
    sprintf(commande, "%s %d %d", COMMANDE_CHANGESTATUTBOUTON, index, etat);
    EcrireMessageDebug("raspberryGPIO", commande);
    sendData(commande);
    EcrireMessageInfo("raspberryGPIO", "Traitement evènement transmis");
    piUnlock(0);
    
    SuiviGPIO = 0;
}

/**
 * Définie la valeur d'une GPIO
 * @param index Index (commence à 1)
 * @param value Valeur de sortie : CONFIG_ALLUME / CONFIG_ETEINT
 * @return      Code erreur de retour
 */
int WiringPiSetValue(int index, int value)
{
    index--;
    
    if (index > 7)
    {
        return MSG_RangeUnsatisfiable;
    }
    if (value < 0 || value > 1)
    {
        return MSG_Unauthorized;
    }
    if (value == 1)
    {
        value = LOW;
    }
    else
    {
        value = HIGH;
    }
    digitalWrite (correspondanceIndexWiringPiGPIO[index], value);
    return MSG_OK;
}

/**
 * Retourne la valeur d'un index
 * @param index Identifiant du bouton à vérifier
 * @return      Retourne la valeur CONFIG_ALLUME / CONFIG_ETEINT
 */
int WiringPiGetValue(int index)
{
    index--;
    if (digitalRead(correspondanceIndexWiringPiGPIO[index]) == 1)
    {
        return CONFIG_ETEINT;
    }
    else
    {
        return CONFIG_ALLUME;
    }
}

#endif
