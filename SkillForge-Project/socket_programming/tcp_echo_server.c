/* tcp_echo_server.c */
#include <stdio.h>      // For printf(), perror()
#include <stdlib.h>     // For exit()
#include <string.h>     // For memset(), string functions
#include <errno.h>      // For errno
#include <unistd.h>     // For read(), write(), close()
#include <arpa/inet.h>  // For sockaddr_in, htons(), inet_ntoa()
#include <sys/socket.h> // For socket(), bind(), listen(), accept()

#define PORT 12345      // TCP port number for the server
#define BACKLOG 10      // Max number of pending connection requests
#define BUFSZ 4096      // Buffer size for reading client data

int main() {
    int srv = socket(AF_INET, SOCK_STREAM, 0);   // Create a TCP socket (IPv4)
    if (srv < 0) { perror("socket"); exit(1); }  // Check for socket creation failure

    int opt = 1;                                       
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));   // Allow immediate reuse of port in TIME_WAIT

    struct sockaddr_in addr = {0};   // Zero-initialize address structure
    addr.sin_family = AF_INET;       // Set address family to IPv4
    addr.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces
    addr.sin_port = htons(PORT);     // Convert port number to network byte order

    if (bind(srv, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(1);     // Bind socket to IP + port
    }

    if (listen(srv, BACKLOG) < 0) {
        perror("listen"); exit(1);   // Mark socket as listening for connections
    }

    printf("Listening on %d\n", PORT);

    while (1) {   // Infinite loop: continuously accept client connections
        struct sockaddr_in cli;           // Structure to hold client address
        socklen_t clilen = sizeof(cli);   // Size of client address structure

        int cli_fd = accept(srv, (struct sockaddr*)&cli, &clilen);
        if (cli_fd < 0) { perror("accept"); continue; } // Accept a client

        char buf[BUFSZ];   // Buffer to store incoming data
        ssize_t r;         // Number of bytes read

        // Read data from the client in a loop
        while ((r = read(cli_fd, buf, sizeof(buf))) > 0) {
            ssize_t w = 0, total = 0;

            // Ensure full write (handle partial writes)
            while (total < r) {
                w = write(cli_fd, buf + total, r - total);  // Echo back data
                if (w < 0) { perror("write"); break; }      // Handle write errors
                total += w;                                 // Advance write offset
            }
        }

        close(cli_fd);  // Close the client connection
    }

    close(srv);  // Close the server socket (unreachable in this loop)
    return 0;
}

