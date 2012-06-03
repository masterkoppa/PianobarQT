#ifndef QPLAYLIST_H
#define QPLAYLIST_H

#include <QDockWidget>
#include <QListWidget>
#include <QEvent>

class QPlaylist: public QDockWidget
{
  Q_OBJECT
public:
    QPlaylist(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    void pushSong(QString songName);
    void clearPlaylist();
    void setSongSelected(int row);
    /**
     * Eats up any mouse and keyboard events to make this QListWidget
     * a READ-ONLY list, I don't want to deal with selecting a song
     * in it and being played. Let them next or prev songs
     */
    bool eventFilter(QObject* o, QEvent* e);
    
private:
    QListWidget* playlist;
};

#endif // QPLAYLIST_H
