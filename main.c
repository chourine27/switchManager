
#include "configuration.h"
#include "initialisation.h"
#include "serveurudp.h"
#include "gestionlog.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <error.h>

extern int errno;

int main()
{
    int i = 0;
    pthread_t thread_ServeurUDP;
    printf("\n");
    printf("  __         o _|_   __  |__   __ __   __   __   __   __   ___   __  \n");
    printf("__)  (__(__( |  |_, (___ |  ) |  )  ) (__( |  ) (__( (__| (__/_ |  ' \n");
    printf("                                                      __/            \n");
    printf("\n");
    
    printf("\\ | |¯ |¯| |¯  | |¯| |\\|   |¯|   |¯|\n"); 
    printf(" \\| |¯ |¯\\  ¯| | |_| | |   |/|    ¯|\n"); 
    printf("     ¯      ¯               ¯     ¯ \n"); 

    // Initialisation
//#ifdef DEBUG
    InitLog();
    EcrireMessageInfo("main", "InitLog OK");
//#endif
    initConfig();
    EcrireMessageInfo("main", "InitConfig OK");
    initGPIO();
    EcrireMessageInfo("main", "InitGPIO OK");
    initMinuterie();
    EcrireMessageInfo("main", "InitMinuterie OK");
    pthread_create (&thread_ServeurUDP, NULL, fn_StartServerUDP, NULL);
    pthread_join (thread_ServeurUDP, NULL);
    
    return 0;
}
