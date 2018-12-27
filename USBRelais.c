/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "constantes.h"
#include "USBRelais.h"
#include "listecodes.h"

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
// Retour : MSG_OK si OK, code d'erreur sinon
int USBRelais_gpioSetValue(int index, int valeur)
{
    return USBRelais_sendData(PREFIXRELAI, index, valeur);
}

// Ecrit dans un fichier specifique au GPIO
// index : Index de la GPIO
// valeur : valeur à écrire dans le fichier
// Retour : MSG_OK si OK, code d'erreur sinon
int USBRelais_sendData(char* prefix, int index, int valeur)
{
    char commande[MAXBUF]; // = PREFIXRELAI;
    char *portname = SERIALPORT;
    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

    sprintf(commande, "%s%d%d\n", PREFIXRELAI, index, valeur);
#ifdef DEBUG
    printf("USBRelais : %s", commande);
#else
    if (fd < 0)
    {
        printf("error %d opening %s: %s", errno, portname, strerror (errno));
//        error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
        return;
    }
    set_interface_attribs (fd, B9600, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blocking

    write (fd, commande, 7);           // send 7 character greeting
    usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
                                     // receive 25:  approx 100 uS per char transmit
    char buf [100];
    int n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read
#endif
    return MSG_OK;
}

int set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
            printf("error %d from tcgetattr", errno);
//                error_message ("error %d from tcgetattr", errno);
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
            printf("error %d setting term attributes", errno);
//                error_message ("error %d setting term attributes", errno);
}