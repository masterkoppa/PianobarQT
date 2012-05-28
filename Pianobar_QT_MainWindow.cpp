#include "Pianobar_QT_MainWindow.h"
#include "QStationsList.h"
#include <QLabel>
#include <qgridlayout.h>

Pianobar_QT_MainWindow::Pianobar_QT_MainWindow(QWidget* parent, Qt::WindowFlags flags): QMainWindow(parent, flags)
{
  //DO Nothing
}

Pianobar_QT_MainWindow::Pianobar_QT_MainWindow(QString username): QMainWindow()
{
  resize(500, 500);
  QString title ("");
  title.append("Pianobar QT: ");
  title.append(username);
  
  this->setWindowTitle(title);
  
   QWidget *centralWidget = new QWidget(this);
   
   QGridLayout* test = new QGridLayout(centralWidget);
   
   QLabel* label = new QLabel("TEST");
   
   test->addWidget(label, 0, 0);
   
   centralWidget->setLayout(test);
   setCentralWidget(centralWidget);
   
   QStationsList* example = new QStationsList();
   
   addDockWidget(Qt::LeftDockWidgetArea, example);
  
}


#include "Pianobar_QT_MainWindow.moc"