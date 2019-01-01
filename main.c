
#include "configuration.h"
iu#include "initialisation.h"
#include "serveurudp.h"
#include "gestionlog.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
    int i = 0;
    pthread_t thread_ServeurUDP;
    
    printf("  __         o _|_   __  |__   __ __   __   __   __   __   ___   __  \n");
    printf("__)  (__(__( |  |_, (___ |  ) |  )  ) (__( |  ) (__( (__| (__/_ |  ' \n");
    printf("                                                      __/            \n");
    printf("\n");
    printf("\\ | |¯ |¯| |¯  | |¯| |\\|   |¯|   '| \n");
    printf(" \\| |¯ |¯\\  ¯| | |_| | |   |/|    |\n");
    printf("     ¯      ¯               ¯   °   \n");

    // Initialisation
    initLog();
    ecrireMessageInfo("main", "InitLog OK");
    initConfig();
    ecrireMessageInfo("main", "InitConfig OK");
    initGPIO();
    ecrireMessageInfo("main", "InitGPIO OK");
    initMinuterie();
    ecrireMessageInfo("main", "InitMinuterie OK");
    pthread_create (&thread_ServeurUDP, NULL, fn_StartServerUDP, NULL);
    pthread_join (thread_ServeurUDP, NULL);
    
    return 0;
}
