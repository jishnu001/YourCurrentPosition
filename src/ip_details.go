package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
)

type ipDetail struct {
	As          string
	City        string
	Country     string
	CountryCode string
	ISP         string
	Lat         float32
	Lon         float32
	Org         string
	Query       string
	Region      string
	RegionName  string
	Status      string
	Timezone    string
	Zip         string
}

func main() {
	resp, err := http.Get("http://www.ip-api.com/json")

	if err != nil {
		fmt.Println("Error connecting...")
		log.Fatal(err)
		return
	}

	defer resp.Body.Close()

	var j ipDetail
	err = json.NewDecoder(resp.Body).Decode(&j)

	if err != nil {
		fmt.Println("Error decoding...")
		log.Fatal(err)
	} else {
		fmt.Println(j.Country)
	}

}
