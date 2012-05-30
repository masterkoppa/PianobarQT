#ifndef PIANOBAR_QT_MAINWINDOW_H
#define PIANOBAR_QT_MAINWINDOW_H

#include <QMainWindow>
#include <piano.h>
#include <waitress.h>
#include "pianohelper.h"
#include "pianosteps.h"
#include "QStationsList.h"
#include "QPlaylist.h"
#include <QLabel>
#include <qgridlayout.h>
#include <QListWidget>
#include "QPlaylist.h"
#include <QHttpHeader>
#include <QHttp>
#include <QBuffer>
#include <QPicture>


//Phonon
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <Phonon/SeekSlider>

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
    std::vector<PandoraSong> playlist;
    
    QStationsList* stationsDock;
    QPlaylist* playlistDock;
    Phonon::MediaObject* media;
    
    QLabel* timeLabel;
    QLabel* albumArt;
    QByteArray imageData;
    QLabel* songName;
    QLabel* artist;
    QLabel* album;
    
    PianoHandle_t ph;
    WaitressHandle_t wh;
    
    int playlistIndex;
    
    void getPlaylist();
    void nextSong();
    int request;
    
private slots:
    void onNewStationSelect();
    void onEachTick();
    void onEndOfSong();
    void albumDownloaded(int id, bool err);
};

#endif // PIANOBAR_QT_MAINWINDOW_H
