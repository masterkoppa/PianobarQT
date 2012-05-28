#include "QStationsList.h"
#include <QListWidget>

#define title "Stations List"


QStationsList::QStationsList(QWidget* parent, Qt::WindowFlags flags): QDockWidget(title, parent, flags)
{
  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}

void QStationsList::setStations(std::vector< PandoraStation > stations)
{
  QListWidget* stationList = new QListWidget(this);
  
  for(std::vector<PandoraStation>::size_type i = 0; i != stations.size(); i++){
    new QListWidgetItem(QString(stations[i].toString()), stationList);
  }
}


#include "QStationsList.moc"