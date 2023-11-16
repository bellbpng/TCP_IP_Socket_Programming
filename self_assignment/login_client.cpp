#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <memory.h>

typedef struct user_data{
    int id;
    char password[20];
} User;

int main(int argc, char* argv[])
{
    int clnt_sock;
    struct sockaddr_in serv_addr;
    char message[20] = "no response";
    User myInfo;
    if(argc != 5){
        printf("Usage: %s, <IP> <Port> <ID> <Password>\n", argv[0]);
        exit(1);
    }

    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(clnt_sock==-1)
        printf("socket() error!\n");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    myInfo.id = atoi(argv[3]);
    memcpy(&myInfo.password, argv[4], sizeof(argv[4]));
    printf("My ID: %d, Password: %s\n", myInfo.id, myInfo.password);

    if(connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        printf("connect() error!\n");
    
    write(clnt_sock, &myInfo, sizeof(myInfo));
    read(clnt_sock, message, sizeof(message));
    printf("Message from server: %s\n", message);
    close(clnt_sock);
    return 0;
}