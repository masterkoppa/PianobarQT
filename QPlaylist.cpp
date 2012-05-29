#include "QPlaylist.h"
#define title "Song List"

QPlaylist::QPlaylist(QWidget* parent, Qt::WindowFlags flags): QDockWidget(title, parent, flags)
{
  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
}


void QPlaylist::onSongChange()
{

}


#include "QPlaylist.moc"