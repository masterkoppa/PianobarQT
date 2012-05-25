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
  void PianoLogin();
};

#endif // PIANOSTEPS_H
