#include <stdio.h>          // For printf
#include <sys/socket.h>     // For socket()
#include <unistd.h>         // For close()

int main() {
    
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // socket(domain, type, protocol)
    // AF_INET = Use IPv4
    // SOCK_STREAM = Use TCP (reliable connection)
    // 0 = Let OS choose correct protocol automatically
    

    // If socket creation failed, it returns -1
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        return 1;
    }

    // If success, Linux gives a small number
    // That number is your communication handle
    printf("Socket created successfully\n");

    printf("Socket file descriptor number is: %d\n", sockfd);

    // We are done using it
    // So we close it
    close(sockfd);

    return 0;
}