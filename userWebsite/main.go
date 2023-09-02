package main

import (
	"fmt"
	"net/http"
)

func greetHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w,"<h1> Welcome to my home page </h1>")
	fmt.Fprintf(w,"Request URL path = %s", r.URL.Path)
}

func main() {
	http.HandleFunc("/", greetHandler)
	fmt.Println("Starting server on port 9999")
	http.ListenAndServe(":9999", nil)
}