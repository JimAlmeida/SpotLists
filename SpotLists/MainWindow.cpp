#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Spotlists v1.0");
    QScreen* viewport = QGuiApplication::primaryScreen();

    window_size = QSize(viewport->geometry().width(), viewport->geometry().height());

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
    page_layout->addWidget(new QWidget());
    page_layout->addWidget(search_page);
    page_layout->addWidget(album_page);
    page_layout->addWidget(track_page);
    central_widget->setLayout(page_layout);
}

void MainWindow::setUpComponents() {
    this->setCentralWidget(central_widget);
    
    playlist_dock->setWidget(playlist);
    playlist_dock->setMinimumWidth(window_size.width() * 0.15);
    playlist_dock->setTitleBarWidget(new QWidget()); //I don't want no title bar.
    
    media_dock->setWidget(media_player);
    media_dock->setTitleBarWidget(new QWidget()); //I don't want no title bar.

    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, playlist_dock);
    this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, media_dock);
    
    this->addToolBar(navigation);
}

void MainWindow::connections() {
    
    QObject::connect(playlist, &PlaylistWidget::sendPlaylistToPlayer, this, &MainWindow::sendPlaylist2Player);
    QObject::connect(search_page, &SearchPage::sendSongToPlayer, this, &MainWindow::sendSong2Player);
    QObject::connect(search_page, &SearchPage::requestContentPage, this, &MainWindow::requestAlbumContent);

    //ContentPage
    QObject::connect(album_page, &ContentPage::requestContent, this, &MainWindow::requestTrackContent);
    QObject::connect(track_page, &ContentPage::sendSongToPlayer, this, &MainWindow::sendSong2Player);

    //TopBar
    QObject::connect(navigation, &TopBar::startSearch, this, &MainWindow::queryFromAPI);
    QObject::connect(navigation, &TopBar::openFile, this, &MainWindow::openFile);
    QObject::connect(navigation, &TopBar::saveFile, this, &MainWindow::saveFile);
    
    QObject::connect(navigation, &TopBar::goBack, this, &MainWindow::navigateBack);
    QObject::connect(navigation, &TopBar::goForward, this, &MainWindow::navigateForward);

    QObject::connect(media_player, &MusicPlayer::addTrackToPlaylist, playlist, &PlaylistWidget::addTrack);
    QObject::connect(media_player, &MusicPlayer::removeTrackFromPlaylist, playlist, &PlaylistWidget::removeTrack);
}

void MainWindow::setCustomStyle() {
    this->setWindowIcon(QIcon("images/Icon.png"));
    this->setStyleSheet("background-color: #131511; color: white");
}

//Slots
void MainWindow::navigateBack() {
    if (page_layout->currentIndex() >= 1)
        page_layout->setCurrentIndex(page_layout->currentIndex() - 1);
}
void MainWindow::navigateForward() {
    if (page_layout->currentIndex() <= 2)
        page_layout->setCurrentIndex(page_layout->currentIndex() + 1);
}
void MainWindow::sendSong2Player(PlaylistElement track_data) {
    media_player->setTrack(track_data);
}
void MainWindow::sendPlaylist2Player(PlaylistElement selected_element, PlaylistData data) {
    media_player->setPlaylist(data);
    media_player->setPlaylistTrack(selected_element);
}
void MainWindow::queryFromAPI(std::string query) {
    SpotifyFlow flow;
    search_page->loadData(flow.searchByArtist(query), flow.searchByTrack(query));
    page_layout->setCurrentIndex(1);
}
void MainWindow::requestAlbumContent(PlaylistElement artist_data, ContentType type) {
    SpotifyFlow flow;
    album_page->loadData(ContentType::ALBUM, flow.searchAlbums(artist_data));
    page_layout->setCurrentIndex(2);
};
void MainWindow::requestTrackContent(PlaylistElement album_data, ContentType type) {
    SpotifyFlow flow;
    track_page->loadData(ContentType::TRACK, flow.searchAlbumsTracks(album_data));
    page_layout->setCurrentIndex(3);
};
void MainWindow::openFile() {
    QString allowed_file_extensions = "All Files(*);;Playlist Files (*.playlist);;";
    QString file_name = QFileDialog::getOpenFileName(this, "Open File", QString(), allowed_file_extensions);
    if (!file_name.isEmpty()) {
        PlaylistData playlist_data = PlaylistData::readPlaylist(file_name.toStdString().c_str());
        playlist->loadData(playlist_data);
        media_player->setPlaylist(playlist_data);
    }
}
void MainWindow::saveFile() {
    QString allowed_file_extensions = "All Files(*);;Playlist Files (*.playlist);;";
    QString file_name = QFileDialog::getSaveFileName(this, "Save File", QString(), allowed_file_extensions);
    if (!file_name.isEmpty()) {
        playlist->saveData(file_name.toStdString());
    }
}
