#ifndef PANDORASONG_H
#define PANDORASONG_H

#include <piano.h>

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
};

#endif // PANDORASONG_H
