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

QString PandoraSong::toString()
{
  QString retString ("");
  
  retString.append(artist);
  retString.append(" - ");
  retString.append(title);
  retString.append(" - ");
  retString.append(album);
  
  return retString;
}

QString PandoraSong::getAudioURL()
{
  QString* AudioUrl = new QString(this->audioUrl);
  
  return *AudioUrl;
}






