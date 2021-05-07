#include "ContentPage.h"

ContentPage::ContentPage(ContentType content_type, QWidget* parent) : QWidget(parent)
{
	page_title = new QLabel(this);
	content_cover = new QLabel(this);
	playlist_data = PlaylistData();
	page_content = content_type;
	playlist_elements = new Playlist(this);
	scroller = new QScrollArea(this);

	scroller->setWidget(playlist_elements);
	scroller->setWidgetResizable(true);

	buildLayout();
	connections();
	setCustomStyle();
}

ContentPage::ContentPage(ContentType content_type, PlaylistData p_data, QWidget* parent) : ContentPage(content_type, parent) {
	loadData(content_type, p_data);
}
ContentPage::ContentPage(ContentType content_type, std::vector<PlaylistElement> p_data, QWidget* parent) : ContentPage(content_type, parent) {
	loadData(content_type, p_data);
}

void ContentPage::loadData(ContentType content_type, PlaylistData p_data) {
	playlist_data = p_data;
	playlist_elements->loadData(playlist_data);

	playlist_elements->buildGridLayout(2);

	std::string image_url;
	if (content_type == ContentType::TRACK) {
		image_url = playlist_data[0].album_img.medium_image;
		std::string album_name = "Album " + playlist_data[0].album;
		page_title->setText(album_name.c_str());
	}
	else {
		image_url = playlist_data[0].artist_img.medium_image;
		std::string artist_name = "Artist " + playlist_data[0].artist;
		page_title->setText(artist_name.c_str());
	}
	content_cover->setPixmap(ImageLoader::loadImageFromURL(image_url, 128));
}

void ContentPage::loadData(ContentType content_type, std::vector<PlaylistElement> p_data) {
	playlist_data.loadData(p_data);
	this->loadData(content_type, playlist_data);
}

void ContentPage::loadContent(ContentType content_type, PlaylistData data) {
	loadData(content_type, data);
}

void ContentPage::buildLayout() {
	QGridLayout* base_layout = new QGridLayout();
	base_layout->addWidget(content_cover, 0, 0, Qt::AlignLeft);
	base_layout->addWidget(page_title, 0, 1, Qt::AlignRight);
	base_layout->addWidget(scroller, 1, 0, 1, 2);

	this->setLayout(base_layout);
}
void ContentPage::connections() {
	QObject::connect(playlist_elements, &Playlist::elementSelected, this, &ContentPage::elementSelected);
}
void ContentPage::elementSelected(PlaylistElement data) {
	//This conditional involves a check on both the name and the sample url to check if the content page is loaded with tracks
	//It checks on both of em' because sometimes the API releases an empty sample url.
	if (data.sample_url.empty() && data.track.empty()) {
		emit requestContent(data, ContentType::TRACK);
	}
	else {
		emit sendSongToPlayer(data);
	}
}
void ContentPage::setCustomStyle() {}