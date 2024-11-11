#include <arpa/inet.h>    // For socket programming and address manipulation
#include <string.h>        // For string manipulation functions (e.g., strcpy, memset)
#include <stdio.h>         // For standard input/output functions
#include <stdlib.h>        // For memory allocation and process termination (e.g., exit())
#include <unistd.h>        // For close() function (to close sockets)

#define MAXLINE 1024       // Define the maximum buffer size for communication (1024 bytes)

int main(int argc, char *argv[]) {
    int sockfd, n;             // sockfd: socket file descriptor; n: number of bytes received
    socklen_t len;             // Length of the server address structure
    char sendline[MAXLINE], recvline[MAXLINE]; // Buffers for sending and receiving data
    struct sockaddr_in servaddr;   // Structure to hold the server's address information

    // Prompt the user to enter a message
    printf("\nEnter the message: ");
    if (fgets(sendline, sizeof(sendline), stdin) == NULL) {  // Read input from stdin
        perror("Error reading input");
        exit(1);  // Exit if reading input fails
    }

    // Remove the trailing newline character from the input (if it exists)
    sendline[strcspn(sendline, "\n")] = '\0';

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {  // AF_INET means IPv4, SOCK_DGRAM for UDP
        perror("Socket creation failed");
        exit(1);  // Exit if socket creation fails
    }

    // Initialize the server address structure to zero
    bzero(&servaddr, sizeof(servaddr));  // Clear the memory for servaddr structure

    servaddr.sin_family = AF_INET;                   // Set address family to AF_INET (IPv4)
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Set the server's IP address (localhost)
    servaddr.sin_port = htons(5035);                  // Set the server's port number (5035), htons() ensures correct byte order

    // Send the message to the server using the sendto() function
    len = sizeof(servaddr);  // Set the length of the server address structure
    if (sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *) &servaddr, len) < 0) {  // Send data
        perror("Send failed");
        close(sockfd);  // Close the socket on failure
        exit(1);  // Exit the program
    }

    // Receive the server's response using the recvfrom() function
    n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);  // Receive data (blocking call)
    if (n < 0) {  // Check for errors during receiving
        perror("Receive failed");
        close(sockfd);  // Close the socket on failure
        exit(1);  // Exit the program
    }

    recvline[n] = '\0';  // Null-terminate the received string (to ensure it's a valid C string)

    // Print the received message (server's echo)
    printf("\nServer's Echo: %s\n\n", recvline);

    // Close the socket after communication is done
    close(sockfd);
    return 0;  // Return 0 to indicate successful execution
}

