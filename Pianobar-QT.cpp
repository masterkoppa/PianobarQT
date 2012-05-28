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
   if(media->isSeekable()){
    std::cout << "I can seek this song" << std::endl;
   }else{
    std::cout << "I can not seek this song" << std::endl;
   }
   
   label = new QLabel("00:00:00", this);
   
   
   
   connect(media, SIGNAL(tick(qint64)), SLOT(onUpdate()));
   connect(media, SIGNAL(aboutToFinish()), SLOT(aboutToEnd()));
}

void Pianobar_QT::onUpdate()
{
   
   qint64 mtime = media->currentTime();
   
   QString timeFormated = timeToString(mtime);
   
   std::cout << timeFormated.toStdString() << std::endl;
   
   label->setText(timeFormated);
   //label->setText();
}

void Pianobar_QT::aboutToEnd()
{
   std::cout << "About to end" << std::endl;
}

QString Pianobar_QT::timeToString(long time_msecs)
{
  long stime = time_msecs/1000;
  
  int hours = stime / 600;
  int minutes = (stime / 60) % 60;
  int seconds = stime % 60;
  QString retString ("");
  if(hours != 0){
    retString = QString::number(hours);
    retString.append(":");
  }
  
  if(minutes < 10){
    retString.append("0");
  }
  retString.append(QString::number(minutes));
  retString.append(":");
  if(seconds < 10){
    retString.append("0");
  }
  retString.append(QString::number(seconds));
  
  return retString;
}



#include "Pianobar-QT.moc"
