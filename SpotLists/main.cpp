#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <cpr/cpr.h>
#include "CURLDispatcher.h"
#include "CURLRequest.h"
#include "IHTTPRequest.h"
#include "SpotifyAPI.h"
#include "SpotifyFilter.h"
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsondocument.h>
#include "Tests.h"
#include <QtWidgets/qlabel.h>
#include <QtCore/qbytearray.h>
#include <QtGui/qpixmap.h>
#include <QtCore/qfile.h>


int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath(".");
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    MainWindow w;
    w.showMaximized();
    //QWidget* w = GUITests::artistPage();
    //w->show();
    return a.exec();
}
