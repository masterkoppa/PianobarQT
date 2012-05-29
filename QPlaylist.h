#ifndef QPLAYLIST_H
#define QPLAYLIST_H

#include <QDockWidget>
#include <QListWidget>

class QPlaylist: public QDockWidget
{
  Q_OBJECT
public:
    QPlaylist(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    void pushSong(QString songName);
    void clearPlaylist();
    void setSongSelected(int row);
    
private:
    QListWidget* playlist;
private slots:
    void onSongChange();
};

#endif // QPLAYLIST_H
