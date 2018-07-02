#include <stdio.h>
#include <string.h>
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <list>

extern "C" {
  #include <midifile.h>
}

using namespace rapidxml;
using namespace std;

static int mssNote2midiNote(const char* pMssNote) {
  int semiTone = 0;

  if (pMssNote[0] == '+') {
    semiTone = 1;
    pMssNote++;
  }
  else if (pMssNote[0] == '-') {
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

  if (!pXml)
    printf("Error!\n");

  printf("Opened %s\n", pFileName);

  char pText[60000];

  fread(pText, 1, sizeof(pText), pXml);
  fclose(pXml);

  MidiFile midi;
  eMidi_create(&midi);
  eMidi_writeProgramChangeEvent(&midi, 0, 0, 0); // cat
  eMidi_writeProgramChangeEvent(&midi, 0, 1, 0); // dog
  eMidi_writeProgramChangeEvent(&midi, 0, 2, 0); // boat
  eMidi_writeProgramChangeEvent(&midi, 0, 3, 0); // heart
  eMidi_writeProgramChangeEvent(&midi, 0, 4, 0); // toad
  eMidi_writeProgramChangeEvent(&midi, 0, 5, 0); // gameboy
  eMidi_writeProgramChangeEvent(&midi, 0, 6, 0); // flower
  eMidi_writeProgramChangeEvent(&midi, 0, 7, 0); // star

  xml_document<> doc;
  doc.parse<0>(pText);

  const xml_node<>* pRootNode = doc.first_node();
  cout << "Name of first node is: " << pRootNode->name() << "\n";

  for (const xml_attribute<>* pAttr = pRootNode->first_attribute(); pAttr; pAttr = pAttr->next_attribute()) {
    cout << "Root node has attribute '" << pAttr->name() << "' ";
    cout << "with value '" << pAttr->value() << "'\n";

    if (strcmp(pAttr->name(), "tempo") == 0)
      eMidi_writeSetTempoMetaEvent(&midi, 0, atoi(pAttr->value()));
  }

  const int PPQN = 960;

  for (const xml_node<>* pChordNode = pRootNode->first_node("chord"); pChordNode; pChordNode = pChordNode->next_sibling()) {
    bool firstEventOfChord = true;

    struct NoteOffEvent {
      int channel;
      int note;
    };

    list<NoteOffEvent> noteOffEvents;

    for (const xml_node<>* pNoteNode = pChordNode->first_node(); pNoteNode; pNoteNode = pNoteNode->next_sibling()) {
      for (const char* p = pNoteNode->value(); *p;) {
        char pMssNote[3];
        int numDigits = (*p == '+' || *p == '-') ? 2 : 1;

        memcpy(pMssNote, p, numDigits);
        pMssNote[numDigits] = '\0';

        uint8_t note = mssNote2midiNote(pMssNote);

        printf("%s: %s -> Midi Note: %d\n", pNoteNode->name(), pMssNote, note);

        auto putNote = [&](int channel) -> void {
          uint32_t deltaTime = firstEventOfChord ? PPQN : 0;
          eMidi_writeNoteOnEvent(&midi, 0, channel, note, 127);

          NoteOffEvent e;
          e.channel = channel;
          e.note = note;
          noteOffEvents.push_back(e);

          firstEventOfChord = false;
        };

        if (strcmp(pNoteNode->name(), "cat") == 0)
          putNote(0);

// The notes can not be enabled at the same time since the note off events shifts the other notes.
// TODO: use absolute tick scale

        if(strcmp(pNoteNode->name(), "dog") == 0)
          putNote(1);

        if(strcmp(pNoteNode->name(), "boat") == 0)
          putNote(2);

        if(strcmp(pNoteNode->name(), "heart") == 0)
          putNote(3);

        if(strcmp(pNoteNode->name(), "toad") == 0)
          putNote(4);

        if(strcmp(pNoteNode->name(), "gameboy") == 0)
          putNote(5);

        if(strcmp(pNoteNode->name(), "flower") == 0)
          putNote(6);

        if(strcmp(pNoteNode->name(), "star") == 0)
          putNote(7);

        p += numDigits;
      }
    }

    for(int i = 0; noteOffEvents.size(); ++i) {
      NoteOffEvent noe = noteOffEvents.back();
      noteOffEvents.pop_back();

      int deltaTime = i == 0 ? PPQN : 0;
      eMidi_writeNoteOffEvent(&midi, deltaTime, noe.channel, noe.note, 127);
    }

    printf("\n");

    // TODO: This is a hack to keep correct timings on empty chord nodes. Instead, the delta ticks of the previous events should
    //       have correct values (start value + duration of empty nodes), to avoid this hack:

    if (firstEventOfChord)
      eMidi_writeControlChangeEvent(&midi, PPQN, 0, 7, 127);
  }

  eMidi_writeEndOfTrackMetaEvent(&midi, 0);

  eMidi_save(&midi, "cybermarsch.mid");
  eMidi_close(&midi);

  return 0;
}

