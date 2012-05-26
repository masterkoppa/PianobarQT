#include "pandorastation.h"

PandoraStation::PandoraStation(PianoStation_t station)
{
  name = station.name;
  id = station.id;
  seedId = station.seedId;
  //TODO Add the rest of the components
}

char* PandoraStation::toString()
{
  return name;
}

