#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
//#include "my_process.h"
//#include <linux/time.h>

// #define _POSIX_C_SOURCE 200809L

struct process {
    int proc_num;
    int alloc_tickets;
    int* range;
};

struct intarray {
    int* array;
    int size;
};

int psuedo_random();
//void range_assign(struct process* proc_arr, int num_proc, int ticket_num);
void ticket_draw(struct process* proc_arr, int num_proc, struct intarray* run_order, int rand_num, int order_index);
struct process* process_create(int num_proc, int* proc_tickets);
void process_print(struct process* proc_arr, int num_proc, struct intarray* run_order, int* rn_arr);

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

    int ticket_num = 100; // needs to be variable
    int sim_length = 1000; // needs to be variable
    int num_proc = 2; // needs to be variable
    int* proc_tickets = malloc(num_proc * sizeof(int)); // needs to be variable
    proc_tickets[0] = 25; // needs to be variable
    proc_tickets[1] = 75;// needs to be variable

    struct timespec tp;
    int cgt_err;
    int rand_num;
    int draw_num = 0; // number of times the tickets are drawn

    struct process* proc_arr = process_create(num_proc, proc_tickets);
    struct intarray run_order;
    run_order.array = malloc(sim_length * sizeof(int));
    run_order.size = sim_length;
    int* rn_arr = malloc(run_order.size * sizeof(int));


    //range_assign(proc_arr, num_proc, ticket_num);

    while (draw_num < sim_length){   

        cgt_err = clock_gettime(CLOCK_BOOTTIME, &tp);
        if (cgt_err < 0){
            perror("clock_gettime error");
            exit(EXIT_FAILURE);
        }

        unsigned int seed = tp.tv_sec + tp.tv_nsec;
        srandom(seed);
        //printf("seed: %i\n", seed);
 
        rand_num = random();
        do {
            rand_num = (rand_num / 10) + 1;
        } while (rand_num > ticket_num);

        rn_arr[draw_num] = rand_num;

        ticket_draw(proc_arr, num_proc, &run_order, rand_num, draw_num);

        draw_num++;
    }

    printf("\n");

    process_print(proc_arr, num_proc, &run_order, rn_arr);

    for (int i = 0; i < num_proc; i++){
        free(proc_arr[i].range);
    }
    free(proc_arr);
    free(proc_tickets);
    free(run_order.array);

    return 0;
}


struct process* process_create(int num_proc, int* proc_tickets){

    struct process* proc_arr = malloc(num_proc * sizeof(struct process));

    int prev_alloc = 0;
    
    for (int i = 0; i < num_proc; i++){
        proc_arr[i].proc_num = i;
        proc_arr[i].alloc_tickets = proc_tickets[i];
        proc_arr[i].range = malloc(2 * sizeof(int));

        proc_arr[i].range[0] = prev_alloc + 1;
        proc_arr[i].range[1] = prev_alloc + proc_arr[i].alloc_tickets;

        printf("process %i\nlow: %d, high: %d\n", i, proc_arr[i].range[0], proc_arr[i].range[1]);  

        prev_alloc = proc_arr[i].alloc_tickets;

    }

    return proc_arr;

}

void ticket_draw(struct process* proc_arr, int num_proc, struct intarray* run_order, int rand_num, int order_index){

    for (int i = 0; i < num_proc; i++){
        if (rand_num >= proc_arr->range[0] && rand_num <= proc_arr->range[1]){
            run_order->array[order_index] = proc_arr[i].proc_num;
        }
    }
}

void process_print(struct process* proc_arr, int num_proc, struct intarray* run_order, int* rn_arr){
    printf("Result: \n");

    for (int i = 0; i < run_order->size; i++) {
        if (i < 10) {
            printf("%i   ", i);
            continue;
        }
        
        printf("%i  ", i);
    }

    printf("\n");
    printf("\n");

    for (int i = 0; i < run_order->size; i++){
        if (rn_arr[i] < 10){
            printf("%i   ", run_order->array[i]);
            continue;
        }
        printf("%i  ", rn_arr[i]);

    }

    printf("\n");
    printf("\n");

    for (int i = 0; i < run_order->size; i++){
        if (run_order->array[i] < 10){
            printf("%i   ", run_order->array[i]);
            continue;
        }
        printf("%i  ", run_order->array[i]);

    }

    printf("\n");

}




