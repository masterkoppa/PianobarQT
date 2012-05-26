#ifndef PIANOHELPER_H
#define PIANOHELPER_H
//Include the pianobar libraries
extern "C" {
#include "piano.h"
#include <json/json_object.h>
#include "waitress.h"
}
#include "pandorastation.h"
#include <vector>


#define TLS_FINGERPRINT "\242\240\276\212\067\222\071\256+.qLV\263\213\301*\233Kw?+-acdeghijmnpqrstux$b()="

class PianoHelper
{
public:
  PianoHelper();
  char *PianoJsonStrdup(json_object *json, const char* key);
  PandoraStation getStations();
  
  /**
  * Helper method that parses the linked list of stations and puts them in a 
  * nice c++ class. This is for the GUI and for my own sanity.
  * @param stations PianoStation representation from libpianobar, this must
  * be the head of the list for the program to work correctly.
  */
  std::vector<PandoraStation> parseStations(PianoStation_t stations);
};

#endif // PIANOHELPER_H
