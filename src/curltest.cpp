#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{

  CURL *curl;
  CURLcode res;
  std::string readBuffer = "";
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.ip-api.com/json");
    
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res == CURLE_OK) {
        //printf("Contents: %s", readBuffer.c_str());
        Document d;
        d.Parse(readBuffer.c_str());
        printf("Provider : %s\n", d["isp"].GetString());

    }
    else {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    
    }
  }    
  
   
  curl_global_cleanup();
 
  return 0;
}

 
