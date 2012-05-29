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
}


void QPlaylist::onSongChange()
{

}


#include "QPlaylist.moc"