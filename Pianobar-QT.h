#ifndef Pianobar_QT_H
#define Pianobar_QT_H

//System Headers
#include <iostream>

//Project Headers
#include "pianosteps.h"
#include "pandorastation.h"
#include "pianohelper.h"

//Libpiano
extern "C" {
#include "piano.h"
#include "waitress.h"
}


//Phonon
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

//QT
#include <QFileDialog>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <qtextedit.h>
#include <QLabel>
#include <QUrl>
#include <QTimer>
#include <qgridlayout.h>
#include <QDesktopWidget>
#include <qgraphicsitem.h>
#include <QtCore/QObject>
#include <QLineEdit>
#include <QFont>
#include <QPushButton>
#include <QHBoxLayout>
#include <QRegExp>
#include <QRegExpValidator>





class Pianobar_QT : public QWidget
{
Q_OBJECT
public:
    Pianobar_QT(QWidget* parent = 0);

private:
    QLabel* label;
    Phonon::MediaObject* media;
    QString timeToString(long time_msecs);
    std::vector<PandoraSong> playlist;
    int playIndex;
    void getMoreSongs();
    PianoHandle_t ph;
    WaitressHandle_t wh;
    PianoSteps piano;
    PianoHelper helper;
    PandoraStation* selectedStation;
    QLineEdit* userName;
    QLineEdit* passwordField;
    QPushButton* ok;
    
    
    
    
private slots:
    /**
     * Function that is to be called for every tick of the player. This
     * method udpates the timer shown on screen and any information that
     * can change every second while there is music playing.
     */
    void onUpdate();
    void aboutToEnd();
    void onStop();
    void logIn();
    void cancelPressed();
};

#endif // Pianobar_QT_H
