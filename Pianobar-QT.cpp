#include "Pianobar-QT.h"

#include <QTimer>
#include <iostream>

Pianobar_QT::Pianobar_QT()
{
   Phonon::MediaObject* media = new Phonon::MediaObject(this);
   Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
   QUrl link = QUrl::fromEncoded("http://audio-sv5-t1-1.pandora.com/access/9004597600067023248.mp4?version=4&lid=688135222&token=R9NIz9%2B61EqsuXzRJnhy1dpdkWZgnHl8GHpLeyYsNY%2BzZQ8eakjcuXshSw2rjW2dqWQUUQ6VEQwzVPLwzJGZTpAcxEzt1%2Ft6sRsJ3WXEpjr7f4G7wTL5LyaLavc19PEATEOwyg4mkqjcUPTsEEBFk6yaFnppAK4Iabx%2B4RMyU33fDWKx7kHYZ2Z59qr9VV2HCnzXWMrVAyQju%2Bfp4V%2BfhL1h0HyylkKGwqvEsVr9h%2B3%2BCjkpFqU6eJdZggeADW9KgHAgJaztwRN7IK%2BiFoQfbsD5K2LdTk5nf6qEUtIuiRu0bEqka6ABnMoKupQwGprZ9xW4i4jK1x%2FYzZWtLamXZR4gs6TNCM12");
   
   media->setCurrentSource(Phonon::MediaSource(link));
   media->play();
   
   
}

Pianobar_QT::Pianobar_QT(QString url): QMainWindow()
{
   Phonon::MediaObject* media = new Phonon::MediaObject(this);
   Phonon::createPath(media, new Phonon::AudioOutput(Phonon::MusicCategory, this));
   QUrl link = QUrl::fromEncoded(url.toAscii());
   

   
   media->setCurrentSource(Phonon::MediaSource(link));
   media->play();
}







#include "Pianobar-QT.moc"
