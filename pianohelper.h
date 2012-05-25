#ifndef PIANOHELPER_H

//Include the pianobar libraries
extern "C" {
#include "piano.h"
#include <json/json_object.h>
#include "waitress.h"
}

#define PIANOHELPER_H
#define TLS_FINGERPRINT "\xA2\xA0\xBE\x8A\x37\x92\x39\xAE\x2B\x2E\x71\x4C\x56\xB3\x8B\xC1\x2A\x9B\x4B\x77"

class PianoHelper
{
public:
  char *PianoJsonStrdup(json_object *json, const char* key);
};

#endif // PIANOHELPER_H
