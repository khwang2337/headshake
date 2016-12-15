#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int client_handshake(int * sfd) {
    char pfifo[20];
    char buffer[20];
    
    itoa(getpid(), pfifo, 10);
    mkfifo(pfifo, 0644);
    int serverW = open(pfifo, O_WRONLY);
    int serverR = open("idc", O_RDONLY);
    write(serverR, pfifo, sizeof(pfifo)); //strlen
    read(serverW, buffer, sizeof(buffer));
    
}

int server_handshake(int * cfd) {
    
    if (! mkfifo("idc", 0644) ) printf("Error: %s", strerror(errno));
    printf("[S] WKP created\n");
    int clientW = open("idc", O_WRONLY);
    char * pfifo[20];
    read(clientW, pfifo, sizeof(pfifo));
    int clientR = open(pfifo, O_WRONLY);
    write(clientR, "hello", 6);
    
    
    
}