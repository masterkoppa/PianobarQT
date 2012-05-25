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
