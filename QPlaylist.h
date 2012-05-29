#ifndef QPLAYLIST_H
#define QPLAYLIST_H

#include <QDockWidget>

class QPlaylist: public QDockWidget
{
  Q_OBJECT
public:
    QPlaylist(QWidget* parent = 0, Qt::WindowFlags flags = 0);
private slots:
    void onSongChange();
};

#endif // QPLAYLIST_H
