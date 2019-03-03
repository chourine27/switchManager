/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tools.h
 * Author: matthieu
 *
 * Created on January 31, 2018, 7:01 AM
 */

#ifndef TOOLS_H
#define TOOLS_H

#ifdef __cplusplus
extern "C" {
#endif

    int splitLine (char* content, char** result);
    int splitString (char *content, char ** result, char *separator);
    int splitInformationInt(char *content, int *result);
    int splitInformationString(char *content, char **result);
    int VerifierDelai(int derniereAction);

#ifdef __cplusplus
}
#endif

#endif /* TOOLS_H */

