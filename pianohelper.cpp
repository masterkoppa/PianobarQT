#include "pianohelper.h"

PianoHelper::PianoHelper()
{
  //DO NOTHING
}


//Code from pianobar
char* PianoHelper::PianoJsonStrdup(json_object* json, const char* key)
{
  return strdup(json_object_get_string(json_object_object_get(json, key)));
}

/*
 * Helper method that parses the linked list of stations and puts them in a 
 * nice c++ class. This is for the GUI and for my own sanity.
 */
std::vector< PandoraStation > PianoHelper::parseStations(PianoStation_t stations)
{
  std::vector<PandoraStation> ret;
  
  while(&stations != NULL){
    PandoraStation station (stations);
    ret.push_back(station);
    //Weird way of iterrating, I know...
    if(stations.next == NULL){
      break;
    }else{
      stations = *stations.next;
    }
  }
  
  return ret;
}
