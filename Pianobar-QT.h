#ifndef Pianobar_QT_H
#define Pianobar_QT_H

#include <QtCore/QObject>

class Pianobar_QT : public QObject
{
Q_OBJECT
public:
    Pianobar_QT();
    virtual ~Pianobar_QT();
private slots:
    void output();
};

#endif // Pianobar_QT_H
