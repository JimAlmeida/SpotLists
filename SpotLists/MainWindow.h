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
#include <qguiapplication.h>
#include <qscreen.h>

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
    QSize window_size;

    IHTTPRequest* http_request;
    IHTTPDispatcher* http_dispatcher;

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
    void queryFromAPI(std::string query);
    void requestAlbumContent(PlaylistElement album_data, ContentType type);
    void requestTrackContent(PlaylistElement album_data, ContentType type);
};
#endif // MAINWINDOW_H
