/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "constantes.h"
#include "USBRelais.h"
#include "listecodes.h"
#include "gestionlog.h"
#include "tools.h"

#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

// Définie la valeur de sortie du port
// index : Index du port à traiter en char
// valeur : Valeur de sortie à définir
// retour : Valeur de retour de la commande
// Retour : MSG_OK si OK, code d'erreur sinon
int USBRelais_gpioSetValue(int index, int valeur)
{
    char retour[MAXBUF];
    return USBRelais_sendData(PREFIXRELAI, index, valeur, retour);
}

// Récupère la valeur de sortie d'un GPIO
// index : Index du port à traiter en char
// retour : Valeur de retour de la commande
// Retour : Etat du relai. 1 pour allumé, 0 pour éteint
int USBRelais_gpioGetValue(int index)
{
    char commande[MAXBUF];
    char resultat[20];
    char **argv = NULL;
    argv = malloc(sizeof(char *) * MAXARG);
    
    sprintf(commande, "%s?", PREFIXRELAI);
    USBRelais_sendDataByCommande(commande, resultat);
    ecrireMessageDebug("USBRelai", resultat);
    splitString(resultat, argv, SEPARINFO);
    ecrireMessageDebug("USBRelai", argv[0]);
    ecrireMessageDebug("USBRelai", argv[1]);
    ecrireMessageDebug("USBRelai", argv[2]);
    ecrireMessageDebug("USBRelai", argv[3]);
    ecrireMessageDebug("USBRelai", argv[4]);
    ecrireMessageDebug("USBRelai", argv[5]);
    ecrireMessageDebug("USBRelai", argv[6]);
    ecrireMessageDebug("USBRelai", argv[7]);
    return atoi(argv[index-1]);
}

// Ecrit dans un fichier specifique au GPIO
// index : Index de la GPIO
// valeur : valeur à écrire dans le fichier
// Retour : MSG_OK si OK, code d'erreur sinon
int USBRelais_sendData(char* prefix, int index, int valeur, char* resultat)
{
    char commande[MAXBUF]; // = PREFIXRELAI;
    sprintf(commande, "%s%d%d\n", PREFIXRELAI, index, valeur);
    return USBRelais_sendDataByCommande(commande, resultat);
}

int USBRelais_sendDataByCommande(char* commande, char* resultat)
{
    char *portname = SERIALPORT;
    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
#ifdef DEBUG
    ecrireMessageInfo("USBRelais", commande);
#else
    ecrireMessageDebug("USBRelais", commande);
    if (fd < 0)
    {
        char contenuString[MAXBUF];
        sprintf(contenuString, "error %d opening %s: %s", errno, portname, strerror (errno));
        ecrireMessageErreur("USBRelais", contenuString);
        return MSG_MethodFailure;
    }
    set_interface_attribs (fd, B9600, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blocking

    write (fd, commande, 7);           // send 7 character greeting
    usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
                                     // receive 25:  approx 100 uS per char transmit
    int n = read (fd, resultat, sizeof resultat);  // read up to 100 characters if ready to read
#endif
    return MSG_OK;
}

int set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
            char contenuString[MAXBUF];
            sprintf(contenuString, "error %d from tcgetattr. %s", errno, strerror (errno));
            ecrireMessageErreur("USBRelais", contenuString);

            return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
//                error_message ("error %d from tcsetattr", errno);
                return MSG_MethodFailure;
        }
        return MSG_OK;
}

void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
//                error_message ("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
            char contenuString[MAXBUF];
            sprintf(contenuString, "error %d fsetting term attributes. %s", errno, strerror (errno));
            ecrireMessageErreur("USBRelais", contenuString);            
        }
}