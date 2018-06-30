#include <stdio.h>
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>

using namespace rapidxml;
using namespace std;

int main() {
  const char* pFileName = "cybermarsch.xml";

  FILE* p = fopen(pFileName, "r");

  if(!p)
    printf("Error!\n");

  printf("Opened %s\n", pFileName);

  char pText[60000];

  fread(pText, 1, sizeof(pText), p);

  xml_document<> doc;
  doc.parse<0>(pText);

//  print(std::cout, doc, 0);

  xml_node<>* pRootNode = doc.first_node();
  cout << "Name of first node is: " << pRootNode->name() << "\n";

  xml_node<>* pNode = pRootNode->first_node("chord");

  if(!pNode) {
    printf("Error: 'chord' node not found!\n");
    return -1;
  }

  print(std::cout, *pNode, 0);

  for (xml_attribute<>* pAttr = pNode->first_attribute(); pAttr; pAttr = pAttr->next_attribute()) {
    cout << "Node chord has attribute " << pAttr->name() << " ";
    cout << "with value " << pAttr->value() << "\n";
  }

  fclose(p);

  return 0;
}

