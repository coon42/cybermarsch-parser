#include <stdio.h>
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>

extern "C" {
  #include <midifile.h>
}

using namespace rapidxml;
using namespace std;

static int mssNote2midiNote(const char* pMssNote) {
  int semiTone = 0;

  if (pMssNote[0] == '-') {
    semiTone = 1;
    pMssNote++;
  }
  else if (pMssNote[0] == '+') {
    semiTone = -1;
    pMssNote++;
  }

  auto char2Note = [](char charNote) -> int {
    switch(charNote) {
      case 'A': return 69; // A4 (440 Hz)
      case 'B': return 71; // B4
      case 'C': return 72; // C5
      case 'D': return 74; // D5
      case 'E': return 76; // E5
      case 'F': return 77; // F5
      case 'G': return 79; // G5
      case 'H': return 81; // A5
      case 'a': return 83; // B5
      case 'b': return 84; // C6
      case 'c': return 86; // D6
      case 'd': return 88; // E6
      case 'e': return 89; // F6
      case 'f': return 91; // G6
      case 'g': return 93; // A6
      case 'h': return 95; // B6
      case 'i': return 96; // C7
    }

    return 0;
  };

  return char2Note(pMssNote[0]) + semiTone;
}

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

  for (xml_attribute<>* pAttr = pRootNode->first_attribute(); pAttr; pAttr = pAttr->next_attribute()) {
    cout << "Root node has attribute '" << pAttr->name() << "' ";
    cout << "with value '" << pAttr->value() << "'\n";
  }

  // TODO: set tempo here!

  for(xml_node<>* pChordNode = pRootNode->first_node("chord"); pChordNode; pChordNode = pChordNode->next_sibling()) {
    for(xml_node<>* pNoteNode = pChordNode->first_node(); pNoteNode; pNoteNode = pNoteNode->next_sibling()) {
      // print(std::cout, *pNode, 0);
    
      printf("%s: %s\n", pNoteNode->name(), pNoteNode->value());
    }
  }

  eMidi_save(&midi, "cybermarsch.mid");
  eMidi_close(&midi);

  return 0;
}

