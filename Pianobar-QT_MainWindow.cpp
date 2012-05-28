#include "Pianobar-QT_MainWindow.h"

Pianobar_QT_MainWindow::Pianobar_QT_MainWindow(QWidget* parent): QWidget(parent)
{

}

void Pianobar_QT_MainWindow::setHandlers(PianoHandle_t* ph, WaitressHandle_t* wh)
{
  //Make sure that you are logged into the system
  Q_ASSERT(ph->user.listenerId != NULL);
  
  
      
    piano.PianoGetStations(ph, wh);
    
    
    std::vector<PandoraStation> stations = helper.parseStations(ph->stations);
    
    selectedStation = new PandoraStation(*ph->stations->next);
    
    getMoreSongs();
    
    media = new Phonon::MediaObject(this);
    Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));

    //Set the index to start at 0
    playIndex = 0;
    
    //Before we continue make sure that we have a playlist
    Q_ASSERT(playlist.size() > 0);
    
    //Queue up the first one
    QUrl link = QUrl::fromEncoded(playlist[0].getAudioURL().toAscii());
    media->setCurrentSource(link);
    media->play();
    
    
    media->setTickInterval(1000);
   
    //label = new QLabel("00:00:00/00:00:00", this);

   
   
    connect(media, SIGNAL(tick(qint64)), SLOT(onUpdate()));
    connect(media, SIGNAL(aboutToFinish()), SLOT(aboutToEnd()));
    connect(media, SIGNAL(finished()), SLOT(onStop()));
}

QString Pianobar_QT_MainWindow::timeToString(long time_msecs)
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

void Pianobar_QT_MainWindow::getMoreSongs()
{
  PianoStation_t station = selectedStation->toPianobarStation();
    
  PianoSong_t* song = piano.PianoGetPlaylist(&ph, &wh, &station);
  if(playlist.empty()){
    playlist = helper.parsePlaylist(song);
  }else{
    std::vector<PandoraSong> tmp = helper.parsePlaylist(song);
    playlist.insert(playlist.end(), tmp.begin(), tmp.end());
  }
  
  //Iterates through the playlist and prints it out
  std::cout << "Playlist: " << std::endl;
  for(std::vector<PandoraSong>::size_type i = 0; i != playlist.size(); i++){
    QString song = playlist[i].toString();
    std::cout << song.toStdString() << std::endl;
  }
}

void Pianobar_QT_MainWindow::onUpdate()
{
   
   qint64 mtime = media->currentTime();
   
   QString timeFormated = timeToString(mtime);
   
   QString timeTotal = timeToString(media->totalTime());
   
   QString retString = timeFormated;
   
   retString.append("/");
   retString.append(timeTotal);
   
   //label->setText(retString);
}

void Pianobar_QT_MainWindow::aboutToEnd()
{
   if(playIndex < playlist.size()){
     playIndex++;
     if(playIndex == playlist.size()){
      std::cout << "Seems like we are finished here, lets get the next one" << std::endl;
      
      getMoreSongs();
     }
     QUrl link = QUrl::fromEncoded(playlist[playIndex].getAudioURL().toAscii());
     media->setCurrentSource(Phonon::MediaSource(link));
     media->play();
     std::cout << "Playing: " << playlist[playIndex].getTitle() << std::endl;
   }else{
    std::cout << "End of playlist" << std::endl;
   }
   
}

void Pianobar_QT_MainWindow::onStop()
{
  std::cout << "End of playlist, done" << std::endl;
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
#include "Pianobar-QT_MainWindow.moc"