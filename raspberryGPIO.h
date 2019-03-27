/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   raspberryGPIO.h
 * Author: matthieu
 *
 * Created on 1 mars 2019, 16:22
 */

#ifndef RASPBERRYGPIO_H
#define RASPBERRYGPIO_H

#ifdef __cplusplus
extern "C" {
#endif

    void InitWiringPiGPIO();
    void InitWiringPiGPIOEvent();
    void EvenementCouperInterrupteur();
    void EvenementAllumerInterrupteur();
    int EnvoyerCommande(int index, int etat);
    int WiringPiSetValue(int index, int value);
    int WiringPiGetValue(int index);

#ifdef __cplusplus
}
#endif

#endif /* RASPBERRYGPIO_H */

