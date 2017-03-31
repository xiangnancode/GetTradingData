#include <iostream>
//#include <stdio.h>
#include <curl/curl.h>


int main(void) {
  CURL *curl;
  CURLcode res;
  //https://curl.haxx.se/libcurl/c/curl_easy_init.html
  curl = curl_easy_init(); 
  if(curl) {
    //https://curl.haxx.se/libcurl/c/curl_easy_setopt.html
    curl_easy_setopt(curl, CURLOPT_URL, "http://finance.google.com/finance/info?&q=TZA");
    //https://curl.haxx.se/libcurl/c/curl_easy_perform.html
    res = curl_easy_perform(curl);
    /* always cleanup */
    //https://curl.haxx.se/libcurl/c/curl_easy_cleanup.html
    curl_easy_cleanup(curl);
  }
  return 0;
}