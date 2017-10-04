/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Test_gestiongpio.c
 * Author: matthieu
 *
 * Created on October 4, 2017, 6:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "gestiongpio.h"

/*
 * Simple C Test Suite
 */

void testEtatRelai() {
    int index;
    int result = EtatRelai(index);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testEtatRelai (Test_gestiongpio) message=error message sample\n");
    }
}

void testActiverRelai() {
    int index;
    int result = ActiverRelai(index);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testActiverRelai (Test_gestiongpio) message=error message sample\n");
    }
}

void testDesactiverRelai() {
    int index;
    int result = DesactiverRelai(index);
    if (1 /*check result*/) {
        printf("%%TEST_FAILED%% time=0 testname=testDesactiverRelai (Test_gestiongpio) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% Test_gestiongpio\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testEtatRelai (Test_gestiongpio)\n");
    testEtatRelai();
    printf("%%TEST_FINISHED%% time=0 testEtatRelai (Test_gestiongpio)\n");

    printf("%%TEST_STARTED%%  testActiverRelai (Test_gestiongpio)\n");
    testActiverRelai();
    printf("%%TEST_FINISHED%% time=0 testActiverRelai (Test_gestiongpio)\n");

    printf("%%TEST_STARTED%%  testDesactiverRelai (Test_gestiongpio)\n");
    testDesactiverRelai();
    printf("%%TEST_FINISHED%% time=0 testDesactiverRelai (Test_gestiongpio)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
