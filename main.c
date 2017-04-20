#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 4096
#define DEBUG 0
#define PUSH_COMMAND_DEFAULT "push -i %s -t 'Coin' -m 'Coin Network is Down'"

void *pre_01(char *p) {
    fprintf(stdout, "Path: %s\n", p);
}

void *check(char *p, char* i) {
    int t;
    char *push_command = malloc(sizeof(char) * BUFFER_SIZE);
    char *args = " getinfo 2> /dev/null";
    strcat(p, args);
    if (DEBUG == 1) {
        fprintf(stdout, "+ Command to be executed: %s\n", p);
    }
    t = system(p);
    if ( t != 0 ) {
        sprintf(push_command, PUSH_COMMAND_DEFAULT, i);
        if (DEBUG == 1) {
            fprintf(stdout, "+ Push command to be executed: %s\n", push_command);
        }
        system(push_command);
    }

    free(push_command);
}


int main(int argc, char* argv[])
{
    FILE *fp;
    FILE *fp1;
    char buffer[BUFFER_SIZE];
    char id[BUFFER_SIZE];

    fp = fopen("watchcoin.conf", "r");
    fp1 = fopen("id.conf", "r");
    if ((fp == NULL) || (fp1 == NULL)) {
        fprintf(stderr, "Could not open the config file.\n");
        fprintf(stderr, "Check if 'watchcoin.conf' and 'id.conf' exists.\n");
        exit(1);
    }

    /* Read the data from config file */
    fread(buffer, BUFFER_SIZE, sizeof(char), fp);
    fread(id, BUFFER_SIZE, sizeof(char), fp1);

    pre_01(buffer); /* Prints the path to the stdout */
    check(buffer, id);
    return 0;
}
