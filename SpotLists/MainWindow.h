#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qtextbrowser.h>
#include <qfuture.h>
#include <qfuturewatcher.h>
#include <qdockwidget.h>
#include <qstackedlayout.h>
#include <qtoolbar.h>
#include <qfiledialog.h>

#include "SearchPage.h"
#include "ContentPage.h"
#include "MusicPlayer.h"
#include "SpotifyFlow.h"
#include "SearchBar.h"
#include "ContentType.h"

#include "Playlist.h"
#include "PlaylistWidget.h"
#include "PlaylistElement.h"
#include "PlaylistData.h"
#include "PlaylistElementGUI.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    SearchPage* search_page = nullptr;
    ContentPage* album_page = nullptr;
    ContentPage* track_page = nullptr;
    MusicPlayer* media_player = nullptr;
    TopBar* navigation = nullptr;
    PlaylistWidget* playlist = nullptr;
    SpotifyFlow api;

    QDockWidget* playlist_dock = nullptr;
    QDockWidget* media_dock = nullptr;
    QWidget* central_widget = nullptr;

    QStackedLayout* page_layout = nullptr;

    void buildLayout();
    void connections();
    void setCustomStyle();
    void setUpComponents();

public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();

public slots:
    void openFile();
    void saveFile();
};
#endif // MAINWINDOW_H
