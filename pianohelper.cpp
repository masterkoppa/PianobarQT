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


void PianoHelper::downloadSong(const std::string url, char* destination)
{
  std::ofstream ofs(destination);
  CURLcode returnCode = this->curl_read(url, ofs);
  
  if(returnCode != CURLE_OK){
    std::cerr << "Error getting song: " << url << " to " << destination << std::endl;
  }
}


//Code from: http://www.cplusplus.com/forum/unices/45878/
CURLcode PianoHelper::curl_read(const std::string& url, std::ostream& os, long int timeout)
{
  CURLcode code(CURLE_FAILED_INIT);
  CURL* curl = curl_easy_init();

  if(curl)
  {
    if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write))
    && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
    && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
    && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
    && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
    && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())))
    {
      code = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
  }
  return code;
}

//Code from: http://www.cplusplus.com/forum/unices/45878/
size_t PianoHelper::data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
  if(userp)
  {
    std::ostream& os = *static_cast<std::ostream*>(userp);
    std::streamsize len = size * nmemb;
    if(os.write(static_cast<char*>(buf), len))
      return len;
  }

  return 0;
}
