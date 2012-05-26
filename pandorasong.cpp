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

