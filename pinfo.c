/*
* Name: Elton Emini
* Date: 11/3/2025
* Purpose: get process priority and scheduling info
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

#include <stdlib.h>   // For atoi, exit, EXIT_FAILURE
#include <unistd.h>   // For getpid
#include <errno.h>    // For error checking (errno)


const char* get_scheduler_name(int policy) {
    switch (policy) {
        case SCHED_OTHER:
            return "SCHED_OTHER (Standard time-sharing)";
        case SCHED_FIFO:
            return "SCHED_FIFO (Real-time First-In, First-Out)";
        case SCHED_RR:
            return "SCHED_RR (Real-time Round-Robin)";
        case SCHED_BATCH:
            return "SCHED_BATCH (Batch processing)";
        case SCHED_IDLE:
            return "SCHED_IDLE (Idle-priority)";
        default:
            return "Unknown Policy";
    }
}

int main(int argc, char* argv[]) {
    
    pid_t pid; 

    if (argc == 1) {
        pid = getpid();
        printf("Getting info for current process (PID: %d)\n", pid);
    } else if (argc == 2) {
        pid = (pid_t)atoi(argv[1]); 
        if (pid <= 0) {
            fprintf(stderr, "Error: Invalid PID specified: %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        printf("Getting info for target process (PID: %d)\n", pid);
    } else {
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

   
    int policy = sched_getscheduler(pid);
    
    if (policy == -1) {
        // Handle errors. The assignment requires checking for a non-existent PID.
        if (errno == ESRCH) { // ESRCH = Error, No Such Process
            fprintf(stderr, "Error: Process with PID %d does not exist.\n", pid);
        } else {
            perror("sched_getscheduler failed");
        }
        exit(EXIT_FAILURE); 
    }

    
    struct sched_param param;
    
    // sched_getparam() fills the 'param' struct with scheduling parameters
    if (sched_getparam(pid, &param) == -1) {
        
        if (errno == ESRCH) {
            fprintf(stderr, "Error: Process with PID %d does not exist.\n", pid);
        } else {
            perror("sched_getparam failed");
        }
        exit(EXIT_FAILURE);
    }

    
    printf("  - Process Priority: %d\n", param.sched_priority);
    printf("  - Scheduling Method: %s\n", get_scheduler_name(policy));

    return 0; 
}