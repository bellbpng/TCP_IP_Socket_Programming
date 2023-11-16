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

