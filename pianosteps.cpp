#include "pianosteps.h"

PianoSteps::PianoSteps()
{
  //NOTHING
  std::cout << "Built" << std::endl;
}

void PianoSteps::PianoInitialize(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle)
{
  gnutls_global_init();
  
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
    
  waitressHandle->tlsFingerprint = TLS_FINGERPRINT;
}

//TODO: Allow for dynamic username and passwords
void PianoSteps::PianoLogin(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle)
{
  PianoReturn_t pianoRet;
  WaitressReturn_t waitRet;
  
  
  //IDEA: Build this object inside the GUI and pass it built
  PianoRequestDataLogin_t loginReq;
    
  loginReq.user = "ajr2546@rit.edu";
  loginReq.password = "passwordTest";
  loginReq.step = 0;
  
  
  //ui.c:160
  PianoRequest_t request;
  
  memset(&request, 0, sizeof(request));
  
  //This is in a loop because for logging into the system you need to go twice
  do{
    request.data = (void *)&loginReq;
    
    pianoRet = PianoRequest (pianoHandle, &request, PIANO_REQUEST_LOGIN);
    
    if(pianoRet != PIANO_RET_OK){
      std::cerr << "Problem Encountered, piano returned not ok" << std::endl;
    }else{
      std::cout << "Piano Returned OK, moving on" << std::endl;
    }
    
    waitRet = BarPianoHttpRequest(waitressHandle, &request);
    
    if(waitRet != WAITRESS_RET_OK){
      std::cerr << "Problem Encountered, waitress returned not ok" << std::endl;
    }else{
      std::cout << "Waitress Returned OK, moving on" << std::endl;
    }
    
    pianoRet = PianoResponse(pianoHandle, &request);
    
    if(pianoRet != PIANO_RET_CONTINUE_REQUEST){
      if(pianoRet == PIANO_RET_P_INVALID_AUTH_TOKEN){
	std::cout << "Invalid Auth Token" << std::endl;
      }else if(pianoRet == PIANO_RET_OK){
	std::cout << "Everything whent ok" << std::endl;
      }
    }
    
    if(request.responseData != NULL){
      free(request.responseData);
    }
    
    PianoDestroyRequest(&request);
  } while(pianoRet == PIANO_RET_CONTINUE_REQUEST);
  
  if(pianoRet == PIANO_RET_P_INVALID_PARTNER_LOGIN){
    std::cout << "Invalid user credentials" << std::endl;
  }else if(pianoRet == PIANO_RET_OK){
    std::cout << "Valid credentials" << std::endl;
  }
  
  
  
  std::cout << "Done with login" << std::endl;
}

void PianoSteps::PianoGetStations(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle)
{
  PianoReturn_t pianoRet;
  WaitressReturn_t waitRet;
  
  PianoRequest_t request;
  
  memset(&request, 0, sizeof(request));
  
  
  do{
    pianoRet = PianoRequest (pianoHandle, &request, PIANO_REQUEST_GET_STATIONS);
    
    if(pianoRet != PIANO_RET_OK){
      std::cerr << "Problem Encountered, piano returned not ok" << std::endl;
    }else{
      std::cout << "Piano Returned OK, moving on" << std::endl;
    }
    
    waitRet = BarPianoHttpRequest(waitressHandle, &request);
    
    if(waitRet != WAITRESS_RET_OK){
      std::cerr << "Problem Encountered, waitress returned not ok" << std::endl;
    }else{
      std::cout << "Waitress Returned OK, moving on" << std::endl;
    }
    
    pianoRet = PianoResponse(pianoHandle, &request);
  } while(pianoRet == PIANO_RET_CONTINUE_REQUEST);
  
  std::cout << "Done getting stations" << std::endl;
}


//Code from ui.c:175
WaitressReturn_t PianoSteps::BarPianoHttpRequest(WaitressHandle_t* waitressHandle, PianoRequest_t* request)
{
  waitressHandle->extraHeaders = "Content-Type: text/plain\r\n";
  waitressHandle->postData = request->postData;
  waitressHandle->method = WAITRESS_METHOD_POST;
  waitressHandle->url.path = request->urlPath;
  waitressHandle->url.tls = request->secure;
  
  return WaitressFetchBuf(waitressHandle, &request->responseData);
}


