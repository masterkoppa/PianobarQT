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
  
  songDownloaded = false;
  albumArtDownloaded = false;
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

QString PandoraSong::toShortString()
{
  QString retString ("");
  
  retString.append(artist);
  retString.append(" - ");
  retString.append(title);
  
  return retString;
}

QString PandoraSong::getAudioURL()
{
  QString* AudioUrl = new QString(this->audioUrl);
  
  return *AudioUrl;
}

QString PandoraSong::getAlbumArtURL()
{
  QString* AlbumArtURL = new QString(this->coverArt);
  
  return *AlbumArtURL;
}

bool PandoraSong::isSongBanned()
{
  return rating == PIANO_RATE_BAN;
}

bool PandoraSong::isSongLoved()
{
  return rating == PIANO_RATE_LOVE;
}

bool PandoraSong::isSongNeutral()
{
  return rating == PIANO_RATE_NONE;
}

PianoSong_t PandoraSong::toPianoSong()
{
  PianoSong_t song;
  
  song.artist = artist;
  song.stationId = stationId;
  song.album = album;
  song.audioUrl = audioUrl;
  song.coverArt = coverArt;
  song.musicId = musicId;
  song.title = title;
  song.seedId = seedId;
  song.feedbackId = feedbackId;
  song.detailUrl = detailUrl;
  song.trackToken = trackToken;
  song.fileGain = fileGain;
  song.rating = rating;
  song.audioFormat = format;
  
  return song;
}










