#ifndef PIANOSTEPS_H
extern "C" {
#include "piano.h"
#include <json/json_object.h>
#include "waitress.h"
}

#include "pianohelper.h"
#include <QDebug>
#include <iostream>

#define PIANOSTEPS_H

class PianoSteps
{
public:
  PianoSteps();
  void PianoInitialize(PianoHandle_t* , WaitressHandle_t* );
  /**
   * Sets up the process of logging into the pandora service.
   * 
   * This is done via the libpiano library and it's partner libwaitress.
   * The process is as follows:
   * The program sets up the user credentials into a RequestObject.
   * This request object is sent to libpiano.PianoRequest()
   * ----This call sets up the request to be sent into the server.
   * The prepared request gets sent to the server via BarPianoHttpRequest
   * The the response is analyzed by libpiano.PianoResponse()
   * 
   * This processed is repeated twice to validate the user with the server.
   * ----Don't know why twice but it can't do it in one go apparently.
   */
  bool PianoLogin(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle, char* username, char* password);
  void PianoGetStations(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle);
  /**
   * SEE: main.c:161
   */
    PianoSong_t* PianoGetPlaylist(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle, PianoStation_t* station);
private:
    WaitressReturn_t BarPianoHttpRequest(WaitressHandle_t* waitressHandle, PianoRequest_t* request);
    char* lastKnownUsername;
    char* lastKnownPassword;
};

#endif // PIANOSTEPS_H
