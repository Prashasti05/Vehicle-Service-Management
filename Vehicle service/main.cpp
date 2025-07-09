#include "openingwindow.h"     // Include custom opening window class

#include <QApplication>        // Include core Qt application class

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  //create instance of Qapplication


    OpeningWindow w;   //create instance of open window
    w.show();          //display window

    return a.exec();    // Start the event loop
}
