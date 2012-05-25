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
    
    
    
    
    PianoRequestDataLogin_t loginReq;
    
    loginReq.user = "andresruiz2010@gmail.com";
    loginReq.password = "passwordHere";
    loginReq.step = 0;
    
    PianoRequest_t req;
    
    memset(&req, 0, sizeof(req));
    
    std::cout << "HERE" << std::endl; 
    
    void *data = &loginReq;
    
    req.data = data;

    PianoReturn_t pRet;
    std::cout << "WELL THEN" << std::endl;
    
    pRet = PianoRequest(&ph, &req, PIANO_REQUEST_LOGIN);
        
    if(pRet == PIANO_RET_OK){
      std::cout << "Loged in!" << std::endl;
    }else{
      std::cout << "Loged in?" << std::endl;
    }
    
    WaitressReturn_t *wret;
    
    
    
    
    std::cout << "Goodbye!" << std::endl;
    
    
    return 0;
}
