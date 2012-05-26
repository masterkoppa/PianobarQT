#ifndef PANDORASTATION_H
#define PANDORASTATION_H

extern "C" {
#include "piano.h"
}


class PandoraStation
{
  char *name;
  char *id;
  char *seedId;
  char isCreator;
  char isQuckMix;
  char useQuickmix;
  
public:
  PandoraStation(PianoStation_t station);
  PianoStation_t toPianobarStation();
  char* toString();
};

#endif // PANDORASTATION_H
