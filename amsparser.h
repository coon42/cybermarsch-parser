#include <string.h>
#include <list>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>

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
  bool openXml(const char* pXmlFileName);

  rapidxml::xml_document<> xml_;
  int tempo_{120};
  const int PPQN = 960;
};

