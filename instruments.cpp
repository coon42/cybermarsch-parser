#include "instruments.h"

int Instrument::mssNote2midiNote(const char* pMssNote) const {
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

