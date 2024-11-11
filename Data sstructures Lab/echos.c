// Program 2: C server code to send the echo back to client
#include <sys/types.h>      // For defining types used in socket programming (e.g., socklen_t)
#include <sys/socket.h>     // For socket functions (e.g., socket(), bind(), recvfrom(), sendto())
#include <netinet/in.h>      // For defining sockaddr_in structure and IP address constants (e.g., INADDR_ANY)
#include <unistd.h>          // For close() function to close the socket
#include <netdb.h>           // For host-related functions (though not used in this code)
#include <stdio.h>           // For standard input/output (e.g., printf)
#include <string.h>          // For string manipulation functions (e.g., bzero, strlen)
#include <arpa/inet.h>       // For network-related functions (e.g., htons(), inet_ntoa())

#define MAXLINE 1024         // Define a constant for the maximum buffer size

int main(int argc, char **argv) {
    int sockfd, n;           // sockfd is the socket descriptor, n is the number of bytes received
    socklen_t len;           // len is the length of the client address structure
    char msg[1024];          // Buffer to store incoming and outgoing messages
    struct sockaddr_in servaddr, cliaddr;   // sockaddr_in structures for server and client addresses

    // Create the UDP socket (AF_INET for IPv4, SOCK_DGRAM for UDP)
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {  // Check for socket creation errors
        perror("Socket creation failed");
        return 1;  // Exit if socket creation fails
    }

    // Initialize the server address structure to zero
    bzero(&servaddr, sizeof(servaddr));

    // Fill in the server's address information
    servaddr.sin_family = AF_INET;            // IPv4 address family
    servaddr.sin_addr.s_addr = INADDR_ANY;    // Accept connections on all network interfaces (0.0.0.0)
    servaddr.sin_port = htons(5035);          // Server's port (5035), htons() ensures correct byte order

    // Bind the socket to the server's address
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");                // If bind fails, print an error and exit
        close(sockfd);
        return 1;
    }
    printf("\n\nBinded\n");

    // Now the server is ready to listen for incoming messages
    printf("\n\nListening...\n");

    // Infinite loop to keep the server running and handling client messages
    for(;;) {
        len = sizeof(cliaddr);  // Size of the client address structure

        // Receive a message from the client (blocking call)
        n = recvfrom(sockfd, msg, MAXLINE, 0, (struct sockaddr*)&cliaddr, &len);

        if (n < 0) {  // Check for any error in receiving data
            perror("Recvfrom failed");
            continue;  // Continue to the next iteration in case of error
        }

        // Print the received message from the client
        printf("\nClient's Message: %s\n", msg);

        // If the received message length is less than 6 bytes, print an error
        if (n < 6) {
            perror("Message too short (error in message)");
        }

        // Echo the received message back to the client using sendto()
        if (sendto(sockfd, msg, n, 0, (struct sockaddr*)&cliaddr, len) < 0) {
            perror("Sendto failed");  // If sending the message fails, print an error
            continue;  // Continue the loop even if send fails
        }
    }

    // Close the socket (this will never be reached because of the infinite loop)
    close(sockfd);

    return 0;  // Return 0 to indicate successful program execution (not reached in this case)
}

