/*  	g++ -c  -I/usr/include/curl testcurl.c
 *  	g++ -o testtest testcurl.o -L/usr/lib/libcurl -lcurl
 * 		./testtest
*/
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include "/usr/include/curl/curl.h"
#include "/usr/include/curl/easy.h"
using namespace std;
int writer(char *data, size_t size, size_t nmemb, string *buffer){
	fprintf(stderr,"Hello I am a function pointer\n");
	int result = 0;
	if(buffer != NULL) {
		buffer -> append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
} 
int main ()
{
	/* (A) Variable Declaration */
	CURL *curl;		/* That is the connection, see: curl_easy_init */
	/*CURLcode res;		/* Not needed, see: curl_easy_cleanup */
	string buffer;		/* See: CURLOPT_WRITEDATA */
	
	/* (B) Initilise web query */
	curl = curl_easy_init();
	
	/* (C) Set Options of the web query 
	 * See also:  http://curl.haxx.se/libcurl/c/curl_easy_setopt.html  */
	if (curl){
		curl_easy_setopt(curl, CURLOPT_URL, "http://ichart.finance.yahoo.com/table.csv?s=DAI.DE&a=NaN&b=02&c=pr-2&g=d&ignore=.csv");
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);	 /* No we don't need the Header of the web content. Set to 0 and curl ignores the first line */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0); /* Don't follow anything else than the particular url requested*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);	/* Function Pointer "writer" manages the required buffer size */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer ); /* Data Pointer &buffer stores downloaded web content */	
	}
	else{
		fprintf(stderr,"Error 1\n");	/* Badly written error message */
		return 0;											
	}
	
	/* (D) Fetch the data */
    curl_easy_perform(curl);
	/* res = curl_easy_perform(curl); */
	/* There is no need for "res" as it is just a flag */	
	
	/* (E) Close the connection */
	curl_easy_cleanup(curl);
	
	/* (F) Transform &buffer into a istringstream object */
	std::istringstream iss(buffer);
	
	string line, item;	
    int linenum = 0;
    while (getline (iss, line)){
        linenum++;													/* Move to Next Line */
        cout << "\nLine #" << linenum << ":" << endl;				/* Terminal Printout */
        std::istringstream linestream(line);						/* Read Next Line */
        int itemnum = 0;
        while (getline (linestream, item, ',')){
            itemnum++;
            cout << "Item #" << itemnum << ": " << item << endl;	/* Terminal Printout */
        } // End WHILE (items)
    } //End WHILE (lines)
	
	return 0;	
}