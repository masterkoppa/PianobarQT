#include "pandorastation.h"

PandoraStation::PandoraStation(PianoStation_t station)
{
  name = station.name;
  id = station.id;
  seedId = station.seedId;
  isCreator = station.isCreator;
  isQuickMix = station.isQuickMix;
  useQuickMix = station.useQuickMix;
}

char* PandoraStation::toString()
{
  return name;
}

PianoStation_t PandoraStation::toPianobarStation()
{
  PianoStation_t station;
  
  station.name = name;
  station.id = id;
  station.seedId = seedId;
  station.isCreator = isCreator;
  station.isQuickMix = isQuickMix;
  station.useQuickMix = useQuickMix;
  
  return station;
}


