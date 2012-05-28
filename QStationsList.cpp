#include "QStationsList.h"

#define title "Stations List"

QStationsList::QStationsList(QWidget* parent, Qt::WindowFlags flags): QDockWidget(title, parent, flags)
{
  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}

#include "QStationsList.moc"