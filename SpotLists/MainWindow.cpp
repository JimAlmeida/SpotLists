#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Spotlists v1.0");

    search_page = new SearchPage(this);
    album_page = new ContentPage(ContentType::ALBUM, this);
    track_page = new ContentPage(ContentType::TRACK, this);
    media_player = new MusicPlayer(this);
    navigation = new TopBar(this);
    playlist = new PlaylistWidget(this);

    playlist_dock = new QDockWidget(this);
    media_dock = new QDockWidget(this);
    central_widget = new QWidget(this);

    page_layout = new QStackedLayout(); //parenting will be automatically resolved when setting a widget with this layout.

    setUpComponents();
    buildLayout();
    connections();
    setCustomStyle();
}

MainWindow::~MainWindow(){}

void MainWindow::buildLayout()
{
    page_layout->addWidget(search_page);
    page_layout->addWidget(album_page);
    page_layout->addWidget(track_page);
    central_widget->setLayout(page_layout);
}

void MainWindow::setUpComponents() {
    this->setCentralWidget(central_widget);
    playlist_dock->setWidget(playlist);
    media_dock->setWidget(media_player);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, playlist_dock);
    this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, media_dock);
    this->addToolBar(navigation);
}

void MainWindow::connections() {
    auto sendSong2Player = [&](PlaylistElement& track_data) {media_player->setTrack(track_data); };
    QObject::connect(playlist, &PlaylistWidget::sendSongToPlayer, this, sendSong2Player);
    QObject::connect(search_page, &SearchPage::sendSongToPlayer, this, sendSong2Player);
    QObject::connect(search_page, &SearchPage::requestContentPage, this, &MainWindow::requestAlbumContent);

    //ContentPage
    QObject::connect(album_page, &ContentPage::requestContent, this, &MainWindow::requestTrackContent);
    QObject::connect(track_page, &ContentPage::sendSongToPlayer, this, sendSong2Player);

    //TopBar
    QObject::connect(navigation, &TopBar::startSearch, this, &MainWindow::queryFromAPI);
    QObject::connect(navigation, &TopBar::openFile, this, &MainWindow::openFile);
    QObject::connect(navigation, &TopBar::saveFile, this, &MainWindow::saveFile);
    
    auto back = [&]() {if (page_layout->currentIndex() >= 1) page_layout->setCurrentIndex(page_layout->currentIndex() - 1); };
    QObject::connect(navigation, &TopBar::goBack, this, back);
    auto forward = [&]() {if (page_layout->currentIndex() <= 2) page_layout->setCurrentIndex(page_layout->currentIndex() + 1); };
    QObject::connect(navigation, &TopBar::goForward, this, forward);

    QObject::connect(media_player, &MusicPlayer::addTrackToPlaylist, playlist, &PlaylistWidget::addTrack);
    QObject::connect(media_player, &MusicPlayer::removeTrackFromPlaylist, playlist, &PlaylistWidget::removeTrack);
}

void MainWindow::setCustomStyle() {

}
void MainWindow::queryFromAPI(std::string query) {
    SpotifyFlow flow;
    search_page->loadData(flow.searchByArtist(query), flow.searchByTrack(query));
}

void MainWindow::requestAlbumContent(PlaylistElement album_data, ContentType type) {
    SpotifyFlow flow;
    album_page->loadData(ContentType::ALBUM, flow.searchAlbums(album_data));
    page_layout->setCurrentIndex(1);
};

void MainWindow::requestTrackContent(PlaylistElement album_data, ContentType type) {
    SpotifyFlow flow;
    track_page->loadData(ContentType::TRACK, flow.searchAlbumsTracks(album_data));
    page_layout->setCurrentIndex(2);
};

void MainWindow::openFile() {
    QString file_name = QFileDialog::getOpenFileName(this, "Open File");
    if (!file_name.isEmpty()) {
        playlist->loadData(file_name.toStdString());
    }
}
void MainWindow::saveFile() {
    QString file_name = QFileDialog::getSaveFileName(this, "Save File");
    if (!file_name.isEmpty()) {
        playlist->saveData(file_name.toStdString());
    }
}