/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Test_gestionfichier.c
 * Author: matthieu
 *
 * Created on October 4, 2017, 6:52 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "gestionfichier.h"

/*
 * Simple C Test Suite
 */

void testIsEmpty() {
    FILE* file;
    _Bool result = isEmpty(file);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testIsEmpty (Test_gestionfichier) message=error message sample\n");
    }
}

void testCopieTexteDeConfig() {
    char* parametre;
    char* ligne;
    char* configParam;
    int result = copieTexteDeConfig(parametre, ligne, configParam);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testCopieTexteDeConfig (Test_gestionfichier) message=error message sample\n");
    }
}

void testCopieEntierDeConfig() {
    char* parametre;
    char* ligne;
    int* configParam;
    int valeur;
    int result = copieEntierDeConfig(parametre, ligne, configParam, valeur);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testCopieEntierDeConfig (Test_gestionfichier) message=error message sample\n");
    }
}

void testOuvrirFichier() {
    char* NomFichier;
    FILE* result = OuvrirFichier(NomFichier);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testOuvrirFichier (Test_gestionfichier) message=error message sample\n");
    }
}

void testFermerFichier() {
    FILE* fichier;
    FermerFichier(fichier);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testFermerFichier (Test_gestionfichier) message=error message sample\n");
    }
}

void testChargerConfiguration() {
    FILE* fichier;
    int result = ChargerConfiguration(fichier);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testChargerConfiguration (Test_gestionfichier) message=error message sample\n");
    }
}

void testLireParametre() {
    char* NomFichier;
    char* Parametre;
    char* valeur;
    int result = LireParametre(NomFichier, Parametre, valeur);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testLireParametre (Test_gestionfichier) message=error message sample\n");
    }
}

void testInitialiseValeur() {
    char* nomFichier;
    char* parametre;
    char* valeur;
    int result = InitialiseValeur(nomFichier, parametre, valeur);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testInitialiseValeur (Test_gestionfichier) message=error message sample\n");
    }
}

void testEcrireParametre() {
    char* NomFichier;
    char* Parametre;
    char* Valeur;
    int result = EcrireParametre(NomFichier, Parametre, Valeur);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testEcrireParametre (Test_gestionfichier) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% Test_gestionfichier\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testIsEmpty (Test_gestionfichier)\n");
    testIsEmpty();
    printf("%%TEST_FINISHED%% time=0 testIsEmpty (Test_gestionfichier)\n");

    printf("%%TEST_STARTED%%  testCopieTexteDeConfig (Test_gestionfichier)\n");
    testCopieTexteDeConfig();
    printf("%%TEST_FINISHED%% time=0 testCopieTexteDeConfig (Test_gestionfichier)\n");

    printf("%%TEST_STARTED%%  testCopieEntierDeConfig (Test_gestionfichier)\n");
    testCopieEntierDeConfig();
    printf("%%TEST_FINISHED%% time=0 testCopieEntierDeConfig (Test_gestionfichier)\n");

    printf("%%TEST_STARTED%%  testOuvrirFichier (Test_gestionfichier)\n");
    testOuvrirFichier();
    printf("%%TEST_FINISHED%% time=0 testOuvrirFichier (Test_gestionfichier)\n");

    printf("%%TEST_STARTED%%  testFermerFichier (Test_gestionfichier)\n");
    testFermerFichier();
    printf("%%TEST_FINISHED%% time=0 testFermerFichier (Test_gestionfichier)\n");

    printf("%%TEST_STARTED%%  testChargerConfiguration (Test_gestionfichier)\n");
    testChargerConfiguration();
    printf("%%TEST_FINISHED%% time=0 testChargerConfiguration (Test_gestionfichier)\n");

    printf("%%TEST_STARTED%%  testLireParametre (Test_gestionfichier)\n");
    testLireParametre();
    printf("%%TEST_FINISHED%% time=0 testLireParametre (Test_gestionfichier)\n");

    printf("%%TEST_STARTED%%  testInitialiseValeur (Test_gestionfichier)\n");
    testInitialiseValeur();
    printf("%%TEST_FINISHED%% time=0 testInitialiseValeur (Test_gestionfichier)\n");

    printf("%%TEST_STARTED%%  testEcrireParametre (Test_gestionfichier)\n");
    testEcrireParametre();
    printf("%%TEST_FINISHED%% time=0 testEcrireParametre (Test_gestionfichier)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
