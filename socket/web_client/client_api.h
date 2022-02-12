#ifndef __CLIENT_API_H_
#define __CLIENT_API_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_BUFFER_LEN  1025
#define MAX_TOKEN_LEN   5

int fd;
int isconnect;
pthread_t recv_tid;

void error(char* msg);
void terminate();
int parsing(char* str, char* token[], char* ch);
int init(char* ip, int port);
void* recv_data();

#endif /* __CLIENT_API_H_ */