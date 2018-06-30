#include <stdio.h>
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>

extern "C" {
  #include <midifile.h>
}

using namespace rapidxml;
using namespace std;

int main() {
  const char* pFileName = "cybermarsch.xml";

  FILE* pXml = fopen(pFileName, "r");

  if(!pXml)
    printf("Error!\n");

  printf("Opened %s\n", pFileName);

  char pText[60000];

  fread(pText, 1, sizeof(pText), pXml);
  fclose(pXml);

  MidiFile midi;
  eMidi_create(&midi);

  xml_document<> doc;
  doc.parse<0>(pText);

  xml_node<>* pRootNode = doc.first_node();
  cout << "Name of first node is: " << pRootNode->name() << "\n";

  for(xml_node<>* pNode = pRootNode->first_node("chord"); pNode; pNode = pNode->next_sibling()) {
    print(std::cout, *pNode, 0);

    for (xml_attribute<>* pAttr = pNode->first_attribute(); pAttr; pAttr = pAttr->next_attribute()) {
      cout << "Node chord has attribute " << pAttr->name() << " ";
      cout << "with value " << pAttr->value() << "\n";
    }
  }

  eMidi_save(&midi, "cybermarsch.mid");
  eMidi_close(&midi);

  return 0;
}

