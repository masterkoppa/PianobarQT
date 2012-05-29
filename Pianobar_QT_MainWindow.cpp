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
   media->setTickInterval(2000);
   Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
   connect(media, SIGNAL(tick(qint64)), SLOT(onEachTick()));
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
  
  PandoraStation* station = stationsDock->selectedStation;
  
  PianoStation_t tmpStation = station->toPianobarStation();
    
  PianoSong_t* song = piano.PianoGetPlaylist(&ph, &wh, &tmpStation);
  std::vector<PandoraSong> tmp = helper.parsePlaylist(song);

  QUrl link = QUrl::fromEncoded(tmp[0].getAudioURL().toAscii());
  media->setCurrentSource(link);
  media->play();
  
  std::cout << "Starting song" << std::endl;
  
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


#include "Pianobar_QT_MainWindow.moc"