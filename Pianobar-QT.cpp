#include "Pianobar-QT.h"

#include <QTimer>

#include <iostream>
#include <qgridlayout.h>
#include <QDesktopWidget>
#include <qgraphicsitem.h>

Pianobar_QT::Pianobar_QT() : QWidget()
{
  resize(1000, 800);
  //QUrl link = QUrl::fromEncoded("");
  //QPixmap image = new QPixmap();
}

Pianobar_QT::Pianobar_QT(QString url)
{
   media = new Phonon::MediaObject(this);
   Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
   QUrl link = QUrl::fromEncoded(url.toAscii());

   media->setCurrentSource(Phonon::MediaSource(link));
   media->play();
   
   media->setTickInterval(1);
   
   
   
   std::cout << "Started playback" << std::endl;
   std::cout << "Is it seekable: " << media->isSeekable() << std::endl;
   
   connect(media, SIGNAL(tick(qint64)), SLOT(onUpdate()));
   connect(media, SIGNAL(aboutToFinish()), SLOT(aboutToEnd()));
}

void Pianobar_QT::onUpdate()
{
   std::cout << media->currentTime() << std::endl;
   std::cout << "Ticked" << std::endl;
   //label->setText();
}

void Pianobar_QT::aboutToEnd()
{
   std::cout << "About to end" << std::endl;
}




#include "Pianobar-QT.moc"
