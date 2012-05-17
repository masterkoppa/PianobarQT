#include <QCoreApplication>
#include "Pianobar-QT.h"

extern "C" {
#include "piano.h"
#include "waitress.h"
}

int main(int argc, char** argv)
{    
    char *user = "android";
    char *password = "AC7IBG09A3DTSYM4R41UJWL07VLN8JI7";
    char *device = "android-generic";
    char *in = "R=U!LH$O2B#";
    char *out = "6#26FRL$ZWD";
    
    PianoHandle ph;
    
    
    PianoInit(&ph, user, password, device, in, out);
    
    WaitressHandle_t wh;
    
    WaitressInit(&wh);
    
    
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
    
    
    
    std::cout << "Goodbye!" << std::endl;
    
    
    return 0;
}
