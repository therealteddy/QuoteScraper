/* Author: Ted Jerin 
   Description: A program that scrapes the web for quotes 
   Date: 17-Dec-23
*/

#include <stdio.h> 
#include <curl/curl.h>
#include <libxml/xpath.h>
#include <libxml/HTMLtree.h>
#include <libxml/HTMLparser.h>

#include "callbacks.h" 

int main(int argc, char* argv[]) {
   CURL* curl = curl_easy_init(); 
   FILE* htmldoc = fopen(SCRAPPED_FILEPATH, "w+");
   htmlDocPtr _htmldoc = htmlReadFile(SCRAPPED_FILEPATH, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING); 
   
   if (!curl) {
      fprintf(stderr, "Failed to curl_easy_init()\n"); 
      return 1; 
   }
   if (!htmldoc) {
      fprintf(stderr, "Failed to open/create %s\n", SCRAPPED_FILEPATH);
   }
   /*if (!_htmldoc) {
      fprintf(stderr, "Failed read file %s\n", SCRAPPED_FILEPATH);
   }*/

   curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com"); 

   // Write to either stdio or a file 
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write); 
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, htmldoc);

   // Use these options to avoid ssl verification
   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, CURL_FALSE);
   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, CURL_FALSE);

   CURLcode res = curl_easy_perform(curl); 

   if (res != CURLE_OK) {
      printf("Failed to curl_easy_perform()\n%s\n", curl_easy_strerror(res)); 
      return 1;
   }

   //xmlFreeDoc(_htmldoc);
   curl_easy_cleanup(curl);
   fclose(htmldoc);

   printf("Done!\n"); 
   return 0;
}