package main

// include library
import (
	"io"
	"log"
	"net"
)

func main(){
	// get listener
	listener, error := net.Listen("tcp", ":9010") // tcp, port: 9010

	// error handling
	if nil != error{
		log.Fatalf("Fail to bind address to 5032: err: %v", error)
	}
	defer listener.Close()

	log.Printf("## Program Start")
	// main loop
	for{
		// waiting connection
		connection, error := listener.Accept()
		// connection fail
		if nil != error {
			log.Printf("connection fail: %v", error)
			continue
		} else{
			log.Printf("client connection: %v", connection.RemoteAddr())
		}

		// go routine
		go func(){
			buffer := make([]byte,1000) // buffer

			// read loop
			for{
				// input
				count, error := connection.Read(buffer)
				if nil != error{
					if io.EOF == error{
						log.Printf("Connection End: %v", connection.RemoteAddr().String())
					} else{
						log.Printf("Receive error: %v", error)
					}
					return
				}
				if 0 < count{
					// slicing data
					data := buffer[:count]
					log.Println(string(data))
				}
			}
		} ()
	}
}