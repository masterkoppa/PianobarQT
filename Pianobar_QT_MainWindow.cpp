#include "Pianobar_QT_MainWindow.h"



/**
* Converts the time given in milliseconds to a qstring
*/
inline QString timeToString (long time_msecs)
{
    long stime = time_msecs / 1000;

    int hours = stime / 600;
    int minutes = (stime / 60) % 60;
    int seconds = stime % 60;
    QString retString ("");
    //TODO: If deemed necessary, append a 0 if hours is less than 10.
    if (hours != 0) {
        retString = QString::number (hours);
        retString.append (":");
    }

    if (minutes < 10) {
        retString.append ("0");
    }
    retString.append (QString::number (minutes));
    retString.append (":");
    if (seconds < 10) {
        retString.append ("0");
    }
    retString.append (QString::number (seconds));

    return retString;
}

inline QPushButton* createButton (QString name, QString iconName)
{
    QPushButton* ret = new QPushButton (QIcon::fromTheme (iconName), 0);
    ret->setToolTip (name);

    return ret;
}

Pianobar_QT_MainWindow::Pianobar_QT_MainWindow (QWidget* parent, Qt::WindowFlags flags) : QMainWindow (parent, flags)
{
    //DO Nothing
}

Pianobar_QT_MainWindow::Pianobar_QT_MainWindow (QString username) : QMainWindow()
{
    resize (800, 800);
    QString title ("");
    title.append ("Pianobar QT: ");
    title.append (username);

    this->setWindowTitle (title);

    QWidget* centralWidget = new QWidget (this);

    QGridLayout* test = new QGridLayout (centralWidget);



    QVBoxLayout* infoLayout = new QVBoxLayout();
    
    this->buildLabels();
    
    infoLayout->addWidget (songName);
    infoLayout->addWidget (artist);
    infoLayout->addWidget (album);


    QHBoxLayout* buttonLayout = new QHBoxLayout();

    prev = createButton ("Previous Song", "media-skip-backward");

    playPause = createButton ("Play/Pause", "media-playback-start");

    next = createButton ("Next Song", "media-skip-forward");

    loveSong = createButton ("Neutral", "face-smile");

    buttonLayout->addWidget (prev);
    buttonLayout->addWidget (playPause);
    buttonLayout->addWidget (next);

    test->addWidget (loveSong, 0, 0, Qt::AlignCenter);
    test->addWidget (albumArt, 1, 0, Qt::AlignCenter);
    test->addLayout (infoLayout, 2, 0, Qt::AlignCenter);
    test->addLayout (buttonLayout, 3, 0, Qt::AlignCenter);
    test->addWidget (timeLabel, 4, 0, Qt::AlignCenter);


    centralWidget->setLayout (test);
    setCentralWidget (centralWidget);


    stationsDock = new QStationsList();

    addDockWidget (Qt::LeftDockWidgetArea, stationsDock);

    playlistDock = new QPlaylist();


    addDockWidget (Qt::RightDockWidgetArea, playlistDock);


    media = new Phonon::MediaObject (this);
    media->setTickInterval (1000);
    Phonon::createPath (media, new Phonon::AudioOutput (Phonon::MusicCategory, this));

    Phonon::SeekSlider* seeker = new Phonon::SeekSlider (media, this);
    seeker->setIconVisible (false);
    seeker->setMinimumWidth (300);

    test->addWidget (seeker, 5, 0, Qt::AlignCenter);

    connect (media, SIGNAL (tick (qint64)), SLOT (onEachTick()));
    connect (media, SIGNAL (finished()), SLOT (onEndOfSong()));
    connect (media, SIGNAL (stateChanged (Phonon::State, Phonon::State)), SLOT (updateOnMediaStateChange()));
    connect (playPause, SIGNAL (clicked (bool)), SLOT (playPauseToggle()));
    connect (next, SIGNAL (clicked (bool)), SLOT (onNextSongSelect()));
    connect (prev, SIGNAL (clicked (bool)), SLOT (onPrevSongSelect()));

    //Since they're no functions you can do on start, disable the buttons
    disableButtons();
}

void Pianobar_QT_MainWindow::buildLabels()
{
    //Set the time label to show something
    timeLabel = new QLabel ("00:00:00:/00:00:00");

    //Album art label
    albumArt = new QLabel ("Album Art");

    //Set somthing as a default
    QIcon defaultIcon = QIcon::fromTheme ("audio-ac3");
    albumArt->setAlignment (Qt::AlignCenter);
    albumArt->setScaledContents (true);
    albumArt->setPixmap (defaultIcon.pixmap (500, 500));
    
    albumArt->setMinimumSize (400, 400);
    albumArt->setMaximumSize (400, 400);
    
    //Song Information Labels
    songName = new QLabel ("Title: ");
    artist = new QLabel ("Artist: ");
    album = new QLabel ("Album: ");
    
    songName->setMaximumWidth(400);
    artist->setMaximumWidth(400);
    album->setMinimumWidth(400);
}



void Pianobar_QT_MainWindow::setHandlers (PianoHandle_t ph, WaitressHandle_t wh)
{
    this->ph = ph;
    this->wh = wh;

    piano.PianoGetStations (&ph, &wh);

    std::vector<PandoraStation> stations = helper.parseStations (ph.stations);

    stationsDock->setStations (stations);
    connect (stationsDock->stationList, SIGNAL (itemActivated (QListWidgetItem*)), SLOT (onNewStationSelect()));
}

void Pianobar_QT_MainWindow::onNewStationSelect()
{
    qDebug() << "New Station";

    playlistDock->clearPlaylist();

    //If there is something there already
    if (!playlist.empty()) {
        playlist.clear();
    }

    playlistIndex = 0;
    nextSong();

    qDebug() << "Starting song";

}

void Pianobar_QT_MainWindow::getPlaylist()
{
    //Get the selected station from the dock
    PandoraStation* station = stationsDock->selectedStation;

    //For my own sanity, make sure it's actually something
    Q_ASSERT (station != NULL);

    //Make it into something pianobar can understand
    PianoStation_t tmpStation = station->toPianobarStation();

    //Get the linked list for this playlist
    PianoSong_t* song = piano.PianoGetPlaylist (&ph, &wh, &tmpStation);

    //Make sure that the song is valid, otherwise errors will happen.
    Q_ASSERT (song != NULL);

    //If it's empty fill it
    if (playlist.empty()) {
        playlistIndex = 0;
        qDebug() << "Filling playlist";
        playlist = helper.parsePlaylist (song);

        //Pushes the song to the playlist dock
        for (std::vector<PandoraSong>::size_type i = playlistIndex; i != playlist.size(); i++) {
            playlistDock->pushSong (playlist[i].toShortString());
        }

    } else {
        //Since its not empty we will append to the end of the list
        qDebug() << "Re-filling playlist";
        std::vector<PandoraSong> tmp = helper.parsePlaylist (song);
        playlist.insert (playlist.end(), tmp.begin(), tmp.end());
        tmp.clear();

        //Pushes the NEW songs to the playlist dock
        for (std::vector<PandoraSong>::size_type i = playlistIndex + 2; i != playlist.size(); i++) {
            playlistDock->pushSong (playlist[i].toShortString());
        }
    }


}

void Pianobar_QT_MainWindow::nextSong()
{
    if (playlistIndex + 2 == playlist.size()) {
        getPlaylist();//If we are about to finish, get a new one
    }

    qDebug() << playlistIndex << " " << playlist.size();

    if (playlist.empty()) {
        getPlaylist();//Get the new playlist since we have none
        playlistIndex--;//Make sure we start at 0
    }

    playlistIndex++;

    playSong();
}

void Pianobar_QT_MainWindow::prevSong()
{
    if (playlistIndex == 0) {
        playSong();
    } else {
        playlistIndex--;
        playSong();
    }
}

void Pianobar_QT_MainWindow::playSong()
{
    playlistDock->setSongSelected (playlistIndex);

    QString url = playlist[playlistIndex].getAudioURL();

    QUrl link = QUrl::fromEncoded (url.toAscii());
    media->clear();
    media->setCurrentSource (link);
    media->play();

    //Set the album art

    QString albumArtUrl = playlist[playlistIndex].getAlbumArtURL();

    QUrl albumArtLink = QUrl::fromEncoded (albumArtUrl.toAscii());

    imageBuffer = new QBuffer (&imageData);

    http = new QHttp (this);
    http->setHost (albumArtLink.host());

    qDebug() << "Album Art URL:" << albumArtUrl;

    request = http->get (albumArtLink.path(), imageBuffer);

    //Connect the http request to a response handler
    connect (http, SIGNAL (requestFinished (int, bool)), SLOT (albumDownloaded (int, bool)));

    //Set the song info
    QString songNameText ("Title: ");
    songNameText.append (QString (playlist[playlistIndex].getTitle()));

    QString albumText ("Album: ");
    albumText.append (QString (playlist[playlistIndex].getAlbum()));

    QString artistText ("Artist: ");
    artistText.append (QString (playlist[playlistIndex].getArtist()));

    //Song Information
    songName->setText (songNameText);
    album->setText (albumText);
    artist->setText (artistText);

    //Song rating
    if (playlist[playlistIndex].isSongNeutral()) {
        loveSong->setIcon (QIcon::fromTheme ("face-smile"));
        loveSong->setToolTip ("Neutral");
    } else if (playlist[playlistIndex].isSongBanned()) {
        loveSong->setIcon (QIcon::fromTheme ("face-uncertain"));
        loveSong->setToolTip ("Banned");
    } else if (playlist[playlistIndex].isSongLoved()) {
        loveSong->setIcon (QIcon::fromTheme ("face-smile-big"));
        loveSong->setToolTip ("Loved");
    }
}




void Pianobar_QT_MainWindow::onEachTick()
{

    qint64 mtime = media->currentTime();

    QString timeFormated = timeToString (mtime);

    QString timeTotal = timeToString (media->totalTime());

    QString retString = timeFormated;

    retString.append ("/");
    retString.append (timeTotal);

    timeLabel->setText (retString);
}

void Pianobar_QT_MainWindow::onEndOfSong()
{
    if (media->errorType() == Phonon::FatalError) {
        qDebug() << "Phonon Fatal Error happened";
    } else if (media->errorType() == Phonon::NormalError) {
        qDebug() << "Phonon Normal Error, trying to continue";
    }
    //Call the next song when we are finished
    nextSong();

    qDebug() << "Changing Song";
}

void Pianobar_QT_MainWindow::albumDownloaded (int id, bool err)
{

    if (request == id) {
        if (err) {
            qDebug() << "Error downloading Album Art";
            QIcon defaultIcon = QIcon::fromTheme ("audio-ac3");
            albumArt->setPixmap (defaultIcon.pixmap (500, 500));
            return;
        } else {
            qDebug() << "Downloaded Image";
        }
        qDebug() << "Found my request";

        QImage image = QImage::fromData (imageData);

        albumArt->setPixmap (QPixmap::fromImage (image));

        //Sanity check
        Q_ASSERT (albumArt->pixmap() != 0);


    }
}

void Pianobar_QT_MainWindow::playPauseToggle()
{
    if (media->state() == Phonon::PlayingState) {
        media->pause();
    } else if (media->state() == Phonon::PausedState) {
        media->play();
    } else {
        qDebug() << "Invalid Phonon State";
    }
}

void Pianobar_QT_MainWindow::disableButtons()
{
    prev->setEnabled (false);
    playPause->setEnabled (false);
    next->setEnabled (false);
}

void Pianobar_QT_MainWindow::enableButtons()
{
    prev->setEnabled (true);
    playPause->setEnabled (true);
    next->setEnabled (true);
}

void Pianobar_QT_MainWindow::updateOnMediaStateChange()
{
    if (media->state() == Phonon::PlayingState) {
        playPause->setIcon (QIcon::fromTheme (PauseIconName));
        enableButtons();
    } else if (media->state() == Phonon::PausedState) {
        playPause->setIcon (QIcon::fromTheme (PlayIconName));
        enableButtons();
    } else if (media->state() == Phonon::BufferingState) {
        //Do Nothing
    } else if (media->state() == Phonon::ErrorState) {
        qDebug() << "Error occured";
        disableButtons();//Disable the buttons so that they stay that way if there's more problems
        playSong(); //Attempt to replay the current song
    } else {
        enableButtons();
    }
}

void Pianobar_QT_MainWindow::onNextSongSelect()
{
    qDebug() << "Next pressed";
    nextSong();
}

void Pianobar_QT_MainWindow::onPrevSongSelect()
{
    qDebug() << "Prev pressed";
    prevSong();
}






#include "Pianobar_QT_MainWindow.moc"
