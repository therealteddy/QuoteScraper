#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <stdio.h> 

#define CURL_TRUE 1L 
#define CURL_FALSE 0L 

#define SCRAPPED_FILEPATH "./src/scrapped.html"

// Callback to print to stdio 
size_t curl_print(void* htmldata, size_t size, size_t nmemb, void* userdata); 

// Callback to write to user defined file descriptor 
size_t curl_filewrite(void* htmldata, size_t size, size_t nmemb, FILE* htmldoc);

// Callback to write to either stdio or fd depending on userdata 
size_t curl_write(void* htmldata, size_t size, size_t nmemb, void* userdata); 

#endif // CALLBACKS_H