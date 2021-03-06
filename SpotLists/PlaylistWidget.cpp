#include "PlaylistWidget.h"

PlaylistWidget::PlaylistWidget(QWidget* parent) : QWidget(parent)
{
	playlist_data = PlaylistData();
	playlist_elements = new Playlist();
	playlist_scroll = new QScrollArea(this);
	playlist_title = new QLabel(this);
	number_of_tracks = new QLabel(this);

	//may cause issues of displaying empty content when data is already loaded.
	playlist_scroll->setWidget(playlist_elements);
	playlist_scroll->setWidgetResizable(true);

	buildLayout();
	connections();
	setCustomStyle();
}
PlaylistWidget::PlaylistWidget(PlaylistData p_data, QWidget* parent): PlaylistWidget(parent){
	loadData(p_data);
}
PlaylistWidget::PlaylistWidget(std::vector<PlaylistElement> p_data, QWidget* parent): PlaylistWidget(parent) {
	loadData(p_data);
}
void PlaylistWidget::buildLayout() {
	QGridLayout* base_layout = new QGridLayout();
	base_layout->addWidget(playlist_title, 0, 0);
	base_layout->addWidget(number_of_tracks, 1, 0, Qt::AlignRight);
	base_layout->addWidget(playlist_scroll, 2, 0);

	this->setLayout(base_layout);
}
void PlaylistWidget::connections() {
	QObject::connect(playlist_elements, &Playlist::elementSelected, this, [=](PlaylistElement data) {emit sendSongToPlayer(data); });
	QObject::connect(playlist_elements, &Playlist::elementSelected, this, [=](PlaylistElement selected_element) {emit sendPlaylistToPlayer(selected_element, playlist_data); });
}
void PlaylistWidget::setCustomStyle() {
	QFont title_font;
	title_font.setPixelSize(24);
	title_font.setBold(true);
	title_font.setFamily("Tw Cen MT Condensed");
	playlist_title->setFont(title_font);

	QFont subtitle_font;
	subtitle_font.setPixelSize(16);
	subtitle_font.setFamily("Tw Cen MT Condensed");
	number_of_tracks->setFont(subtitle_font);
}

void PlaylistWidget::loadData(PlaylistData& p_data) {
	playlist_data = p_data;
	std::string n_tracks = std::to_string(p_data.size()) + " tracks";

	playlist_elements->loadData(p_data);
	playlist_elements->buildListLayout();

	playlist_title->setText(p_data.getPlaylistName().c_str());
	number_of_tracks->setText(n_tracks.c_str());
	
}
void PlaylistWidget::loadData(std::vector<PlaylistElement> query_results) {
	playlist_data.loadData(query_results);
	this->loadData(playlist_data);
}
void PlaylistWidget::loadData(std::string filepath) {
	PlaylistData data = PlaylistData::readPlaylist(filepath.c_str());
	this->loadData(data);
}

void PlaylistWidget::saveData(std::string filepath) {
	PlaylistData::savePlaylist(filepath.c_str(), playlist_data);
}


void PlaylistWidget::addTrack(PlaylistElement track_data) {
	qDebug() << "PlaylistWidget::addTrack()";
	qDebug() << track_data.display().c_str();
	playlist_data.addTrack(track_data);
	this->loadData(playlist_data); //could be very computationally expensive 
}
void PlaylistWidget::removeTrack(PlaylistElement track_data) {
	qDebug() << "PlaylistWidget::removeTrack()";
	qDebug() << track_data.display().c_str();

	playlist_data.removeTrack(track_data);
	this->loadData(playlist_data); //could be very computationally expensive 
}