/* tcp_client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    if (argc < 3) { fprintf(stderr, "usage: %s <ip> <port>\n", argv[0]); return 1; }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in srv = {0};
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    inet_pton(AF_INET, ip, &srv.sin_addr);

    if (connect(sock, (struct sockaddr*)&srv, sizeof(srv)) < 0) { perror("connect"); return 1; }

    char *msg = "Hello from client\n";
    write(sock, msg, strlen(msg));
    char buf[1024];
    ssize_t r = read(sock, buf, sizeof(buf)-1);
    if (r>0) { buf[r]=0; printf("Echo: %s", buf); }
    close(sock);
    return 0;
}

