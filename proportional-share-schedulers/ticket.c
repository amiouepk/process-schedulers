#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

int psuedo_random();

/* Main function will take care of console input and processing using *getopt*
 * and calls functions in order to execute compartmentalizable tasks
 */

int main(int argc, char** argv) {

    int c;

    static const struct option long_options[] = {
        {"help",          no_argument, NULL, 'h'},
        {"psuedo-random", no_argument, NULL, 'p'}

    };

    c = getopt_long(argc, argv, "p", long_options, NULL);

    switch (c){
        case 'h':
            printf("help\n");
            break;
        case 'p':
            //printf("p?\n");
            psuedo_random();
            break;
        default:
            printf("default case\n");

    }

    


    





    return 0;
}


int psuedo_random() {






    return 0;
}










