#include <QCoreApplication>
#include "Pianobar-QT.h"
#include "pianosteps.h"

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

    
    WaitressReturn_t *wret;
    
    
    
    
    std::cout << "Goodbye!" << std::endl;
    
    
    return 0;
}
