package main

import (
	"fmt"
	"net/http"
	"html/template"
	"log"
	"time"
)

type Film struct {
	Title string
	Director string
}

func greetHandler(w http.ResponseWriter, r *http.Request) {
	tmpl := template.Must(template.ParseFiles("index.html"))
	films := map[string][]Film{
		"Films": {
			{Title: "The GodFather", Director: "Francis Fors Coppola"},
			{Title: "Blade Runner", Director: "Ridley Scott"},
			{Title: "The thing", Director: "John Carpenter"},
		},
	}
	tmpl.Execute(w, films)
}

func addFilmHandler(w http.ResponseWriter, r *http.Request){
	time.Sleep(1 * time.Second)
	title := r.PostFormValue("title")
	director := r.PostFormValue("director")
	tmpl := template.Must(template.ParseFiles("index.html"))
	tmpl.ExecuteTemplate(w, "film-list-element", Film{Title:title, Director:director})
}

func main() {
	http.HandleFunc("/", greetHandler)
	http.HandleFunc("/add-film/", addFilmHandler)
	fmt.Println("Starting server on port 9999")
	log.Fatal(http.ListenAndServe(":9999", nil))
}