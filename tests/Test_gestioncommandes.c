/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Test_gestioncommandes.c
 * Author: matthieu
 *
 * Created on October 4, 2017, 6:51 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "gestioncommandes.h"

/*
 * Simple C Test Suite
 */

void testExecuterCommande() {
    char* commande;
    char* resultat;
    int result = ExecuterCommande(commande, resultat);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testExecuterCommande (Test_gestioncommandes) message=error message sample\n");
    }
}

void testRetournerInformationConfig() {
    char* parametreALire;
    char* valeurDefaut;
    char* resultat;
    int result = RetournerInformationConfig(parametreALire, valeurDefaut, resultat);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testRetournerInformationConfig (Test_gestioncommandes) message=error message sample\n");
    }
}

void testRetournerInformationConfigIndex() {
    char* parametreALire;
    char* index;
    char* valeurDefaut;
    char* resultat;
    int result = RetournerInformationConfigIndex(parametreALire, index, valeurDefaut, resultat);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testRetournerInformationConfigIndex (Test_gestioncommandes) message=error message sample\n");
    }
}

void testModifierInformationsConfig() {
    char* parametreAMettreAJour;
    char* valeurAMettreAJour;
    int result = ModifierInformationsConfig(parametreAMettreAJour, valeurAMettreAJour);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testModifierInformationsConfig (Test_gestioncommandes) message=error message sample\n");
    }
}

void testRetournerEtatBouton() {
    int identifiantBouton;
    char* resultat;
    int result = RetournerEtatBouton(identifiantBouton, resultat);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testRetournerEtatBouton (Test_gestioncommandes) message=error message sample\n");
    }
}

void testRetournerEtatBouton2() {
    int identifiantBouton;
    int result = retournerEtatBouton(identifiantBouton);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testRetournerEtatBouton2 (Test_gestioncommandes) message=error message sample\n");
    }
}

void testChangerStatutBouton() {
    int identifiantBouton;
    int statutBouton;
    int result = ChangerStatutBouton(identifiantBouton, statutBouton);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testChangerStatutBouton (Test_gestioncommandes) message=error message sample\n");
    }
}

void testIdentifiantBoutonPlosible() {
    int identifiantBouton;
    int result = IdentifiantBoutonPlosible(identifiantBouton);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testIdentifiantBoutonPlosible (Test_gestioncommandes) message=error message sample\n");
    }
}

void testStatutBoutonPlosible() {
    int statutBouton;
    int result = StatutBoutonPlosible(statutBouton);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testStatutBoutonPlosible (Test_gestioncommandes) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% Test_gestioncommandes\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testExecuterCommande (Test_gestioncommandes)\n");
    testExecuterCommande();
    printf("%%TEST_FINISHED%% time=0 testExecuterCommande (Test_gestioncommandes)\n");

    printf("%%TEST_STARTED%%  testRetournerInformationConfig (Test_gestioncommandes)\n");
    testRetournerInformationConfig();
    printf("%%TEST_FINISHED%% time=0 testRetournerInformationConfig (Test_gestioncommandes)\n");

    printf("%%TEST_STARTED%%  testRetournerInformationConfigIndex (Test_gestioncommandes)\n");
    testRetournerInformationConfigIndex();
    printf("%%TEST_FINISHED%% time=0 testRetournerInformationConfigIndex (Test_gestioncommandes)\n");

    printf("%%TEST_STARTED%%  testModifierInformationsConfig (Test_gestioncommandes)\n");
    testModifierInformationsConfig();
    printf("%%TEST_FINISHED%% time=0 testModifierInformationsConfig (Test_gestioncommandes)\n");

    printf("%%TEST_STARTED%%  testRetournerEtatBouton (Test_gestioncommandes)\n");
    testRetournerEtatBouton();
    printf("%%TEST_FINISHED%% time=0 testRetournerEtatBouton (Test_gestioncommandes)\n");

    printf("%%TEST_STARTED%%  testRetournerEtatBouton2 (Test_gestioncommandes)\n");
    testRetournerEtatBouton2();
    printf("%%TEST_FINISHED%% time=0 testRetournerEtatBouton2 (Test_gestioncommandes)\n");

    printf("%%TEST_STARTED%%  testChangerStatutBouton (Test_gestioncommandes)\n");
    testChangerStatutBouton();
    printf("%%TEST_FINISHED%% time=0 testChangerStatutBouton (Test_gestioncommandes)\n");

    printf("%%TEST_STARTED%%  testIdentifiantBoutonPlosible (Test_gestioncommandes)\n");
    testIdentifiantBoutonPlosible();
    printf("%%TEST_FINISHED%% time=0 testIdentifiantBoutonPlosible (Test_gestioncommandes)\n");

    printf("%%TEST_STARTED%%  testStatutBoutonPlosible (Test_gestioncommandes)\n");
    testStatutBoutonPlosible();
    printf("%%TEST_FINISHED%% time=0 testStatutBoutonPlosible (Test_gestioncommandes)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
