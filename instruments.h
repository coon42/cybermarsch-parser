#include <string.h>
#include <list>

extern "C" {
  #include <midifile.h>
}

//-------------------------------------------------------------------------------------------------------------
// Instrument
//-------------------------------------------------------------------------------------------------------------

class Instrument {
public:
  static int mssNote2midiNote(const char* pMssNote);

private:

};

class Cat : public Instrument {
public:

private:

};


class Dog {

};

class Boat {

};

class Heart {

};

class Toad {

};

class Gameboy {

};

class Flower {

};

class Star {

};

//-------------------------------------------------------------------------------------------------------------
// Channel
//-------------------------------------------------------------------------------------------------------------

class Channel {
public:

private:
};

//-------------------------------------------------------------------------------------------------------------
// Track
//-------------------------------------------------------------------------------------------------------------

class Track {
public:
  Track(const char* pXmlFileName);
  void save(const char* pFileName);

private:
  int tempo_{120};
  const int PPQN = 960;

  MidiFile midi;
};

