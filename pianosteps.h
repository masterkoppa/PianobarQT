#ifndef PIANOSTEPS_H
extern "C" {
#include "piano.h"
#include <json/json_object.h>
#include "waitress.h"
}

#include "pianohelper.h"
#include <iostream>

#define PIANOSTEPS_H

class PianoSteps
{
public:
  PianoSteps();
  void PianoInitialize(PianoHandle_t* , WaitressHandle_t* );
  void PianoLogin(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle);
  void PianoGetStations(PianoHandle_t* pianoHandle, WaitressHandle_t* waitressHandle);
private:
    WaitressReturn_t BarPianoHttpRequest(WaitressHandle_t* waitressHandle, PianoRequest_t* request);
};

#endif // PIANOSTEPS_H
