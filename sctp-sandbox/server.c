#include "common.h"
#include <pthread.h>

int get_message(int server_fd, struct sockaddr_in *sender_addr);
int send_reply(int server_fd, struct sockaddr_in* dest_addr);


int main(int argc, char* argv[])
{
    int server_fd = 0;
    int server_port = SERVER_PORT;

    if(argc == 2) {
        server_port = atoi(argv[1]);
        if(server_port < 1 || server_port > 65535) {
            printf("Invalid port number (%d). Valid values are between 1 and 65535.\n", server_port);
            return 1;
        }
    }
    else if(argc != 1) { // argc can be two (port number passed) or one (no params passed)
        printf("Usage: %s [PORT NUMBER TO BIND TO]\n", argv[0]);
        return 2;
    }
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    //server_fd = socket(ADDR_FAMILY, SOCK_TYPE, PROTO)

    if((server_fd) == -1) {
        perror("socket");
        return 3;
    }

    //enable some notifications
    if(enable_notifications(server_fd) != 0) {
        printf("Error enabling notifications\n");
        return 4;
    }


    struct sockaddr_in bind_addr;
    memset(&bind_addr, 0, sizeof(struct sockaddr_in));
    bind_addr.sin_family = ADDR_FAMILY;
    bind_addr.sin_port = htons(server_port);
    bind_addr.sin_addr.s_addr = INADDR_ANY;

    if(sctp_bindx(server_fd, (struct sockaddr*)&bind_addr, 1, SCTP_BINDX_ADD_ADDR) == -1) {
        perror("bind");
        return 5;
    }

    if(listen(server_fd, SERVER_LISTEN_QUEUE_SIZE) != 0) {
        perror("listen");
        return 6;
    }

    printf("Listening on port %d\n", server_port);

    struct sockaddr_in addr_buf;

    while(1) {
        memset(&addr_buf, 0, sizeof(addr_buf));

        if(get_message(server_fd, &addr_buf)) {
            break;
        }

        if(send_reply(server_fd, &addr_buf)) {
            break;
        }
    }

    return 7;
}

int get_message(int server_fd, struct sockaddr_in* sender_addr)
{
    char payload[1024];
    int buffer_len = sizeof(payload) - 1;
    memset(&payload, 0, sizeof(payload));

    int sender_addr_size = sizeof(struct sockaddr_in);

    struct sctp_sndrcvinfo snd_rcv_info;
    memset(&snd_rcv_info, 0, sizeof(snd_rcv_info));

    int msg_flags = 0;

    while(1) {
        int recv_size = 0;

        if((recv_size = sctp_recvmsg(server_fd, &payload, buffer_len, (struct sockaddr*)sender_addr, &sender_addr_size, &snd_rcv_info, &msg_flags)) == -1) {
            printf("recvmsg() error\n");
            return 1;
        }

        if(msg_flags & MSG_NOTIFICATION) {
            if(!(msg_flags & MSG_EOR)) {
                printf("Notification received, but the buffer is not big enough.\n");
                continue;
            }

            handle_notification((union sctp_notification*)payload, recv_size, server_fd);
        }
        else if(msg_flags & MSG_EOR) {
            printf("%s\n", payload);
            break;
        }
        else {
            printf("%s", payload); //if EOR flag is not set, the buffer is not big enough for the whole message
        }
    }

    return 0;
}

int send_reply(int server_fd, struct sockaddr_in* dest_addr)

{
    char buf[8];
    memset(buf, 0, sizeof(buf));
    strncpy(buf, "OK", sizeof(buf)-1);

    if(sctp_sendmsg(server_fd, buf, strlen(buf), (struct sockaddr*)dest_addr, sizeof(struct sockaddr_in), 0, 0, 0, 0, 0) == -1) {
        printf("sendmsg() error\n");
        return 1;
    }

    return 0;
}
