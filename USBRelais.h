/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   USBRelais.h
 * Author: matthieu
 *
 * Created on December 18, 2018, 10:43 AM
 */
#ifdef Raspberry
#define SERIALPORT "/dev/ttyUSB0" // Chemin d'accès au GPIO
#else
#define SERIALPORT "/NetBeansProjects/switchManager/gpio/gpio" // Chemin d'accès au GPIO
#endif
#define BAUDRATE 9600
#define BYTESIZE 8
#define PARITY 'N'
#define TIMEOUT "None"
#define XONXOFF false
#define RTSCTS false
#define DSRDTR false

#ifndef USBRELAIS_H
#define USBRELAIS_H

#ifdef __cplusplus
extern "C" {
#endif

int USBRelais_gpioSetValueByIndex(int index, int valeur);
int USBRelais_gpioSetValue(char* index, char* valeur);
int USBRelais_gpioInit(char* index);


#ifdef __cplusplus
}
#endif

#endif /* USBRELAIS_H */

