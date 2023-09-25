#include "kernel/types.h"
#include "user.h"


int main(uint argc, char * argv[]){
    int p[2];
    char message[10];
    pipe(p);

    int pid = fork();
    if (pid < 0){
        printf("fork failed");
        exit(1);
    }

    if(pid == 0){
        read(p[0], message, sizeof(message));
        close(p[0]);
        printf("<child pid: %d>: got %s\n", getpid(), message);

        write(p[1], "pong", 5);
        close(p[1]);

        exit(0);
    }
    else{
        write(p[1], "ping", 5);
        close(p[1]);

        read(p[0], message, sizeof(message));
        close(p[0]);
        printf("<parent pid: %d>: got %s\n", getpid(), message);

        exit(0);
    }
    
    exit(0);
}


