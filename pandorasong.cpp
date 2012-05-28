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

QString PandoraSong::getAudioURL()
{
  QString* AudioUrl = new QString(this->audioUrl);
  
  return *AudioUrl;
}






