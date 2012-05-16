#include "Pianobar-QT.h"

#include <QTimer>
#include <iostream>

Pianobar_QT::Pianobar_QT()
{
    QTimer* timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), SLOT(output()) );
    timer->start( 1000 );
}

Pianobar_QT::~Pianobar_QT()
{}

void Pianobar_QT::output()
{
    std::cout << "Hello World!" << std::endl;
}

#include "Pianobar-QT.moc"
