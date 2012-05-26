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
//     QApplication::setApplicationName("Phonon Tutorial 2");
//     Pianobar_QT mw;
//     mw.show();
//     return app.exec();

    curl_global_init(CURL_GLOBAL_ALL);
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
      std::cout << playlist[i].toString() << std::endl;
      //std::cout << playlist[i].getAlbumArt() << std::endl;
      sleep(10);
      std::cout << playlist[i].getSong() << std::endl;
    }
    
    std::cout << "Goodbye!" << std::endl;
    
    curl_global_cleanup();
    
    return 0;
}
