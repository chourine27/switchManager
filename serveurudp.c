/* ========================================================================== */
/*                                                                            */
/*   serveurudp.c                                                               */
/*   Matthieu CHARQUET                                                        */
/*                                                                            */
/*   Description                                                              */
/*   Serveur UDP                                                              */
/* ========================================================================== */

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

void die(char *s)
{
    perror(s);
    exit(1);
}

// Execute le serveur en mode thread
// threadData : Données
void * fn_StartServerUDP (void * threadData)
{
    int error = StartServerUDP();
}

int StartServerUDP(void)
{
    struct sockaddr_in si_me, si_other;

    int s, retourCode, slen = sizeof(si_other) , recv_len;
    int broadcast=1;
    char buf[BUFLEN];
    char resultat[BUFLEN];
    char messageLog[MAXBUF];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

//    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
    
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    if (LireParametre(CONFIG_NOMFICHIER, PARAMETRE_PORTSERVEUR, resultat) != MSG_OK)
    {
        printf("StartServerUDP - Erreur de recuperation du port de connexion\n");
        return MSG_InternalServerError;
    }

    si_me.sin_port = htons(atoi(resultat));
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

    ecrireMessageInfo("serveurudp", "Server démarré, prêt à recevoir des données\n");
    //keep listening for data
    
    while(1)
    {
        bzero(buf, BUFLEN);
        fflush(stdout);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }

        //print details of the client/peer and the data received
        sprintf(messageLog, "Received packet from %s:%d - Commande : %s", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
        ecrireMessageInfo("serveurudp", messageLog);
        retourCode = ExecuterCommande(buf, resultat);
        if (retourCode != MSG_OK)
        {
            sprintf(messageLog, "StartServerUDP - Commande retourne une erreur : %d\n ", retourCode);
            ecrireMessageInfo("serveurudp", messageLog);
            //now reply this error to client
        }
        if (sendto(s, resultat, strlen(resultat), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        memset(resultat, 0, sizeof (resultat));
    }

    return MSG_OK;
}

/*
** listener.c -- a datagram sockets "server" demo
*/

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
