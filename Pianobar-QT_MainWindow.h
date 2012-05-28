#ifndef PIANOBAR_QT_MAINWINDOW_H
#define PIANOBAR_QT_MAINWINDOW_H

//Phonon
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

//Libpiano
extern "C" {
#include "piano.h"
#include "waitress.h"
}

//System Headers
#include <iostream>

//Project Headers
#include "pianosteps.h"
#include "pandorastation.h"
#include "pianohelper.h"

#include <QtGui/QApplication>
#include <QLabel>
#include <QUrl>
#include <qgridlayout.h>
#include <QDesktopWidget>
#include <QtCore/QObject>
#include <QLineEdit>
#include <QFont>
#include <QPushButton>
#include <QHBoxLayout>

class Pianobar_QT_MainWindow : public QWidget
{
  Q_OBJECT
public:
    Pianobar_QT_MainWindow(QWidget* parent = 0);
    void setHandlers(PianoHandle_t ph, WaitressHandle_t wh);
private:
    PianoHandle_t ph;
    WaitressHandle_t wh;
    Phonon::MediaObject* media;
    std::vector<PandoraSong> playlist;
    PianoSteps piano;
    PianoHelper helper;
    PandoraStation* selectedStation;
    int playIndex;
    
    
    QString timeToString(long time_msecs);
    void getMoreSongs();
     
private slots:
    /**
     * Function that is to be called for every tick of the player. This
     * method udpates the timer shown on screen and any information that
     * can change every second while there is music playing.
     */
    void onUpdate();
    void aboutToEnd();
    void onStop();
};

#endif // PIANOBAR_QT_MAINWINDOW_H
