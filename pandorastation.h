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
  char isQuickMix;
  char useQuickMix;
  
public:
  /**
   * Generates a PandoraStation object based on the struct pass on.
   * This is mostly for representation purposes.
   */
  PandoraStation(PianoStation_t station);
  /**
   * Returns a PianoStation Structure that represents the Pandora Station,
   * this is the original object minus the linked list part of it.
   * 
   * You must keep track of all the stations from pandora.
   */
  PianoStation_t toPianobarStation();
  /**
   * Returns a string representation of this station, basically the name of
   * the station.
   */
  char* toString();
};

#endif // PANDORASTATION_H
