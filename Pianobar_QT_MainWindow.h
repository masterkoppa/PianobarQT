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
#include <QHBoxLayout>
#include <QPushButton>

//Phonon
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <Phonon/SeekSlider>


//Custom Defines

#define PlayIconName "media-playback-start"
#define PauseIconName "media-playback-pause"

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
    
    QPushButton* playPause;
    QPushButton* next;
    QPushButton* prev;
    
    PianoHandle_t ph;
    WaitressHandle_t wh;
    
    int playlistIndex;
    
    void getPlaylist();
    void nextSong();
    void enableButtons();
    void disableButtons();
    
    int request;
    
private slots:
    /**
     * Function used when a new station is selected. This will reset
     * the current playlist, do some cleanup and start the new station.
     */
    void onNewStationSelect();
    /**
     * Update any GUI Components that need to be updated every second of the
     * songs progress. Example:
     * 
     * Seconds elapsed on song being displayed on the GUI.
     */
    void onEachTick();
    /**
     * Slot used at the end of a song. This will queue the next song
     * by calling the next song method.
     */
    void onEndOfSong();
    /**
     * Process the downloaded album art. Params passed
     * from the signal.
     */
    void albumDownloaded(int id, bool err);
    /**
     * Togle the state of playing in the system. If not playing or paused,
     * the system will spit out an error message.
     */
    void playPauseToggle();
    /**
     * Update any GUI objects that need to change when the applications state changes.
     * 
     * For example, when the song is paused the play/pause button must have it's icon
     * changed.
     */
    void updateOnMediaStateChange();
    void onNewSongSelect();
};

#endif // PIANOBAR_QT_MAINWINDOW_H
