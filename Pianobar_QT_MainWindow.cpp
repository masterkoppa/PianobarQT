#include "Pianobar_QT_MainWindow.h"
#include <QListWidget>
#include "QPlaylist.h"

/**
 * Converts the time given in milliseconds to a qstring
 */
QString timeToString(long time_msecs)
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

Pianobar_QT_MainWindow::Pianobar_QT_MainWindow(QWidget* parent, Qt::WindowFlags flags): QMainWindow(parent, flags)
{
  //DO Nothing
}

Pianobar_QT_MainWindow::Pianobar_QT_MainWindow(QString username): QMainWindow()
{
  resize(500, 500);
  QString title ("");
  title.append("Pianobar QT: ");
  title.append(username);
  
  this->setWindowTitle(title);
  
   QWidget *centralWidget = new QWidget(this);
   
   QGridLayout* test = new QGridLayout(centralWidget);
   
   timeLabel = new QLabel("00:00:00:/00:00:00");
   
   test->addWidget(timeLabel, 0, 0);
   
   centralWidget->setLayout(test);
   setCentralWidget(centralWidget);
   
   
   stationsDock = new QStationsList();
   
   addDockWidget(Qt::LeftDockWidgetArea, stationsDock);
   
   playlistDock = new QPlaylist();
   
   
   addDockWidget(Qt::RightDockWidgetArea, playlistDock);
   
   
   media = new Phonon::MediaObject(this);
   media->setTickInterval(1000);
   Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
   connect(media, SIGNAL(tick(qint64)), SLOT(onEachTick()));
   connect(media, SIGNAL(finished()), SLOT(onEndOfSong()));
}


void Pianobar_QT_MainWindow::setHandlers(PianoHandle_t ph, WaitressHandle_t wh)
{
    this->ph = ph;
    this->wh = wh;
    
    piano.PianoGetStations(&ph, &wh);
    
    std::vector<PandoraStation> stations = helper.parseStations(ph.stations);
    
    stationsDock->setStations(stations);
    connect(stationsDock->stationList, SIGNAL(itemActivated(QListWidgetItem*)), SLOT(onNewStationSelect()));
}

void Pianobar_QT_MainWindow::onNewStationSelect()
{
  std::cout << "New Station" << std::endl;
  
  playlistDock->clearPlaylist();
  
  nextSong();
  
  
  
  std::cout << "Starting song" << std::endl;
  
}

void Pianobar_QT_MainWindow::getPlaylist()
{
  //Get the selected station from the dock
  PandoraStation* station = stationsDock->selectedStation;
  
  //For my own sanity, make sure it's actually something
  Q_ASSERT(station != NULL);
  
  //Make it into something pianobar can understand
  PianoStation_t tmpStation = station->toPianobarStation();
  
  //Get the linked list for this playlist
  PianoSong_t* song = piano.PianoGetPlaylist(&ph, &wh, &tmpStation);
  
  //If it's empty fill it
  if(playlist.empty()){
    playlistIndex = 0;
    playlist = helper.parsePlaylist(song);
  }else{
    //Since its not empty we will append to the end of the list
    std::vector<PandoraSong> tmp = helper.parsePlaylist(song);
    playlist.insert(playlist.end(), tmp.begin(), tmp.end());
  }
  for(std::vector<PandoraSong>::size_type i = playlistIndex; i != playlist.size(); i++){
    playlistDock->pushSong(playlist[i].toShortString());
  }
  
}

void Pianobar_QT_MainWindow::nextSong()
{
  if(playlistIndex-1 == playlist.size()){
    getPlaylist();//If we are about to finish, get a new one
  }
  
  if(playlist.empty()){
    getPlaylist();//Get the new playlist since we have none
    playlistIndex--;//Make sure we start at 0
  }
  
  playlistIndex++;
  
  playlistDock->setSongSelected(playlistIndex);
  
  QUrl link = QUrl::fromEncoded(playlist[playlistIndex].getAudioURL().toAscii());
  media->setCurrentSource(link);
  media->play();
  
  
}



void Pianobar_QT_MainWindow::onEachTick()
{
   
   qint64 mtime = media->currentTime();
   
   QString timeFormated = timeToString(mtime);
   
   QString timeTotal = timeToString(media->totalTime());
   
   QString retString = timeFormated;
   
   retString.append("/");
   retString.append(timeTotal);
      
   timeLabel->setText(retString);
}

void Pianobar_QT_MainWindow::onEndOfSong()
{
  if(media->errorType() == Phonon::FatalError){
    std::cout << "Phonon Fatal Error happened" << std::endl;
  }else if(media->errorType() == Phonon::NormalError){
    std::cout << "Phonon Normal Error, trying to continue" << std::endl;
  }
  //Call the next song when we are finished
  nextSong();
  
  std::cout << "Changing Song" << std::endl;
}



#include "Pianobar_QT_MainWindow.moc"