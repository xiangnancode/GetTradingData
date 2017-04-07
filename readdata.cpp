/*  	g++ -c  -I/usr/include/curl testcurl.c
 *  	g++ -o testtest testcurl.o -L/usr/lib/libcurl -lcurl
 * 		./testtest
*/
//#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <stdio.h>

#include "curl/curl.h"
#include <ctime>
//#include "/usr/include/curl/easy.h"
using namespace std;

string loadticker() {
  ifstream file ("stocksymbols");
  //cout << "reading tickers... " << endl;
  string entry;
  //while (file.good()) 
  {
    getline(file, entry,'\n');
  }
  file.close();
  return entry;
}

void outputdata(string entry) {
  ofstream file;
  file.open("./output/output1", std::ios_base::app);
  file << entry;
  file.close();
}

int writer(char *data, size_t size, size_t nmemb, string *buffer){
	int result = 0;
	if(buffer != NULL) {
		buffer -> append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
} 

string getonlinedata(){
  /* (A) Variable Declaration */
  CURL *curl;   /* That is the connection, see: curl_easy_init */
  string buffer;    /* See: CURLOPT_WRITEDATA */
  string tickers;
  tickers = loadticker();
  string url = "http://finance.google.com/finance/info?q="+tickers;
  
  /* (B) Initilise web query */
  curl = curl_easy_init();
  
  /* (C) Set Options of the web query 
   * See also:  http://curl.haxx.se/libcurl/c/curl_easy_setopt.html  */
  if (curl){
    //curl_easy_setopt(curl, CURLOPT_URL, "http://ichart.finance.yahoo.com/table.csv?s=DAI.DE&a=NaN&b=02&c=pr-2&g=d&ignore=.csv");
    curl_easy_setopt(curl, CURLOPT_URL, &url[0]);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);   /* No we don't need the Header of the web content. Set to 0 and curl ignores the first line */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0); /* Don't follow anything else than the particular url requested*/
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);  /* Function Pointer "writer" manages the required buffer size */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer ); /* Data Pointer &buffer stores downloaded web content */ 
  }
  else{
    fprintf(stderr,"Error 1\n");  /* Badly written error message */
    return 0;                     
  }
  
  /* (D) Fetch the data */
    curl_easy_perform(curl);
  
  /* (E) Close the connection */
  curl_easy_cleanup(curl);
  return buffer;
}

string pickdata(string rawdata) {
  string res;
  istringstream rawdatastream(rawdata);
  string ticker, entry;
  while (getline (rawdatastream, ticker, '}'))
  {
    istringstream tickerstream(ticker);
    getline(tickerstream, entry, 'l');
    getline(tickerstream, entry, '"');
    getline(tickerstream, entry, '"');
    if(getline(tickerstream, entry, '"')) {
      res += ',';
      res.append(entry);
    }
  }
  res += '\n';
  return res;
}



int main ()
{
  string rawdata;
  string picked;
  string newpicked;
  string saving;

  time_t now;
  tm *gmtm;
  bool processed = false;
  int interval = 5, runtime = 1000;
  while(1) {
  	now = time(0);
  	gmtm = gmtime(&now);
    if (gmtm->tm_sec % interval == 0 && !processed) {
      processed = true;
      rawdata = getonlinedata();
      picked = pickdata(rawdata);
      saving = to_string(gmtm->tm_hour - 4) + ":" + to_string(gmtm->tm_min) + ":" + to_string(gmtm->tm_sec);
      saving.append(picked);
      cout << saving << endl;
      outputdata(saving);
      --runtime;
      if (runtime == 0) break;
    } else if (gmtm->tm_sec % interval != 0) {
    	processed = false;
    }
  }
	return 0;	
}