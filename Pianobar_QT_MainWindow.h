#ifndef PIANOBAR_QT_MAINWINDOW_H
#define PIANOBAR_QT_MAINWINDOW_H

//Project Includes

#include "pianohelper.h"
#include "pianosteps.h"
#include "QStationsList.h"
#include "QPlaylist.h"

//Libpiano includes
extern "C" {
  #include <piano.h>
  #include <waitress.h>
}

//QT Includes
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QHttp>
#include <QBuffer>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QAction>

//Phonon
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
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
    QPushButton* loveSong;
    
    QAction* likeCurrSong;
    QAction* neutralCurrSong;
    QAction* dislikeCurrSong;
    
    QBuffer* imageBuffer;
    QHttp* http;
    
    PianoHandle_t ph;
    WaitressHandle_t wh;
    
    void getPlaylist();
    
    /**
     * Tries to play the next song in the playlist.
     * 
     * This will make sure that the playlist is allways filled
     * by checking the size of the playlist and the playlist index
     * everytime calling getPlaylist() whenever needed.
     */
    void nextSong();
    
    /**
     * Tries to play the previous song in the playlist.
     * 
     * This will make sure to never make playlist index negative.
     */
    void prevSong();
    
    /**
     * Uses the play index to play the selected song, it should
     * be called by nextSong() and prevSong ONLY!
     */
    void playSong();
    
    /**********************************
     *         Helper Methods         *
     **********************************/
    
    /**
     * Enable any playback related buttons or actions
     */
    void enableButtons();
    
    /**
     * Disable any playback related buttons or actions
     */
    void disableButtons();
    
    /**
     * Builds the GUI labels, in a method for readability and
     * ease of use.
     */
    void buildLabels();
    
    
    /**********************************
     *        State Variables         *
     **********************************/
    /**
     * Id used by the http request, this is stored here to compare any http responses
     * in the listener
     */
    int request;
    
    /**
     * Piano Rating of the current song, this is updated every song
     */
    PianoSongRating_t songRating;
    
    /**
     * The current index of the playlist.
     */
    unsigned int playlistIndex;
    
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
    
    /**
     * Call any methods necessary when the next button or action is selected.
     * 
     * This will call nextSong() and print out a debugging message
     */
    void onNextSongSelect();
    
    /**
     * Call any methods necessary when the previous button or action is selected.
     * 
     * This will call prevSong() and print out a debugging message
     */
    void onPrevSongSelect();
    
    void rate_likeSong();
    
    void rate_neutSong();
    
    void rate_banSong();
};

#endif // PIANOBAR_QT_MAINWINDOW_H
