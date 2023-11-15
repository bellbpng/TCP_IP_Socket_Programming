#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char* message);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if(argc!=3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 소켓을 만들고 파일 디스크립터를 반환 받음(소켓을 파일 형태로 처리)
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");

    // 연결 요청할 서버의 IP 주소와 PORT 번호 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]); // ip 주소
    serv_addr.sin_port = htons(atoi(argv[2])); // port 번호. 호스트 데이터(리틀 엔디안) -> 네트워크 바이트(빅 엔디안) 순서로 변환

    // 입력 받은 서버의 주소정보를 가지고 연결 요청
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error!");

    // 서버로 부터 메세지를 전달 받음 (sock 파일을 읽어서 message 버퍼에 저장)
    str_len=read(sock, message, sizeof(message)-1);
    if(str_len==-1)
        error_handling("read() error!");

    printf("Message from server : %s \n", message);
    close(sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

