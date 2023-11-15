#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    // 클라이언트에게 전달할 메세지
    char message[]="Hello World!";

    if(argc!=2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // 서버 소켓
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 서버의 네트워크 주소와 포트번호 할당 (서버 소켓 파일에 write)
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error!");
    
    // 연결 요청이 가능한 상태로 존재
    if(listen(serv_sock,5)==-1)
        error_handling("listen() error!");

    clnt_addr_size = sizeof(clnt_addr);
    // 연결 요청 수락 시 연결된 클라이언트 주소와 포트 정보가 담김
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    printf("client ip address: %d, port: %d\n", clnt_addr.sin_addr.s_addr, clnt_addr.sin_port);
    if(clnt_sock==-1)
        error_handling("accept() error");

    // 클라이언트 소켓에게 message를 전달. 파일 형태로 다루므로 clnt_sock 에 message를 write 해줌
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
