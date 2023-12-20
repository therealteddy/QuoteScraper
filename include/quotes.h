#ifndef QUOTES_H
#define QUOTES_H

#include <libxml/xpath.h> 
#include <libxml/HTMLparser.h>

#define DEFAULT_URL "https://quotes.toscrape.com/"

#define XPATH_QUOTE_EXPR "//body//div[@class=\"quote\"]//span[@class=\"text\"]/text()"
#define XPATH_AUTHOR_EXPR "//body//div[@class=\"quote\"]//span//small[@class=\"author\"]/text()"

/* Evaluate a xpath expression */
xmlNodeSetPtr xpath_evaluate(htmlDocPtr htmldoc, xmlChar* xpath_expr); 

/* Print a nodeset */ 
void xpath_printns(xmlNodeSetPtr ns); 

#endif // QUOTES_H