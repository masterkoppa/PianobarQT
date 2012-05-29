#ifndef PANDORASONG_H
#define PANDORASONG_H

#include "piano.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <QString>

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
    QString toString();
    
    /**
     * Returns the shorter string representation of this song in the following
     * format:
     * 
     * Artist - Title
     */
    QString toShortString();
    
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
     * Returns the audio url in a QString that is usable by the phonon
     * to grab.
     */
    QString getAudioURL();
    
    /**
     * Returns the url to the album art to be displayed for this song. This
     * is returned in a QString to simplify the program.
     */
    QString getAlbumArtURL();
};

#endif // PANDORASONG_H
