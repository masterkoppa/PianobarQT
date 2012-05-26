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


std::vector< PandoraStation > PianoHelper::parseStations(PianoStation_t* stations)
{
  std::vector<PandoraStation> ret;
  
  while(stations != NULL){
    PandoraStation station (*stations);
    ret.push_back(station);
    //Weird way of iterrating 
    stations = stations->next;
  }
  
  return ret;
}

std::vector< PandoraSong > PianoHelper::parsePlaylist(PianoSong_t* playlist)
{
  std::vector<PandoraSong> ret;
  
  while(playlist != NULL){
    PandoraSong song (*playlist);
    ret.push_back(song);
    playlist = playlist->next;
  }
  
  return ret;
}



