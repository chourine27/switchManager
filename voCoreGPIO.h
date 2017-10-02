/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   voCoreGPIO.h
 * Author: matthieu
 *
 * Created on October 2, 2017, 7:18 AM
 */

#ifndef VOCOREGPIO_H
#define VOCOREGPIO_H

#ifdef VOCORE
#define RACINECHEMIN "/sys/class/gpio/gpio" // Chemin d'accès au GPIO
#else
#define RACINECHEMIN "/NetBeansProjects/switchManager/gpio/gpio" // Chemin d'accès au GPIO
#endif

#define DIRECTIONCHEMIN "/direction" // Chemin pour accèder a l'information de direction du port
#define VALEURCHEMIN "/value" // Chemin pour accéder à la valeur du port
#define DIRECTIONSORTIE "out" // Valeur à définir pour mettre le port en sortie


int voCore_gpioDirectionOut(char* index);
int voCore_gpioSetValue(char* index, char* value);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* VOCOREGPIO_H */

