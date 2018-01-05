#include <QApplication>
#include "chatwindow.h"
#include <QTime>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    ChatWindow wnd;
    wnd.show();
    return a.exec();
}
