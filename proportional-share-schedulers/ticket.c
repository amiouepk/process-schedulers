#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

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
            printf("p?\n");
            break;
        default:
            printf("default case\n");

    }


    //getopt_long();

    





    return 0;
}