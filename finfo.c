/*
* Name: Elton Emini
* Course Section: 111
* Assignment Name: Lab 9 System Calls
* Date: 11/3/2025
* Purpose: Display file information using stat() system call
*/

#include <stdio.h>
#include <stdlib.h>      // For exit(), EXIT_FAILURE
#include <sys/types.h>   // For stat()
#include <sys/stat.h>    // For stat() and file mode macros
#include <unistd.h>      // For stat()
#include <time.h>        // For ctime() to format the date

int main(int argc, char *argv[]) {
    
    
    // MUST be given exactly one argument 
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filepath = argv[1];
    struct stat file_stat; 

    
    // Call stat() returns 0 on success and -1 on error
    if (stat(filepath, &file_stat) == -1) {
        // If it fails, print a detailed error (e.g., "No such file")
        perror(filepath);
        exit(EXIT_FAILURE);
    }


    printf("File Type:            ");
    switch (file_stat.st_mode & S_IFMT) {
        case S_IFREG:  printf("Regular File\n");            break;
        case S_IFDIR:  printf("Directory\n");               break;
        case S_IFLNK:  printf("Symbolic Link\n");           break;
        case S_IFCHR:  printf("Character Device\n");        break;
        case S_IFBLK:  printf("Block Device\n");            break;
        case S_IFIFO:  printf("FIFO\n");       break;
        case S_IFSOCK: printf("Socket\n");                  break;
        default:       printf("Unknown Type\n");            break;
    }

    // b. Permissions 
    char perms[10];
    perms[0] = (file_stat.st_mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (file_stat.st_mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (file_stat.st_mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (file_stat.st_mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (file_stat.st_mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (file_stat.st_mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (file_stat.st_mode & S_IROTH) ? 'r' : '-';
    perms[7] = (file_stat.st_mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (file_stat.st_mode & S_IXOTH) ? 'x' : '-';
    perms[9] = '\0'; // Null terminator
    printf("Permissions:          %s\n", perms);

    // User ID
    printf("Owner UID:            %u\n", file_stat.st_uid);

    // st_size is type off_t, which is a number
    printf("Size (bytes):         %ld\n", (long)file_stat.st_size);

    // Date and time of last modification (formatted)
    printf("Last modified:      %s", ctime(&file_stat.st_mtime));

    return 0; 
}