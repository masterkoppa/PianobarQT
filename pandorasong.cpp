#include "pandorasong.h"

PandoraSong::PandoraSong(PianoSong_t song)
{
  artist = song.artist;
  stationId = song.stationId;
  album = song.album;
  audioUrl = song.audioUrl;
  coverArt = song.coverArt;
  musicId = song.musicId;
  title = song.title;
  seedId = song.seedId;
  feedbackId = song.feedbackId;
  detailUrl = song.detailUrl;
  trackToken = song.trackToken;
  fileGain = song.fileGain;
  rating = song.rating;
  format = song.audioFormat;
}

char* PandoraSong::getAlbum()
{
  return album;
}

char* PandoraSong::getArtist()
{
  return artist;
}

char* PandoraSong::getTitle()
{
  return title;
}

char* PandoraSong::toString()
{
  
  char* ret;
  //Alocate enough memory for the whole string, plus some extra in case of 
  //problems
  ret = (char* )malloc(sizeof(title) + sizeof(artist) + sizeof(album) + 20);
  
  //Copy the original string
  strcpy(ret, artist);
  
  //Append these strings to the return
  strcat(ret, " - ");
  strcat(ret, title);
  strcat(ret, " - ");
  strcat(ret, album);
  
  return  ret;
}

char* PandoraSong::getAlbumArt()
{
  
  char* dest = generateAlbumPath();
  
  downloadSong(coverArt, dest);
  
  std::cout << "URL: " << coverArt << std::endl;
  
  return dest;
}

char* PandoraSong::getSong()
{
  char* dest = generateSongPath();
  
  std::cout << "URL: " <<  audioUrl << std::endl;
  
  downloadSong(audioUrl, dest);
  
  return dest;
}


void PandoraSong::downloadSong(char* url, char* destination)
{  
  std::ofstream ofs (destination);
  CURLcode returnCode = curl_read(url, ofs, 30);
  
  if(returnCode != CURLE_OK){
    std::cerr << "Error getting song: " << url << " to " << destination << std::endl;
  }
}


//Code from: http://www.cplusplus.com/forum/unices/45878/
CURLcode PandoraSong::curl_read(char* url, std::ostream& os, long int timeout)
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
    && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url)))
    {
      code = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
  }
  
  return code;
}

//Code from: http://www.cplusplus.com/forum/unices/45878/
size_t PandoraSong::data_write(void* buf, size_t size, size_t nmemb, void* userp)
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

char* PandoraSong::generateAlbumPath()
{
  char* dest = (char*) malloc(sizeof("/tmp/") + sizeof(album)*100);
  
  strcpy(dest, "/tmp/");
  strcat(dest, album);
  strcat(dest, ".jpg");//Append file format
  
  return dest;
}

char* PandoraSong::generateSongPath()
{
  
  char* dest = (char*)malloc(sizeof(title) * 1000);
  //std::string dest;
  
  //dest += "/tmp/";
  //dest += title;
  //dest += ".mp4";
  
  strcpy(dest, "/tmp/");
  strcat(dest, title);
  //FIXME TEMP SOLUTION
  strcat(dest, ".mp4");
  
//   switch(format){
//     case PIANO_AF_UNKNOWN:
//       std::cerr << "Unknown file format for song" << std::endl;
//       break;
//     case PIANO_AF_AACPLUS:
//     case PIANO_AF_AACPLUS_LO:
//       strcat(dest, ".mp4");
//       break;
//     case PIANO_AF_MP3:
//     case PIANO_AF_MP3_HI:
//       strcat(dest, ".mp3");
//       break;
//   }
  
  return dest;
}



