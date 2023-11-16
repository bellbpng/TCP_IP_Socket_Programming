## Hello World 서버 프로그램 구현
- 클라이언트가 서버에 연결요청을 하고, 연결요청 수락 시 "Hello World!" 라고 응답해주는 서버 프로그램

### 소켓의 생성 과정
- 소켓 생성 -> `socket` 함수 호출
- IP주소와 PORT번호 할당 -> `bind` 함수 호출
- 연결요청 가능 상태로 변경 -> `listen` 함수 호출
- 연결요청에 대한 수락 -> `accept` 함수 호출

### 주요 함수 정리
```c++
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```
- 소켓을 생성하는 함수
- 성공 시 파일 디스크립터, 실패 시 -1 반환

```c++
#include <sys/socket.h>
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
```
- IP주소, PORT번호라는 소켓의 주소정보를 할당
- 성공 시 0, 실패 시 -1 반환

```c++
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```
- 소켓을 연결 요청이 가능한 상태로 만들어줌
-성공 시 0, 실패 시 -1 반환

```c++
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr_t *addr, socklen_t *addrlen);
```
- 연결 요청을 수락함
- 성공 시 파일 디스크립터, 실패 시 -1 반환

### 클라이언트와 서버 간의 동작
- ![image](https://github.com/bellbpng/TCP_IP_Socket_Programming/assets/59792046/80c6b08e-87b8-41b0-98dd-5cf4d483700e)
