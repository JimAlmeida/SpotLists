#include "PlaylistElementGUI.h"

/*	
	track->setText("MOUSE RELEASE EVEEEEEENT!");
	this->adjustSize();
	this->resize(this->sizeHint());
*/

PlaylistElementGUI::PlaylistElementGUI(QWidget* parent) : QWidget(parent) {
	cover = new QLabel(parent = this);
	track = new QLabel(parent = this);
	artist = new QLabel(parent = this);
	content_availability = new QLabel(parent = this);
	buildlayout();
	setCustomStyle();
	setCustomSizePolicy();
}

PlaylistElementGUI::PlaylistElementGUI(const PlaylistElement& data, QWidget* parent) : PlaylistElementGUI(parent) {
	loadData(data);
}
void PlaylistElementGUI::loadTrackData(const PlaylistElement& data) {
	//Loading Track Name

	track->setText(data.track.c_str());

	//#########################################################################################
	//If track name is not avaliable, load album name
	if (data.track.empty())
		track->setText(data.album.c_str());
}
void PlaylistElementGUI::loadCoverImage(const PlaylistElement& data) {
	//Loading Image...
	QPixmap cover_image;

	//If there is an url for an album cover, then I'll load it. Otherwise I'll use the Artist cover instead. Album takes precedence over artist.
	if (!data.album_img.small_image.empty()) {
		cover_image = ImageLoader::loadImageFromURL(data.album_img.small_image);
	}
	else if (!data.artist_img.small_image.empty()) {
		cover_image = ImageLoader::loadImageFromURL(data.artist_img.small_image);
	}
	else {
		cover_image = QPixmap("images/blankcover.png");
	}

	cover->setPixmap(cover_image);
}
void PlaylistElementGUI::loadArtistData(const PlaylistElement& data) {
	//Loading Artists...
	std::string artists = "";
	std::vector<std::string> artists_array;

	//There is an order of precedence over what kind of artists to display to the user. Track artists > Album Artists > Artists.
	if (!data.track_artist.empty()) {
		artists_array = data.track_artist;
	}
	else if (!data.album_artist.empty()) {
		artists_array = data.album_artist;
	}
	else {
		artists = data.artist + ", ";
	}

	for (auto& a : artists_array) {
		artists += a;
		artists += ", ";
	}

	artists.erase(artists.end() - 2, artists.end()); //removing trailing ', ' from the string

	artist->setText(artists.c_str());
}

void PlaylistElementGUI::setContentNotAvailable() {
	content_availability->setStyleSheet("background-color:red; color:white;");
	content_availability->setText(" Song preview is not available ");
}

void PlaylistElementGUI::setContentAvailable() {
	content_availability->setStyleSheet("background-color:green; color:white;");
	content_availability->setText(" Song preview is available ");
}

void PlaylistElementGUI::assessContentAvailability(const PlaylistElement& data) {
	if (!data.track.empty()) {
		if (data.sample_url.empty()) {
			setContentNotAvailable();
		}
		else {
			setContentAvailable();
		}
	}
}
void PlaylistElementGUI::loadData(const PlaylistElement& data) {
	loadTrackData(data);
	loadCoverImage(data);
	loadArtistData(data);
	assessContentAvailability(data);
	track_data = data;
}

void PlaylistElementGUI::mouseReleaseEvent(QMouseEvent* event) {
	qDebug() << "PElementGUI has been selected: " << this->artist->text();
	emit onSelected(track_data);
}

void PlaylistElementGUI::setCustomSizePolicy() {
	track->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
	artist->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
	cover->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
	content_availability->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
}

void PlaylistElementGUI::buildlayout() {
	QVBoxLayout* description_layout = new QVBoxLayout();
	description_layout->addWidget(track);
	description_layout->addWidget(artist);
	description_layout->addWidget(content_availability);

	QHBoxLayout* base_layout = new QHBoxLayout();
	base_layout->addWidget(cover);
	base_layout->addLayout(description_layout);
	base_layout->addWidget(new QWidget());

	this->setLayout(base_layout);
}

void PlaylistElementGUI::setCustomStyle()
{
	QFont track_font;
	track_font.setPixelSize(16);
	track_font.setBold(true);
	track_font.setFamily("Arial Narrow");

	QFont artist_font;
	artist_font.setPixelSize(11);

	track->setFont(track_font);
	artist->setFont(artist_font);
	cover->setPixmap(QPixmap("images/blankcover.png"));

	QFont content_font;
	content_font.setPixelSize(11);
	content_font.setFamily("Arial");
	content_availability->setFont(content_font);
}

PlaylistElement PlaylistElementGUI::getTrackData() {
	return track_data;
}