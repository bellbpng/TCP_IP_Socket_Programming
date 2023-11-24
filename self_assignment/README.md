## Self Project
- A server checks login id and password from clients
- This is a self-project for studying socket programming

## Struct Declaration

- 출처: [제임스딘딘의 Tech & Life:티스토리](https://techlog.gurucat.net/292)

```c++
struct sockaddr {
	u_short    sa_family;     // address family, 2 bytes
	char    sa_data[14];     // IP address + Port number, 14 bytes
};
```
- 소켓의 주소를 담는 기본 구조체 역할
- 총 16바이트 크기의 구조체

```c++
// IPv4 주소체계를 사용함
struct sockaddr_in {
	short    sin_family;          // 주소 체계: AF_INET
	u_short  sin_port;            // 16 비트 포트 번호, network byte order
	struct   in_addr  sin_addr;   // 32 비트 IP 주소
	char     sin_zero[8];         // 전체 크기를 16 비트로 맞추기 위한 dummy
};

struct  in_addr {
	u_long  s_addr;     // 32비트 IP 주소를 저장 할 구조체, network byte order
};

```
- sockaddr 구조체에서 sa_family 가 AF_INET 인 경우에 사용하는 구조체
- sockaddr 을 그대로 사용할 경우, sa_data에 IP주소와 Port 번호가 조합되어 있어 쓰거나 읽기 불편하다.
- `sin_family`: 항상 **AF_INET** 을 설정
- `sin_addr`: 호스트 IP 주소로 이 변수에는 **INADDR_ANY** 와 같은 것이 저장되어야 한다. 혹은, `inet_aton()`, `inet_addr()`, `inet_makeaddr()` 과 같은 라이브러리가 제공하는 함수의 반환값이 저장되어야 한다.
- `sin_zero`: 8바이틔 더미 데이터. 반드시 0으로 채워져 있어야 함. sockaddr 구조체 크기와 맞추기 위한 용도
- `server_addr.sin_addr.s_addr = INADDR_ANY`: 서버의 경우 이러한 방식으로 주소를 할당하는데, 이것은 **자동으로 이 컴퓨터에 존재하는 랜카드 중 사용가능한 랜카드의 IP주소를 사용하겠다** 를 의미한다.

## Communication Functions
```c
#include <sys/socket.h>
ssize_t send(int sockfd, const void* msg, size_t nbytes, int flags);
```
- `sockfd`: target socket file descriptor
	- server: accept() 함수로 생성된 소켓
	- client: socket() 함수로 생성된 소켓
- 데이터 전송 함수
- 데이터 전송 성공 시 전송한 데이터 바이트 수, 실패 시 -1 반환


```c
#include <sys/socket.h>
ssize_t recv(int sockfd, void* buf, size_t len, int flags);
```
- `sockfd`: source socket file descriptor
	- server: accept() 함수로 생성된 소켓
	- client: socket() 함수로 생성된 소켓
- 데이터 수신 함수
- 데이터 수신 성공 시 수신한 데이터 바이트 수, 실패 시 -1 반환


```c
#include <unistd.h>
ssize_t write(int fd, const void* buf, size_t count);
```
- `fd`: target socket file descriptor
	- server: accept() 함수로 생성된 소켓
	- client: socket() 함수로 생성된 소켓
- 파일에 데이터를 쓰는 함수
- 소켓을 하나의 파일의 형태로 다루기 때문에 가능함


```c
#include <unistd.h>
ssize_t read(int fd, void* buffer, size_t count);
```
- `fd`: target socket file descriptor
	- server: accept() 함수로 생성된 소켓
	- client: socket() 함수로 생성된 소켓
- 파일에 있는 데이터를 읽는 함수
- 소켓을 하나의 파일의 형태로 다루기 때문에 가능함

