#include "QStationsList.h"
#include <QListWidget>
#include <qlayout.h>
#include <QDockWidget>

#define title "Stations List"


QStationsList::QStationsList(QWidget* parent, Qt::WindowFlags flags): QDockWidget(title, parent, flags)
{
  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
}

void QStationsList::setStations(std::vector< PandoraStation > stations)
{
  
  this->stations = stations;
  
  stationList = new QListWidget();
  
  stationList->setSortingEnabled(true);
  //TODO: Make custom QLIstWidgetItem class to have custom sorting
  //      QuickMixes and Genre Stations at top.
  for(std::vector<PandoraStation>::size_type i = 0; i != stations.size(); i++){
    stationList->addItem(new QListWidgetItem(stations[i].toString()));
  }
  
  this->setWidget(stationList);
    
  connect(stationList, SIGNAL(currentRowChanged(int)), SLOT(onNewStationSelect()));
}

void QStationsList::onNewStationSelect()
{
  if(stationList->currentRow() == -1){
    //NO TIME SELECTED, sanity check
    std::cout << "No station selected" << std::endl;
  }else{
    for(std::vector<PandoraStation>::size_type i = 0; i != stations.size(); i++){
      QListWidgetItem* selectedItem = stationList->currentItem();
      
      if(selectedItem->text() == stations[i].toString()){
	//std::cout << "You selected: " << stations[i].toString() << std::endl;
	this->selectedStation = &stations[i];
	break;
      }
    }
  }
  
  std::cout << "Station Change" << std::endl;
}



#include "QStationsList.moc"