#include "QStationsList.h"
#include <QListWidget>
#include <qlayout.h>

#define title "Stations List"


QStationsList::QStationsList(QWidget* parent, Qt::WindowFlags flags): QDockWidget(title, parent, flags)
{
  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}

void QStationsList::setStations(std::vector< PandoraStation > stations)
{
  QListWidget* stationList = new QListWidget();
  
  stationList->setSortingEnabled(true);
  //TODO: Make custom QLIstWidgetItem class to have custom sorting
  //      QuickMixes and Genre Stations at top.
  for(std::vector<PandoraStation>::size_type i = 0; i != stations.size(); i++){
    stationList->addItem(new QListWidgetItem(stations[i].toString()));
  }
  
  this->setWidget(stationList);
}


#include "QStationsList.moc"