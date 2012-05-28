#include <QCoreApplication>
#include "Pianobar-QT.h"


extern "C" {
#include "piano.h"
#include "waitress.h"
}

int main(int argc, char** argv)
{    
    QApplication app(argc, argv);
    QApplication::setApplicationName("Pianobar QT");
    Pianobar_QT mw;
    mw.resize(300, 300);
    mw.show();
    return app.exec();
}
