/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   infoMinuterie.h
 * Author: matthieu
 *
 * Created on January 25, 2018, 3:01 PM
 */

#ifndef INFOMINUTERIE_H
#define INFOMINUTERIE_H

#ifdef __cplusplus
extern "C" {
#endif

    struct InformationsMinuteries
    {
        char *id;
        int seconde;
        int minute;
        int heure;
        int jour;
        int etat;
        char *bouton;
    };


#ifdef __cplusplus
}
#endif

#endif /* INFOMINUTERIE_H */

