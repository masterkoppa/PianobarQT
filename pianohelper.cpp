#include "pianohelper.h"

char* PianoHelper::PianoJsonStrdup(json_object* json, const char* key)
{
  return strdup(json_object_get_string(json_object_object_get(json, key)));
}
