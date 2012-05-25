#ifndef PIANOHELPER_H

//Include the pianobar libraries
extern "C" {
#include "piano.h"
#include <json/json_object.h>
#include "waitress.h"
}

#define PIANOHELPER_H
#define TLS_FINGERPRINT "\242\240\276\212\067\222\071\256+.qLV\263\213\301*\233Kw?+-acdeghijmnpqrstux$b()="

class PianoHelper
{
public:
  char *PianoJsonStrdup(json_object *json, const char* key);
};

#endif // PIANOHELPER_H
