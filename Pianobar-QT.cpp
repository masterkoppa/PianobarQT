#include "Pianobar-QT.h"



Pianobar_QT::Pianobar_QT() : QWidget()
{
    PianoHandle_t ph;
    
    WaitressHandle_t wh;
    
    PianoSteps piano;
    
    piano.PianoInitialize(&ph, &wh);
    
    piano.PianoLogin(&ph, &wh);
    
    piano.PianoGetStations(&ph, &wh);
    
    PianoHelper helper;
    
    std::vector<PandoraStation> stations = helper.parseStations(ph.stations);
    
    PianoSong_t* song = piano.PianoGetPlaylist(&ph, &wh, ph.stations->next);
    
    playlist = helper.parsePlaylist(song);
    
    media = new Phonon::MediaObject(this);
    Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    
    //Iterates through the playlist and prints it out
    std::cout << "Playlist: " << std::endl;
    for(std::vector<PandoraSong>::size_type i = 0; i != playlist.size(); i++){
      QString song = playlist[i].toString();
      std::cout << song.toStdString() << std::endl;
      

      //media->enqueue(Phonon::MediaSource(link));
    }
    playIndex = 0;
    QUrl link = QUrl::fromEncoded(playlist[0].getAudioURL().toAscii());
    media->setCurrentSource(link);
    media->play();
    
    
    media->setTickInterval(1000);
   
    label = new QLabel("00:00:00/00:00:00", this);
   
   
    connect(media, SIGNAL(tick(qint64)), SLOT(onUpdate()));
    connect(media, SIGNAL(aboutToFinish()), SLOT(aboutToEnd()));
    connect(media, SIGNAL(finished()), SLOT(onStop()));
}

void Pianobar_QT::onUpdate()
{
   
   qint64 mtime = media->currentTime();
   
   QString timeFormated = timeToString(mtime);
   
   QString timeTotal = timeToString(media->totalTime());
   
   QString retString = timeFormated;
   
   retString.append("/");
   retString.append(timeTotal);
   //std::cout << media->queue().size() << std::endl;
   //std::cout << retString.toStdString() << std::endl;
   
   label->setText(retString);
   //label->setText();
}

void Pianobar_QT::aboutToEnd()
{
   std::cout << "About to end" << std::endl;
   if(playIndex < playlist.size()){
     std::cout << "Getting next song..." << std::endl;
     std::cout << media->queue().size() << std::endl;
     playIndex++;
     QUrl link = QUrl::fromEncoded(playlist[playIndex].getAudioURL().toAscii());
     media->setCurrentSource(Phonon::MediaSource(link));
     media->play();
     std::cout << media->state() << std::endl;
     std::cout << media->queue().size() << std::endl;
     std::cout << playlist[playIndex].getTitle() << std::endl;
   }else{
    std::cout << "End of playlist" << std::endl;
   }
}

void Pianobar_QT::onStop()
{
  std::cout << "End of playlist" << std::endl;
  if(media->queue().size() > 0){
    std::cout << "I shouldn't be stopping" << std::endl;
    media->play();
    
    switch(media->state()){
      case Phonon::ErrorState:
	std::cout << "Error State" << std::endl;
	break;
      case Phonon::PlayingState:
	std::cout << "Playing State" << std::endl;
	break;
      default:
	std::cout << "Other State" << std::endl;
	break;
    }
  }
}


QString Pianobar_QT::timeToString(long time_msecs)
{
  long stime = time_msecs/1000;
  
  int hours = stime / 600;
  int minutes = (stime / 60) % 60;
  int seconds = stime % 60;
  QString retString ("");
  //TODO: If deemed necessary, append a 0 if hours is less than 10.
  if(hours != 0){
    retString = QString::number(hours);
    retString.append(":");
  }
  
  if(minutes < 10){
    retString.append("0");
  }
  retString.append(QString::number(minutes));
  retString.append(":");
  if(seconds < 10){
    retString.append("0");
  }
  retString.append(QString::number(seconds));
  
  return retString;
}



#include "Pianobar-QT.moc"
