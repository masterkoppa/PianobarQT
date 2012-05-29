#ifndef PIANOBAR_QT_MAINWINDOW_H
#define PIANOBAR_QT_MAINWINDOW_H

#include <QMainWindow>
#include <piano.h>
#include <waitress.h>
#include "pianohelper.h"
#include "pianosteps.h"
#include "QStationsList.h"
#include <QLabel>
#include <qgridlayout.h>


//Phonon
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

class Pianobar_QT_MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Pianobar_QT_MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    Pianobar_QT_MainWindow(QString username);
    void setHandlers(PianoHandle_t ph, WaitressHandle_t wh);
    
private:
    PianoSteps piano;
    PianoHelper helper;
    
    QStationsList* stationsDock;
    Phonon::MediaObject* media;
    
    QLabel* timeLabel;
    
    PianoHandle_t ph;
    WaitressHandle_t wh;
    
private slots:
    void onNewStationSelect();
    void onEachTick();
};

#endif // PIANOBAR_QT_MAINWINDOW_H
