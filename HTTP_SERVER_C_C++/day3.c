#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){


    // STEP-1 MAKE KERNAL give u FileDescriptior - YOUR PHONE
    int socketFD = socket( AF_INET,SOCK_STREAM,0);

    printf("DOMAIN:AF = %d ----   TYPE:SOCKsTREAM = %d \n", AF_INET,SOCK_STREAM);

    if(socketFD == -1)  {
        printf("FD assigning failed.. ABORTING \n\n");
        return -1;
    }

    printf("SOCKET FD assigned %d \n\n ", socketFD);


    //STEP-2 (PORT MAPPING) PREPAARE THE ddress structure 
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; //IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; //all interfaces 
    server_addr.sin_port = htons(5001); // Port 5001

     // Step 3: Bind
    if (
        bind(socketFD, 
        (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0
    ){
        perror("Bind failed");
        return 1;
    }
    else
    printf("\n BIND SCUESS 5001 \n");
    




    // Step 4: Listen
    if (  listen(socketFD, 5)  < 0) { 

        perror("Listen failed");
        return 1;
    }
    printf("Server is listening on port 5001...\n");



     // Step 5: Accept one client
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    printf("Waiting for a client to connect...\n");

    int client_fd = accept(socketFD, (struct sockaddr*)&client_addr, &client_len);

    if (client_fd < 0) {
        perror("Accept failed");
        return 1;
    }

    printf("Client connected!\n");


    // Close client socket
    close(client_fd);

    // Close server socket
    close(socketFD);


    return 0;


}