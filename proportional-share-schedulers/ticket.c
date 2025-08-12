#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include "my_process.h"
//#include <linux/time.h>

// #define _POSIX_C_SOURCE 200809L



int psuedo_random();
int ticket_filter(int num_proc, int ticket_num, int* proc_tickets);

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

    exit(EXIT_SUCCESS);
}


int psuedo_random() {

    int ticket_num = 100;
    int sim_length = 100;
    int num_proc = 2;
    int* proc_tickets = malloc(2 * sizeof(int));
    proc_tickets[0] = 75;
    proc_tickets[1] = 25;

    struct timespec tp;
    int cgt_err = clock_gettime(CLOCK_BOOTTIME, &tp);
    if (cgt_err < 0){
        perror("clock_gettime error");
        exit(EXIT_FAILURE);
    }

    unsigned int seed = (tp.tv_sec >> 2) + (tp.tv_nsec >> 2);

    srand(seed);

    int rand_num;
    int draw_num = 0; // number of times the tickets are drawn



    while (draw_num < sim_length){    
        rand_num = rand();
        do {
            rand_num = (rand_num / 10) + 1;
        } while (rand_num > ticket_num);
        
        ticket_filter(num_proc, ticket_num, proc_tickets);
    }

    printf("generated random number: %i\n", rand_num);


    return 0;
}

int ticket_filter(int num_proc, int ticket_num, int* proc_tickets) {

    struct process* proc_arr = malloc(num_proc * sizeof(struct process));
    
    for (int i = 0; i < num_proc; i++){
        proc_arr[i].proc_num = i;
        proc_arr[i].alloc_tickets = proc_tickets[i];
    }




}










