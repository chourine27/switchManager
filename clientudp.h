/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   clientudp.h
 * Author: matthieu
 *
 * Created on December 19, 2018, 7:37 AM
 */

#ifndef CLIENTUDP_H
#define CLIENTUDP_H

#include "constantes.h"

#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

int sendData(char* commande);


#ifdef __cplusplus
}
#endif

#endif /* CLIENTUDP_H */

