#include "instruments.h"

int main() {
  const char* pXmlFileName = "cybermarsch.xml";
  Track track(pXmlFileName);
  track.save("cybermarsch.mid");

  return 0;
}

