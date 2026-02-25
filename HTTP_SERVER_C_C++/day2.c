#include <stdio.h>          // printf
#include <string.h>         // memset
#include <unistd.h>         // close
#include <sys/socket.h>     // socket
#include <netinet/in.h>     // sockaddr_in

int main() {

    // Step 1: Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        printf("Socket creation failed\n");
        return 1;
    }

    printf("Socket created successfully\n");


    
    // Step 2: Create address structure
    struct sockaddr_in server_addr;

    // Clear memory (good practice)
    memset(&server_addr, 0, sizeof(server_addr));

    // Set address family (IPv4)
    server_addr.sin_family = AF_INET;

    // Accept connections from any IP
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Set port number (convert to network format)
    server_addr.sin_port = htons(5001);



    // Step 3: Bind socket to IP + Port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Bind failed\n");
        return 1;
    }

    printf("Bind successful. Server attached to port 5001\n");

    // Close socket (we are done for today)
    close(server_fd);

    return 0;
}