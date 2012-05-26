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
public:
    PandoraSong(PianoSong_t song);
};

#endif // PANDORASONG_H
