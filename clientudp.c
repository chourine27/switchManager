/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "clientudp.h"

int sendData(char* commande)
{
    int sockfd; 
    char buffer[MAXBUF]; 
    struct sockaddr_in servaddr; 
    int n, len; 
    
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(INITIAL_PORTSERVEUR); 
    servaddr.sin_addr.s_addr = INADDR_LOOPBACK; 
     
    printf("Client UDP : %s\n", commande); 
    sendto(sockfd, (const char *)commande, strlen(commande), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
      
    // TODO : Recupérer la réponse du serveur    
    //n = recvfrom(sockfd, (char *)buffer, MAXBUF, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
    //buffer[n] = '\0'; 
    //printf("Server : %s\n", buffer); 
  
    close(sockfd); 
    return 0; 
}