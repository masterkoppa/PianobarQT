#ifndef QSTATIONSLIST_H
#define QSTATIONSLIST_H

#include <QDockWidget>
#include "pandorastation.h"
#include <iostream>

class QStationsList : public QDockWidget
{
  Q_OBJECT
  
public:
    QStationsList(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    void setStations(std::vector<PandoraStation> stations);
};

#endif // QSTATIONSLIST_H
