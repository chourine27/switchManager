/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gestionlog.h
 * Author: matthieu
 *
 * Created on December 28, 2018, 8:37 AM
 */

#ifndef GESTIONLOG_H
#define GESTIONLOG_H

#ifdef __cplusplus
extern "C" {
#endif
    int InitLog();
    int EcrireMessageDebug (char* origine, const char* message);
    int EcrireMessageInfo (char* origine, const char* message);
    int EcrireMessageAlerte (char* origine, const char* message);
    int EcrireMessageErreur (char* origine, const char* message);
    int ecrireMessage (const char* origine, const char* message, const char* libellePriorite, int priorite);
    int terminelog();

#ifdef __cplusplus
}
#endif

#endif /* GESTIONLOG_H */

