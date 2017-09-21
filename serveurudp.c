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

#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>

//extern struct Configuration config;

void die(char *s)
{
    perror(s);
    exit(1);
}

int StartServerUDP(void)
{
    struct sockaddr_in si_me, si_other;

    int s, retourCode, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
    char resultat[BUFLEN];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

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

    printf("Server started. Ready to receive data\n");
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
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        retourCode = ExecuterCommande(buf, resultat);
        if (retourCode != MSG_OK)
        {
            printf("StartServerUDP - Commande retourne une erreur : %c\n ", retourCode);
            //now reply this error to client
        }
        if (sendto(s, resultat, strlen(resultat), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        memset(resultat, 0, sizeof (resultat));
    }
    close(s);
    return MSG_OK;
}
