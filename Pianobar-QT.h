#ifndef Pianobar_QT_H
#define Pianobar_QT_H

#include <QtCore/QObject>
//Phonon
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

//QT
#include <QFileDialog>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <qtextedit.h>
#include <QUrl>

#include <iostream>



class Pianobar_QT : public QMainWindow
{
Q_OBJECT
public:
    Pianobar_QT();
    Pianobar_QT(QString url);
};

#endif // Pianobar_QT_H
