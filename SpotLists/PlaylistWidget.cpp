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
void PlaylistWidget::loadData(PlaylistData p_data) {
	std::string n_tracks = std::to_string(p_data.size()) + " tracks";

	playlist_elements->loadData(p_data);
	number_of_tracks->setText(n_tracks.c_str());
}
void PlaylistWidget::loadData(std::vector<PlaylistElement> query_results) {
	playlist_data.loadData(query_results);
	this->loadData(playlist_data);
}

void PlaylistWidget::buildLayout() {
	playlist_elements->buildListLayout();

	QGridLayout* base_layout = new QGridLayout();
	base_layout->addWidget(playlist_title, 0, 0);
	base_layout->addWidget(number_of_tracks, 1, 0, Qt::AlignRight);
	base_layout->addWidget(playlist_scroll, 2, 0);

	this->setLayout(base_layout);
}
void PlaylistWidget::connections() {
	QObject::connect(playlist_elements, &Playlist::elementSelected, this, [=](PlaylistElement data) {emit sendSongToPlayer(data); });
}

void PlaylistWidget::setCustomStyle() {}

void PlaylistWidget::saveData(std::string filepath) {
	PlaylistData::savePlaylist(filepath.c_str(), playlist_data);
}

void PlaylistWidget::loadData(std::string filepath) {
	PlaylistData data = PlaylistData::readPlaylist(filepath.c_str());
	this->loadData(data);
}