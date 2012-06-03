#include "pianosteps.h"

/**
 * Clears the request object from its allocation
 */
inline void clearRequest(PianoRequest_t request){
  
  if(request.responseData != NULL){
      free(request.responseData);
  }

  PianoDestroyRequest(&request);
}


PianoSteps::PianoSteps()
{
  //Default constructor
}

void PianoSteps::PianoInitialize(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle)
{
  //Initialize the gnutls library, otherwise wierd things start to happen
  gnutls_global_init();
  
  //Constants for Piano Init
  const char *user = "android";
  const char *password = "AC7IBG09A3DTSYM4R41UJWL07VLN8JI7";
  const char *device = "android-generic";
  const char *in = "R=U!LH$O2B#";
  const char *out = "6#26FRL$ZWD";
  
  //Initialize PianoHandle
  //TODO: DOCUMENT METHOD IN LIBPIANOBAR
  PianoInit(pianoHandle, user, password, device, in, out);
  
  
  //Initialize WaitressHandle
  //TODO: DOCUMENT METHOD IN LIBWAITRESS
  WaitressInit(waitressHandle);
  waitressHandle->url.host = PIANO_RPC_HOST;
    
  waitressHandle->tlsFingerprint = TLS_FINGERPRINT;
}

//TODO: Allow for dynamic username and passwords
bool PianoSteps::PianoLogin(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle, char* username, char* password)
{
  PianoReturn_t pianoRet;
  WaitressReturn_t waitRet;
  
  //Store the username and password in so
  //they can be reused for timeout
  lastKnownPassword = password;
  lastKnownUsername = username;
  
  PianoRequestDataLogin_t loginReq;
  
  loginReq.user = username;
  loginReq.password = password;
  loginReq.step = 0;
  
  //ui.c:160
  PianoRequest_t request;
  
  memset(&request, 0, sizeof(request));
  
  //This is in a loop because for logging into the system you need to go twice
  do{
    request.data = (void *)&loginReq;
    
    
    //Send the login request to libpiano
    pianoRet = PianoRequest (pianoHandle, &request, PIANO_REQUEST_LOGIN);
    
    qDebug() << "LOGIN: Pianobar Request sent";
    
    if(pianoRet != PIANO_RET_OK){
      qDebug() << "Problem Encountered, piano returned not ok";
    }else{
      qDebug() << "Piano Returned OK, moving on";
    }
    
    //Send the login request to libwaitress
    waitRet = BarPianoHttpRequest(waitressHandle, &request);
    
    qDebug() << "LOGIN: Libwaitress Request sent";
    
    if(waitRet != WAITRESS_RET_OK){
      qDebug() << "Problem Encountered, waitress returned not ok" ;
    }else{
      qDebug() << "Waitress Returned OK, moving on";
    }
    
    //Analyze the response from libpiano
    pianoRet = PianoResponse(pianoHandle, &request);
    
    qDebug() << "LOGIN: Reponse sent to libpiano";
    
    if(pianoRet != PIANO_RET_CONTINUE_REQUEST){
      if(pianoRet == PIANO_RET_P_INVALID_AUTH_TOKEN){
	qDebug() << "Invalid Auth Token";
      }else if(pianoRet == PIANO_RET_OK){
	qDebug() << "Everything whent ok";
      }
    }
    
    clearRequest(request);
  } while(pianoRet == PIANO_RET_CONTINUE_REQUEST);
  
  if(pianoRet == PIANO_RET_P_INVALID_PARTNER_LOGIN){
    qDebug() << "Invalid user credentials";
    return false;
  }else if(pianoRet == PIANO_RET_OK){
    qDebug() << "Valid credentials";
    return true;
  }

  qDebug() << "Done with login";
  return false;
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
      qDebug() << "Problem Encountered, piano returned not ok";
    }else{
      qDebug() << "Piano Returned OK, moving on";
    }
    
    waitRet = BarPianoHttpRequest(waitressHandle, &request);
    
    if(waitRet != WAITRESS_RET_OK){
      qDebug() << "Problem Encountered, waitress returned not ok";
    }else{
      qDebug() << "Waitress Returned OK, moving on";
    }
    
    pianoRet = PianoResponse(pianoHandle, &request);

    if(pianoRet == PIANO_RET_P_INVALID_PARTNER_LOGIN){
      PianoLogin(pianoHandle, waitressHandle, lastKnownUsername, lastKnownPassword);
      pianoRet = PIANO_RET_CONTINUE_REQUEST;
    }
    
    clearRequest(request);
  } while(pianoRet == PIANO_RET_CONTINUE_REQUEST);
  
  qDebug() << "Done getting stations";
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

PianoSong_t* PianoSteps::PianoGetPlaylist(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle, PianoStation_t* station)
{
  PianoReturn_t pianoRet;
  WaitressReturn_t waitRet;
  PianoRequestDataGetPlaylist_t playlistReq;
  
  playlistReq.station = station;
  //TODO: Make this adjustable by some sort of settings
  playlistReq.format = PIANO_AF_MP3_HI;
  
  
  PianoRequest_t request;
  
  memset(&request, 0, sizeof(request));
  
  
  do{
    request.data = (void *)&playlistReq;
    
    pianoRet = PianoRequest (pianoHandle, &request, PIANO_REQUEST_GET_PLAYLIST);
    
    if(pianoRet != PIANO_RET_OK){
      qDebug() << "Problem Encountered, piano returned not ok";
    }else{
      qDebug() << "Piano Returned OK, moving on";
    }
    
    waitRet = BarPianoHttpRequest(waitressHandle, &request);
    
    if(waitRet != WAITRESS_RET_OK){
      qDebug() << "Problem Encountered, waitress returned not ok";
    }else{
      qDebug() << "Waitress Returned OK, moving on";
    }
    
    pianoRet = PianoResponse(pianoHandle, &request);
    
    if(pianoRet == PIANO_RET_P_INVALID_PARTNER_LOGIN){
      PianoLogin(pianoHandle, waitressHandle, lastKnownUsername, lastKnownPassword);
      pianoRet = PIANO_RET_CONTINUE_REQUEST;
    }
    
    
    clearRequest(request);
    
  } while(pianoRet == PIANO_RET_CONTINUE_REQUEST);
  
  
  return playlistReq.retPlaylist;
}

void PianoSteps::PianoRateSong(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle, PianoSong_t* song, PianoSongRating_t rating)
{
  PianoReturn_t pianoRet;
  WaitressReturn_t waitRet;
  PianoRequestDataRateSong_t songRateReq;
  
  songRateReq.song = song;
  songRateReq.rating = rating;
  
  PianoRequest_t request;
  
  memset(&request, 0, sizeof(request));
  
  
  do{
    request.data = (void *)&songRateReq;
    
    pianoRet = PianoRequest (pianoHandle, &request, PIANO_REQUEST_GET_PLAYLIST);
    
    if(pianoRet != PIANO_RET_OK){
      qDebug() << "Problem Encountered, piano returned not ok";
    }else{
      qDebug() << "Piano Returned OK, moving on";
    }
    
    waitRet = BarPianoHttpRequest(waitressHandle, &request);
    
    if(waitRet != WAITRESS_RET_OK){
      qDebug() << "Problem Encountered, waitress returned not ok";
    }else{
      qDebug() << "Waitress Returned OK, moving on";
    }
    
    pianoRet = PianoResponse(pianoHandle, &request);
    
    if(pianoRet == PIANO_RET_P_INVALID_PARTNER_LOGIN){
      PianoLogin(pianoHandle, waitressHandle, lastKnownUsername, lastKnownPassword);
      pianoRet = PIANO_RET_CONTINUE_REQUEST;
    }
    
    
    clearRequest(request);
    
  } while(pianoRet == PIANO_RET_CONTINUE_REQUEST);
  
  

}


