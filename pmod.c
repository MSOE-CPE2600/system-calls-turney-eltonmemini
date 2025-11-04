/*
* Name: Elton Emini
* Course Section: 111
* Assignment Name: Lab 9 System Calls
* Date: 11/3/2025
* Purpose: Modify process priority and sleep.
*/

#include <stdio.h>
#include <unistd.h>   // For nice()
#include <time.h>     // For nanosleep()
#include <errno.h>    // For errno (used with nice())

int main(int argc, char* argv[]) {

    
    errno = 0;
    
    // Add 10 to the current nice value.
    // A higher nice value means a LOWER priority (it's "nicer").
    int new_nice_val = nice(10); 
    
    if (new_nice_val == -1 && errno != 0) {
        perror("Error changing priority with nice()");
    } else {
        printf("Successfully reduced priority. New nice value: %d\n", new_nice_val);
    }

    // --- 2. Sleep for 1,837,272,638 nanoseconds ---
    
    struct timespec sleep_time;
    
    // 1,837,272,638 ns = 1 second and 837,272,638 nanoseconds
    sleep_time.tv_sec = 1;
    sleep_time.tv_nsec = 837272638L; // 'L' for long

    printf("Sleeping for 1,837,272,638 nanoseconds...\n");
    
    if (nanosleep(&sleep_time, NULL) == -1) {
        perror("nanosleep failed");
    }
    
    printf("Goodbye! Exiting.\n");
    
    return 0;
}