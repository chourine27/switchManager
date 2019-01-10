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
#ifdef RASPBERRY
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
#define PREFIXRELAI "RLY"
#define INFORELAIS "?RLY"

#ifndef USBRELAIS_H
#define USBRELAIS_H

#ifdef __cplusplus
extern "C" {
#endif

int USBRelais_gpioSetValue(int index, int valeur);
int USBRelais_gpioGetValue(int index);
int USBRelais_gpioInit(char* index);
int USBRelais_sendData(char* prefix, int index, int valeur, char* resultat);
int USBRelais_sendDataByCommande(char* commande, char* resultat);

int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);

#ifdef __cplusplus
}
#endif

#endif /* USBRELAIS_H */

