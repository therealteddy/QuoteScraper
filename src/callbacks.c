#include "callbacks.h"

size_t curl_filewrite(void* htmldata, size_t size, size_t nmemb, FILE* htmldoc) {
   return (fwrite(htmldata, size, nmemb, htmldoc)); 
}

size_t curl_print(void* htmldata, size_t size, size_t nmemb, void* userdata) {
   return (fwrite(htmldata, size, nmemb, stdout)); 
}

size_t curl_write(void* htmldata, size_t size, size_t nmemb, void* userdata) {
    return fwrite(htmldata, size, nmemb, ((FILE*)userdata == NULL) ? stdout : (FILE*) userdata); 
}