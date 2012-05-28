#include <QCoreApplication>
#include "Pianobar-QT.h"
#include "pianosteps.h"
#include "pandorastation.h"
#include "pianohelper.h"

extern "C" {
#include "piano.h"
#include "waitress.h"
}

int main(int argc, char** argv)
{    
//     QApplication app(argc, argv);
//     Pianobar_QT mw;
//     mw.resize(300, 300);
//     mw.show();
//     return app.exec();

    PianoHandle_t ph;
    
    WaitressHandle_t wh;
    
    PianoSteps piano;
    
    piano.PianoInitialize(&ph, &wh);
    
    std::cout << "Calling Login" << std::endl;
    
    piano.PianoLogin(&ph, &wh);
    
    std::cout << "Getting Stations" << std::endl;
    
    piano.PianoGetStations(&ph, &wh);
    
    PianoHelper helper;
    
    std::vector<PandoraStation> stations = helper.parseStations(ph.stations);
    
    std::cout << stations.size() << std::endl;
    
    PianoSong_t* song = piano.PianoGetPlaylist(&ph, &wh, ph.stations->next);
    
    
    std::vector<PandoraSong> playlist = helper.parsePlaylist(song);
    
    std::cout << "Playlist Size: " << playlist.size() << std::endl;
    
    //Iterates through the playlist and prints it out
    std::cout << "Playlist: " << std::endl;
    for(std::vector<PandoraSong>::size_type i = 0; i != playlist.size(); i++){
      QString song = playlist[i].toString();
      std::cout << song.toStdString() << std::endl;
    }
    
    std::cout << "Goodbye!" << std::endl;
    
    
    QApplication app(argc, argv);
    QApplication::setApplicationName("Phonon Tutorial 2");
    Pianobar_QT mw (playlist[0].getAudioURL());
    mw.resize(300, 300);
    mw.show();
    return app.exec();
    return 0;
}
