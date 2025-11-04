/*
* Name: Elton Emini
* Date: 11/3/2025
* Purpose: Provide system info using POSIX system calls
*/

// info.c

#include <stdio.h>
#include <time.h>        // For clock_gettime
#include <sys/utsname.h> // For uname
#include <unistd.h>      // For gethostname, sysconf
#include <limits.h>      // For HOST_NAME_MAX
#include <sys/sysinfo.h> // For get_nprocs

int main(int argc, char* argv[])
{
    struct timespec ts;
    struct utsname system_info;
    
    // Allocate a buffer (an array) for the hostname.
    // Using HOST_NAME_MAX is the standard way.
    char hostname[HOST_NAME_MAX + 1];

    // 1. Current time in nanoseconds
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        // ts.tv_nsec is just the nanosecond part of the current second.
        // For a unique value, you could combine ts.tv_sec and ts.tv_nsec,
        // but the prompt specifically asks for nanoseconds.
        printf("Current time (ns part): %ld\n", ts.tv_nsec);
    }

    // 2. System's network name
    if (gethostname(hostname, sizeof(hostname)) == 0 && hostname[0] != '\0') {
        printf("System's network name: %s\n", hostname);
    } 

    // 3, 4, 5. OS Name, Release, Version, and Hardware Type
    if (uname(&system_info) == 0) {
        if (system_info.sysname[0] != '\0') {
            printf("Operating system name: %s\n", system_info.sysname);
        }
        if (system_info.release[0] != '\0') {
            printf("Operating system release: %s\n", system_info.release);
        }
        if (system_info.version[0] != '\0') {
            printf("Operating system version: %s\n", system_info.version);
        }
        if (system_info.machine[0] != '\0') {
            printf("System's hardware type: %s\n", system_info.machine);
        }
    }

    // 6. Number of CPUs
    // get_nprocs() gets the number of *available* processors
    int num_cpus = get_nprocs();
    printf("Number of CPUs: %d\n", num_cpus);
    
    // 7 & 8. Total and Free Physical Memory (in bytes)
    // We get the page size and the number of pages.
    // Memory = page_size * num_pages
    long page_size = sysconf(_SC_PAGESIZE);
    long total_pages = sysconf(_SC_PHYS_PAGES);
    long free_pages = sysconf(_SC_AVPHYS_PAGES); // Available pages

    if (page_size == -1) {
        perror("sysconf: Could not get page size");
    } else {
        if (total_pages != -1) {
            printf("Total physical memory (bytes): %ld\n", total_pages * page_size);
        }
        if (free_pages != -1) {
            printf("Total free memory (bytes): %ld\n", free_pages * page_size);
        }
    }
 
    return 0;
}