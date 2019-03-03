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
    char resultat[MAXBUF];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
    ecrireMessageDebug("clientudp", "Socket UDP\n");
//    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    
    // zero out the structure
    memset((char *) &si_client, 0, sizeof(si_client));

    si_client.sin_family = AF_INET;
    si_client.sin_port = htons(atoi(CONFIG_LOCALPORTSERVEUR));
    si_client.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    ecrireMessageDebug("clientudp", "Structur init\n");
    if (LireParametre(CONFIG_NOMFICHIER, PARAMETRE_PORTSERVEUR, resultat) != MSG_OK)
    {
        ecrireMessageErreur("clientUDP", "Erreur de recuperation du port de connexion\n");
        return MSG_InternalServerError;
    }
    ecrireMessageDebug("clientudp", "Lecture param OK\n");
    si_serveur.sin_family = AF_INET;
    si_serveur.sin_port = htons(atoi(resultat));
    si_serveur.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    ecrireMessageDebug("clientudp", "Config serveur OK\n");
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_client, sizeof(si_client) ) == -1)
    {
        die("bind");
    }
    ecrireMessageDebug("clientudp", "bind OK\n");
    sprintf(resultat, "Commande client : %s\n", commande);
    ecrireMessageDebug("clientudp", resultat);
    if (sendto(s, commande, strlen(commande), 0, (struct sockaddr*) &si_serveur, slen) == -1)
    {
        die("sendto()");
    }
    ecrireMessageDebug("clientudp", "sendto OK\n");
    memset(commande, 0, sizeof (commande));
    ecrireMessageDebug("clientudp", "memset OK\n");
    bzero(buf, BUFLEN);
    ecrireMessageDebug("clientudp", "bzero OK\n");
    fflush(stdout);
    ecrireMessageDebug("clientudp", "fflush OK\n");
    //try to receive some data, this is a blocking call
    //if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_serveur, &slen)) == -1)
    //{
    //    die("recvfrom()");
    //}
    //sprintf(resultat, "Retour serveur au client : %s\n", commande);
    //ecrireMessageDebug("clientudp", resultat);
    close(s);
    return MSG_OK;
}

