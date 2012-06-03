#include "QPlaylist.h"
#define title "Song List"

QPlaylist::QPlaylist(QWidget* parent, Qt::WindowFlags flags): QDockWidget(title, parent, flags)
{
  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
  
  
  //Demo playlist
  playlist = new QListWidget();
  
//   playlist->addItem(new QListWidgetItem("Song 1"));
//   playlist->addItem(new QListWidgetItem("Song 2"));
//   playlist->addItem(new QListWidgetItem("Song 5"));
//   playlist->addItem(new QListWidgetItem("Song 4"));
//   playlist->addItem(new QListWidgetItem("Song 3"));
  
  this->setWidget(playlist);
  
  
  playlist->installEventFilter(this);
  playlist->viewport()->installEventFilter(this);
}

void QPlaylist::clearPlaylist()
{
  playlist->clear();
}


void QPlaylist::pushSong(QString songName)
{
  playlist->addItem(new QListWidgetItem(songName));
}

void QPlaylist::setSongSelected(int row)
{
  playlist->setCurrentRow(row);
}

bool QPlaylist::eventFilter(QObject* o, QEvent* e)
{
  bool ret = false;
 
  if( o == this->playlist &&( e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease ) )
  {
    ret = true;
  }
  else if( o == this->playlist->viewport() && ( e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease || e->type() == QEvent::MouseButtonDblClick || e->type() == QEvent::MouseMove || e->type() == QEvent::MouseTrackingChange ) )
  {
    ret = true;
  }
  
return ret;
}


#include "QPlaylist.moc"