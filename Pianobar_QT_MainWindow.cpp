#include "Pianobar_QT_MainWindow.h"


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
   
   QLabel* label = new QLabel("TEST");
   
   test->addWidget(label, 0, 0);
   
   centralWidget->setLayout(test);
   setCentralWidget(centralWidget);
   
   stationsDock = new QStationsList();
   
   addDockWidget(Qt::LeftDockWidgetArea, stationsDock);
  
}


void Pianobar_QT_MainWindow::setHandlers(PianoHandle_t ph, WaitressHandle_t wh)
{
    piano.PianoGetStations(&ph, &wh);
    
    std::vector<PandoraStation> stations = helper.parseStations(ph.stations);
    
    stationsDock->setStations(stations);
    
    PandoraStation* station = new PandoraStation(*ph.stations->next);
    
    PianoStation_t tmpStation = station->toPianobarStation();
    
    PianoSong_t* song = piano.PianoGetPlaylist(&ph, &wh, &tmpStation);
    std::vector<PandoraSong> tmp = helper.parsePlaylist(song);
    
    media = new Phonon::MediaObject(this);
    Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    
    QUrl link = QUrl::fromEncoded(tmp[0].getAudioURL().toAscii());
    media->setCurrentSource(link);
    media->play();
}


#include "Pianobar_QT_MainWindow.moc"