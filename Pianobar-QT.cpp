#include "Pianobar-QT.h"




Pianobar_QT::Pianobar_QT(QWidget* parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    
    QLabel* title = new QLabel("Welcome to PianobarQT", this);
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setUnderline(true);
    titleFont.setBold(true);
    
    title->setFont(titleFont);
    
    layout->addWidget(title, 0, 0, 1, 2);
    
    QLabel* userNameLabel = new QLabel("Username", this);
    
    layout->addWidget(userNameLabel, 1, 0);
    
    userName = new QLineEdit(this);
    
    layout->addWidget(userName, 1, 1);
    
    QLabel* passwordLabel = new QLabel("Password", this);
    
    layout->addWidget(passwordLabel, 2, 0);
    
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);
    
    layout->addWidget(passwordField, 2, 1);
    
    ok = new QPushButton("Ok", this);
    QPushButton* cancel = new QPushButton("Cancel", this);
    
    QHBoxLayout* hbox = new QHBoxLayout();
    
    hbox->addWidget(ok, 1, Qt::AlignRight);
    hbox->addWidget(cancel, 1, Qt::AlignRight);
    
    layout->addLayout(hbox, 3, 1);
    
    setLayout(layout);
    
    connect(cancel, SIGNAL(clicked(bool)), SLOT(cancelPressed()));
    connect(ok, SIGNAL(clicked(bool)), SLOT(logIn()));
    
}
void Pianobar_QT::logIn(){
    
    QString username = userName->text();
    QString password = passwordField->text();
    
    if(username.isEmpty() || password.isEmpty()){
       if(username.isEmpty()){
	userName->setStyleSheet("background: red");
       }else{
	userName->setStyleSheet("background: white");
       }
       if(password.isEmpty()){
	passwordField->setStyleSheet("background: red");
       }else{
	passwordField->setStyleSheet("background: white");
       }
       
      return;
    }
    
    std::cout << username.toStdString() << " " << password.toStdString() << std::endl;
    
    piano.PianoInitialize(&ph, &wh);
    
    //Copy the data to avoid overwriting... dam you memory
    char* user = strdup(username.toAscii().data());
    char* pass = strdup(password.toAscii().data());
    
    std::cout << user << " " << pass << std::endl;
    
    if(!piano.PianoLogin(&ph, &wh, user, pass)){
      return;
    }
    
    free(user);
    free(pass);
    
    piano.PianoGetStations(&ph, &wh);
    
    
    std::vector<PandoraStation> stations = helper.parseStations(ph.stations);
    
    selectedStation = new PandoraStation(*ph.stations->next);
    
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
    
    //Make sure that there are no double logins
    ok->disconnect(SIGNAL(clicked(bool)));
}

void Pianobar_QT::onUpdate()
{
   
   qint64 mtime = media->currentTime();
   
   QString timeFormated = timeToString(mtime);
   
   QString timeTotal = timeToString(media->totalTime());
   
   QString retString = timeFormated;
   
   retString.append("/");
   retString.append(timeTotal);
   
   //label->setText(retString);
}

void Pianobar_QT::aboutToEnd()
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

void Pianobar_QT::onStop()
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
void Pianobar_QT::getMoreSongs()
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

void Pianobar_QT::cancelPressed()
{
  //We are out of here
  exit(0);
}



#include "Pianobar-QT.moc"
