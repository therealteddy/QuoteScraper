/* Author: Ted Jerin 
   Description: A program that scrapes the quotes.toscrape.com for quotes 
   Date: 17-Dec-23
*/

#include <time.h>
#include <stdio.h> 
#include <stdlib.h>
#include <curl/curl.h>
#include <libxml/xpath.h>
#include <libxml/HTMLtree.h>
#include <libxml/HTMLparser.h>

#include "callbacks.h" 
#include "quotes.h"

#define USAGE_STRING "Usage: %s [GENRE]\n [GENRE]:\n \t--inspirational\n\t--love\n\t--life\n\t--humor\n\t--books\n\t--reading\n\t--friendship\n\t--friends\n\t--truth\n\t--simile\n"

signed int randint(int min, int max); 

int main(int argc, char* argv[]) {
   // Setup a base url 
   char url[100] = DEFAULT_URL;

   // Check for cmdline args
   if (argc == 2) {
      if (!strcmp(argv[1], "--help")) {
         printf(USAGE_STRING, argv[0]); 
      }
      else if (!strcmp(argv[1], "--inspirational")) strcat(url, "tag/inspirational/");  
      else if (!strcmp(argv[1], "--love"))          strcat(url, "tag/love/");  
      else if (!strcmp(argv[1], "--life"))          strcat(url, "tag/life/");  
      else if (!strcmp(argv[1], "--humor"))         strcat(url, "tag/humor/");  
      else if (!strcmp(argv[1], "--books"))         strcat(url, "tag/books/");  
      else if (!strcmp(argv[1], "--reading"))       strcat(url, "tag/reading/");  
      else if (!strcmp(argv[1], "--friendship"))    strcat(url, "tag/friendship/");  
      else if (!strcmp(argv[1], "--friends"))       strcat(url, "tag/friends/");  
      else if (!strcmp(argv[1], "--truth"))         strcat(url, "tag/truth/");  
      else if (!strcmp(argv[1], "--simile"))        strcat(url, "tag/simile/");  
      else url; // If all else, let the base url be!
   }

   xmlInitParser();
   CURL* curl = curl_easy_init(); 
   FILE* htmldoc = fopen(SCRAPPED_FILEPATH, "w+");
   htmlDocPtr _htmldoc;  

   if (!curl) {
      fprintf(stderr, "Failed to curl_easy_init()\n"); 
      return 1; 
   }
   if (!htmldoc) {
      fprintf(stderr, "Failed to open/create %s\n", SCRAPPED_FILEPATH);
   }

   // Set url to fetch
   curl_easy_setopt(curl, CURLOPT_URL, url); 

   // Write to either stdio or a file 
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write); 
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, htmldoc);

   // Use these options to avoid ssl verification
   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, CURL_FALSE);
   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, CURL_FALSE);

   CURLcode res = curl_easy_perform(curl); 
   fclose(htmldoc); // close before htmlReadFile()

   // Check if curl_easy_perform() was successful
   if (res != CURLE_OK) {
      printf("Failed to curl_easy_perform()\n%s\n", curl_easy_strerror(res)); 
      return 1;
   }

   // Parse the html file
   _htmldoc = htmlReadFile(SCRAPPED_FILEPATH, "UTF-8", HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
   if (!_htmldoc) {
      fprintf(stderr, "Failed read file %s\n", SCRAPPED_FILEPATH);
      xmlFreeDoc(_htmldoc);
   }

   // See if the document is empty!
   if (!xmlDocGetRootElement((xmlDocPtr) _htmldoc)) {
      fprintf(stderr, "Empty Document %s\n", SCRAPPED_FILEPATH); 
      return 1;
   }

   // Get quotes & authors
   xmlNodeSetPtr quote_ns = xpath_evaluate(_htmldoc, XPATH_QUOTE_EXPR);
   xmlNodeSetPtr author_ns = xpath_evaluate(_htmldoc, XPATH_AUTHOR_EXPR); 
   unsigned int rand_index = randint(0, quote_ns->nodeNr); // The rand_index corresponds to the same author and quote
   printf("%s\n", (char*) quote_ns->nodeTab[rand_index]->content);
   printf("- %s\n", (char*) author_ns->nodeTab[rand_index]->content);

   xmlFreeDoc(_htmldoc);
   curl_easy_cleanup(curl);

   return 0;
}

// Generate a random number between bounds
signed int randint(int min, int max) {
   static int initialzed = 0; 
   if (!initialzed) {
      srand(time(NULL));
      initialzed = 1;
   }
   return (int)(min + (rand() % (max-min)));
}