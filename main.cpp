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

    
    PianoHandle_t ph;
    
    WaitressHandle_t wh;
    
    PianoSteps piano;
    
    piano.PianoInitialize(&ph, &wh);
    
    
    std::cout << "Calling Login" << std::endl;
    
    piano.PianoLogin(&ph, &wh);
    
    std::cout << "Getting Stations" << std::endl;
    
    piano.PianoGetStations(&ph, &wh);    
    
    PianoHelper helper;
    
    std::vector<PandoraStation> stations = helper.parseStations(*ph.stations);
    
    std::cout << stations.size() << std::endl;
    
    
    std::cout << "Goodbye!" << std::endl;
    
    
    return 0;
}
