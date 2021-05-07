#include "SearchPage.h"

SearchPage::SearchPage(QWidget* parent): QWidget(parent)
{
	artist_results = PlaylistData();
	track_results = PlaylistData();
	title = new QLabel("Search Results", this);
	artist_section_title = new QLabel("Artist", this);
	track_section_title = new QLabel("Track", this);
	artist_scroll = new QScrollArea(this);
	track_scroll = new QScrollArea(this);
	artist_elements = new Playlist(this);
	track_elements = new Playlist(this);

	artist_scroll->setWidget(artist_elements);
	track_scroll->setWidget(track_elements);
	artist_scroll->setWidgetResizable(true);
	track_scroll->setWidgetResizable(true);

	buildLayout();
	connections();
	setCustomStyle();
}

SearchPage::SearchPage(PlaylistData _artist_data, PlaylistData _track_data, QWidget* parent): SearchPage(parent) {
	loadData(_artist_data, _track_data);
}

SearchPage::SearchPage(std::vector<PlaylistElement> _artist_results, std::vector<PlaylistElement> _track_results, QWidget* parent) : SearchPage(parent) {
	loadData(artist_results, track_results);
}

void SearchPage::loadData(PlaylistData _artist_data, PlaylistData _track_data) {
	artist_results = _artist_data;
	track_results = _track_data;
	
	artist_elements->loadData(artist_results);
	track_elements->loadData(track_results);

	artist_elements->buildListLayout();
	track_elements->buildListLayout();
}

void SearchPage::loadData(std::vector<PlaylistElement> _artist_results, std::vector<PlaylistElement> _track_results) {
	artist_results = PlaylistData(_artist_results);
	track_results = PlaylistData(_track_results);
	this->loadData(artist_results, track_results);
}

void SearchPage::buildLayout() {
	QGridLayout* base_layout = new QGridLayout();
	base_layout->addWidget(title, 0, 0, 1, 2, Qt::AlignCenter);
	base_layout->addWidget(artist_section_title, 1, 0, 1, 1, Qt::AlignLeft);
	base_layout->addWidget(track_section_title, 1, 1, 1, 1, Qt::AlignLeft);
	base_layout->addWidget(artist_scroll, 2, 0, 1, 1);
	base_layout->addWidget(track_scroll, 2, 1, 1, 1);

	this->setLayout(base_layout);
}

void SearchPage::connections() {
	//I am using lambdas here to avoid defining one-line slots;
	QObject::connect(artist_elements, &Playlist::elementSelected, this, [=](PlaylistElement data) {emit requestContentPage(data, ContentType::TRACK); });
	QObject::connect(track_elements, &Playlist::elementSelected, this, [=](PlaylistElement data) {emit sendSongToPlayer(data); });
}
void SearchPage::setCustomStyle() {}