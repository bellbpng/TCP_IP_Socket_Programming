#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct user_data{
    int user_id;
    char password[20];
} User;

User database[] = {{0, "1234"}, {1, "abcd"}, {2, "0000"}};

int findUser(int id, char password[]){
    for(int i=0; i<3; i++){
        if(database[i].user_id == id){
            int len = strlen(password);
            printf("password size: %d\n", len);
            for(int j=0; j<len; j++){
                if(password[j] != database[i].password[j])
                    return 0;
            }
            return 1;
        }
    }
    return 0;
}

// argc: count of arguments, argv[]: string input data
int main(int argc, char* argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    User data;
    int msg_len;

    if(argc != 2){
        printf("Usage: %s <Port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1){
        printf("socket() error!\n");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // IPv4 internet protocol
    serv_addr.sin_port = htons(atoi(argv[1])); // port number
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 32bit IPv4 Address

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){
        printf("bind() error!\n");
    }

    if(listen(serv_sock, 5)==-1){
        printf("listen() error!\n");
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1){
        printf("accept() error!\n");
    }

    while(true){
        msg_len = read(clnt_sock, &data, sizeof(data));
        if(msg_len==-1) break;
        printf("User id: %d, Password: %s\n", data.user_id, data.password);
        if(findUser(data.user_id, data.password))
            write(clnt_sock, "Login Success", 20);
        else
            write(clnt_sock, "Login Fail", 20);
    }
    close(clnt_sock);
    close(serv_sock);
    return 0;
}