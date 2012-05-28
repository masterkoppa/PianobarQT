#ifndef PIANOBAR_QT_MAINWINDOW_H
#define PIANOBAR_QT_MAINWINDOW_H

#include <QMainWindow>

class Pianobar_QT_MainWindow : public QMainWindow
{
  Q_OBJECT
public:
    Pianobar_QT_MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    Pianobar_QT_MainWindow(QString username);
    
};

#endif // PIANOBAR_QT_MAINWINDOW_H
