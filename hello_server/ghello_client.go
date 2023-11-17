package main

import (
	"net"
	"log"
)

func main(){
	connection, error := net.Dial("tcp", ":9010")

	if nil!=error{
		log.Printf("connection fail")
	} else{
		_, error := connection.Write([]byte("Hello World!"))
		if nil==error{
			log.Printf("Send Message Success")
		}
		connection.Close()
	}
}