#include "pianosteps.h"

PianoSteps::PianoSteps()
{
  //NOTHING
  std::cout << "Built" << std::endl;
}

void PianoSteps::PianoInitialize(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle)
{
  
  //Constants for Piano Init
  char *user = "android";
  char *password = "AC7IBG09A3DTSYM4R41UJWL07VLN8JI7";
  char *device = "android-generic";
  char *in = "R=U!LH$O2B#";
  char *out = "6#26FRL$ZWD";
  
  //Initialize PianoHandle
  PianoInit(pianoHandle, user, password, device, in, out);
  
  
  //Constants for WaitressHandle
  
  WaitressInit(waitressHandle);
  waitressHandle->url.host = PIANO_RPC_HOST;
    
  waitressHandle->tlsFingerprint = (const char*)malloc(strlen(TLS_FINGERPRINT));
  memcpy((void*)waitressHandle->tlsFingerprint, (void*)TLS_FINGERPRINT, strlen(TLS_FINGERPRINT));
}

//TODO: Allow for dynamic username and passwords
void PianoSteps::PianoLogin(PianoHandle_t* pianoHandle)
{
  PianoReturn_t pianoRet;
  WaitressReturn_t waitRet;
  
  
  //IDEA: Build this object inside the GUI and pass it built
  PianoRequestDataLogin_t loginReq;
    
  loginReq.user = "andresruiz2010@gmail.com";
  loginReq.password = "passwordHere";
  loginReq.step = 0;
  
  
  //ui.c:160
  PianoRequest_t request;
  
  memset(&request, 0, sizeof(request));
  
  request.data = (void *)&loginReq;
  
  pianoRet = PianoRequest (pianoHandle, &request, PIANO_REQUEST_LOGIN);
  
  if(pianoRet != PIANO_RET_OK){
    std::cerr << "Problem Encountered, piano returned not ok" << std::endl;
  }else{
    std::cout << "Piano Returned OK, moving on" << std::endl;
  }
  
  
  
}

