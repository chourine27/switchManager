
#include "configuration.h"
#include "initialisation.h"
#include "serveurudp.h"

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

/*    log4c_category_t* logger = NULL;
  
    if (log4c_init()){
        printf("log4c_init() failed");
    }else{
      config.logger = log4c_category_get("switchManager");
      log4c_category_log(logger, LOG4C_PRIORITY_ERROR, "Test");
  */  
    // Initialisation
    initConfig();
    initGPIO();
    initMinuterie();
    pthread_create (&thread_ServeurUDP, NULL, fn_StartServerUDP, NULL);
    pthread_join (thread_ServeurUDP, NULL);
    
    /* Explicitly call the log4c cleanup routine */
/*    if ( log4c_fini()){
      printf("log4c_fini() failed");
    }*/
    return 0;
}
