/* ========================================================================== */
/*                                                                            */
/*   clientudp.c                                                               */
/*   Matthieu CHARQUET                                                        */
/*                                                                            */
/*   Description                                                              */
/*   Client UDP                                                              */
/* ========================================================================== */

#include "clientudp.h"
#include "serveurudp.h"
#include "gestioncommandes.h"
#include "gestionfichier.h"
#include "constantes.h"
#include "configuration.h"
#include "listecodes.h"
#include "gestionlog.h"

#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>

int sendData(char* commande)
{
    struct sockaddr_in si_client, si_serveur;

    int s, retourCode, slen = sizeof(si_serveur) , recv_len;
    int broadcast=1;
    char buf[BUFLEN];
    char resultat[BUFLEN];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

//    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    
    // zero out the structure
    memset((char *) &si_client, 0, sizeof(si_client));

    si_client.sin_family = AF_INET;
    si_client.sin_port = htons(atoi(CONFIG_LOCALPORTSERVEUR));
    si_client.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            
    if (LireParametre(CONFIG_NOMFICHIER, PARAMETRE_PORTSERVEUR, resultat) != MSG_OK)
    {
        printf("clientUDP - Erreur de recuperation du port de connexion\n");
        return MSG_InternalServerError;
    }

    si_serveur.sin_family = AF_INET;
    si_serveur.sin_port = htons(atoi(resultat));
    si_serveur.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_client, sizeof(si_client) ) == -1)
    {
        die("bind");
    }
    
    if (sendto(s, commande, strlen(commande), 0, (struct sockaddr*) &si_serveur, slen) == -1)
    {
        die("sendto()");
    }
    memset(commande, 0, sizeof (commande));

    bzero(buf, BUFLEN);
    fflush(stdout);

    //try to receive some data, this is a blocking call
    if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_serveur, &slen)) == -1)
    {
        die("recvfrom()");
    }
    ecrireMessageDebug("clientudp", commande);
    close(s);
    return MSG_OK;
}

