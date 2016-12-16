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
    mkfifo(pfifo, 0644); //make private fifo
    
    int serverW = open(pfifo, O_WRONLY); //connect to pfifo
    int serverR = open("idc", O_RDONLY); //connect to WKP
    
    write(serverR, pfifo, sizeof(pfifo)); //strlen // sends pid to server
    read(serverW, buffer, sizeof(buffer)); //receives message
    printf("[C]: Message received: %s\n", buffer);
    
    execlp("rm", "rm", pfifo, 0);
    write(serverR, "hi", 3); //sends awknowledgement
    
}

int server_handshake(int * cfd) {
    char * pfifo[20]; 
    char * buffer[20];
    
    if (! mkfifo("idc", 0644) ) printf("Error: %s", strerror(errno)); //make WKP
    printf("[S] WKP created\n");
    
    int clientW = open("idc", O_WRONLY); //connect to WKP
    read(clientW, pfifo, sizeof(pfifo)); //receives pid from client
    printf("[S]: received PID\n");
    
    execlp("rm", "rm", "idc", 0);
    int clientR = open(pfifo, O_WRONLY); //connects to pfifo
    
    write(clientR, "hello", 6); //sends message 
    read(clientW, buffer, sizeof(buffer));
    printf("[S]: Message received %s\n", buffer);
    
    
}