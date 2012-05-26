#ifndef PANDORASONG_H
#define PANDORASONG_H

#include "piano.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <curl/curl.h>
#include <string>

class PandoraSong
{
private:
  char* artist;
  char* stationId;
  char* album;
  char* audioUrl;
  char* coverArt;
  char* musicId;
  char* title;
  char* seedId;
  char* feedbackId;
  char* detailUrl;
  char* trackToken;
  float fileGain;
  PianoSongRating_t rating;
  PianoAudioFormat_t format;
  bool songDownloaded = false;
  bool albumArtDownloaded = false;
public:
    PandoraSong(PianoSong_t song);
    /**
     * Returns the string representation of this song in the following
     * format:
     * 
     * Artist - Title - Album
     */
    char* toString();
    
    /**
     * Returns the song artist
     */
    char* getArtist();
    
    /**
     * Returns the song title
     */
    char* getTitle();
    
    /**
     * Returns the song album
     */
    char* getAlbum();
    
    /**
     * Downloads the album art into a temporary folder and returns it's
     * location.
     */
    char* getAlbumArt();
    
    /**
     * Downloads the song into a temporary folder and returns it's location.
     */
    char* getSong();
    
    /**
     * Clears all temporary files and frees up the memory by this object
     * TODO In the application make this optional.
     */
    void destroySong();
private:
  void downloadSong(char* url, char* destination);
  CURLcode curl_read(char* url, std::ostream& os, long int timeout);
  static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp);
  /**
   * Helper funtion that returns the path where the album art should be
   * stored or is currently stored in the case of deletion.
   */
  char* generateAlbumPath();
  
  /**
   * Helper function that returns the path where the song should be
   * stored or is currently stored in the case of deletion.
   */
    char* generateSongPath();
};

#endif // PANDORASONG_H
