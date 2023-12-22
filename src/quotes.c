#include "quotes.h"

xmlNodeSetPtr xpath_evaluate(htmlDocPtr htmldoc, xmlChar* xpath_expr) {
    xmlXPathContextPtr xpath_ctx = xmlXPathNewContext(htmldoc); 
    xmlXPathObjectPtr xpath_res = xmlXPathEvalExpression(xpath_expr, xpath_ctx); 
    xmlNodeSetPtr xpath_ns = xpath_res->nodesetval; 

    if (!xpath_ctx) {
        fprintf(stderr, "Failed to create a XPath Context!\n");
        return (xmlNodeSetPtr) 0; 
    }

    else if (xmlXPathNodeSetIsEmpty(xpath_ns)) {
        fprintf(stderr, "Nodeset was empty!\n"); 
        xmlXPathFreeObject(xpath_res); 
        return (xmlNodeSetPtr) 0; 
    }
    else return xpath_ns; 
}

void xpath_printns(xmlNodeSetPtr ns) {
    for (int i = 0; i < ns->nodeNr; ++i) {
        if (ns->nodeTab[i]->type == XML_TEXT_NODE) printf("\"%s\"\n", ns->nodeTab[i]->content); 
        else if (ns->nodeTab[i]->type == XML_ELEMENT_NODE) printf("<%s>\n", (char*) ns->nodeTab[i]->name);
        else if (ns->nodeTab[i]->type == XML_COMMENT_NODE) printf("/*%s*/\n", ns->nodeTab[i]->content);
        else if (ns->nodeTab[i]->type == XML_DTD_NODE) printf("<!%s>\n", ns->nodeTab[i]->content);
    }
}