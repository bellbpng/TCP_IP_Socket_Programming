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
- `domain`: 생성할 소켓이 통신을 하기 위해 사용할 프로토콜 설정
- `type`: 소켓이 데이터를 전송하는데 있어서 사용하게 되는 전송 타입을 설정
- `protocol`: 두 호스트 간에 통신을 하는데 있어서 특정 프로토콜을 지정하기 위해 사용됨

**Domain**

1. Protocol Family

- `PF_INET`: IPv4 인터넷 프로토콜
- `PF_INET6`: IPv6 인터넷 프로토콜
- `PF_LOCAL`: Local 통신을 위한 UNIX 프로토콜
- `PF_PACKET`: Low level socket을 위한 인터페이스
- `PF_IPX`: IPX 노벨 프로토콜


2. Address Family

- `AF_INET`: IPv4 인터넷 프로토콜
- `AF_INET6`: IPv6 인터넷 프로토콜
- `AF_LOCAL`: IPv6 인터넷 프로토콜

**TYPE**
- `SOCK_STRAM`: 연결지향의 TCP 프로토콜
- `SOCK_DGRAM`: 데이터그램 지향의 UDP 프로토콜
- `SOCK_RAW`: 생 소켓 혹은 날 소켓으로 불리우는 저수준 socket 제어 프로토콜

**Protocol**
- `IPPROTO_TCP`: 연결지향형 데이터 소켓
- `IPPROTO_UDP`: 비연결지향형 데이터 소켓
- 0을 넣어주면 **TYPE** 정보를 통해 자동으로 TCP 혹은 UDP 프로토콜이 정해진다.

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

## Go 언어로 hello server 번역

**참고 자료**

[Go TCP 소켓 통신하기](https://m.blog.naver.com/sssang97/221900253459)

[net package](https://pkg.go.dev/net)

```go
func Listen(network, address string) (Listener, error)
```
- Host IP주소와 Port 번호를 설정하여 서버 소켓을 만드는 작업
- **network**: `tcp`, `tcp4`, `tcp6`, `unix`, `unixpacket`
- **address**: "IPv4_addr : Port" 와 같은 형태로 입력. IPv4_addr 생략 시 host IP address 로 설정됨


```go
type Listener interface {
	// Accept waits for and returns the next connection to the listener.
	Accept() (Conn, error)

	// Close closes the listener.
	// Any blocked Accept operations will be unblocked and return errors.
	Close() error

	// Addr returns the listener's network address.
	Addr() Addr
}
```
- `Accept()`: conn 객체 반환


```go
type Conn interface {
	// Read reads data from the connection.
	// Read can be made to time out and return an error after a fixed
	// time limit; see SetDeadline and SetReadDeadline.
	Read(b []byte) (n int, err error)

	// Write writes data to the connection.
	// Write can be made to time out and return an error after a fixed
	// time limit; see SetDeadline and SetWriteDeadline.
	Write(b []byte) (n int, err error)

	// Close closes the connection.
	// Any blocked Read or Write operations will be unblocked and return errors.
	Close() error

	// LocalAddr returns the local network address, if known.
	LocalAddr() Addr

	// RemoteAddr returns the remote network address, if known.
	RemoteAddr() Addr

	// SetDeadline sets the read and write deadlines associated
	// with the connection. It is equivalent to calling both
	// SetReadDeadline and SetWriteDeadline.
	//
	// A deadline is an absolute time after which I/O operations
	// fail instead of blocking. The deadline applies to all future
	// and pending I/O, not just the immediately following call to
	// Read or Write. After a deadline has been exceeded, the
	// connection can be refreshed by setting a deadline in the future.
	//
	// If the deadline is exceeded a call to Read or Write or to other
	// I/O methods will return an error that wraps os.ErrDeadlineExceeded.
	// This can be tested using errors.Is(err, os.ErrDeadlineExceeded).
	// The error's Timeout method will return true, but note that there
	// are other possible errors for which the Timeout method will
	// return true even if the deadline has not been exceeded.
	//
	// An idle timeout can be implemented by repeatedly extending
	// the deadline after successful Read or Write calls.
	//
	// A zero value for t means I/O operations will not time out.
	SetDeadline(t time.Time) error

	// SetReadDeadline sets the deadline for future Read calls
	// and any currently-blocked Read call.
	// A zero value for t means Read will not time out.
	SetReadDeadline(t time.Time) error

	// SetWriteDeadline sets the deadline for future Write calls
	// and any currently-blocked Write call.
	// Even if write times out, it may return n > 0, indicating that
	// some of the data was successfully written.
	// A zero value for t means Write will not time out.
	SetWriteDeadline(t time.Time) error
}
```

```go
func Dial(network, address string) (Conn, error)

// Examples
Dial("tcp", "golang.org:http")
Dial("tcp", "192.0.2.1:http")
Dial("tcp", "198.51.100.1:80")
Dial("udp", "[2001:db8::1]:domain")
Dial("udp", "[fe80::1%lo0]:53")
Dial("tcp", ":80")
```
- 매개인자로 전달받은 네트워크와 address에 connect 하는 함수


`defer` 키워드

- 지연 실행 키워드로 main 함수가 종료되기 직전에 해당 구문을 실행한다. 혹은 에러 발생 지점보다 앞에 코드를 구현하면 마지막으로 `defer` 키워드를 실행하고 프로그램이 종료된다.

### 기초 문법

**참고 자료**

[Go Syntax](https://go.dev/blog/declaration-syntax)

```go
// Data Declaration
x: int
p: pointer to int
a: array[3] of int

// Example
x int
p *int
a [3]int
```

```go
// function main takes an int and a slice of strings and returns an int.
func main(argc int, argv []string) int
```

```go
// 길이가 5이고 값이 0인 배열을 만든다. 
a := make([]int, 5)  // len(a)=5

// 길이는 0이고 용량이 5인 배열을 만든다.
b := make([]int, 0, 5) // len(b)=0, cap(b)=5
```
- 동적 배열을 만드는 방법


### 고루틴(goroutine)
- 고루틴은 함수를 동시에 여러개 실행시킬 수 있는 기능으로써 스레드보다 언어 문법이 더 간단하며 OS의 리소스를 덜 사용하는 장점이 있다.
- 함수 앞에 `go`라는 키워드를 붙여줌으로써 호출할 수 있다.
- 함수를 정의하지 않고, 아래와 같이 고루틴에 활용되는 함수를 익명함수라고 한다.

```go
func main(){
    //...

    go func(){
        // do something
    }()

    go func(a int, b int) {
        log.Printf("%d와 %d를 입력으로 받는 함수")
    } (3,4)
}
```


**참고 자료**

[goroutine 사용법](https://phsun102.tistory.com/118)

