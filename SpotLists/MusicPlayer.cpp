#include "MusicPlayer.h"

//Constructors
MusicPlayer::MusicPlayer(QWidget* parent): QWidget(parent) {

	track_info_data = PlaylistData();

	player = new QMediaPlayer(this);
	media_controls = new MediaControls(player, this);
	track_info = new PlaylistElementGUI(parent = this);
	add_track = new QPushButton("Add Track to Playlist", this);
	remove_track = new QPushButton("Remove Track from Playlist", this);
	played_songs = new QMediaPlaylist(this);

	played_songs->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

	media_controls->enablePreviousButton(false);
	media_controls->enableNextButton(false);

	player->setPlaylist(played_songs);
	buildLayout();
	connections();
	setCustomStyle();
}
MusicPlayer::MusicPlayer(PlaylistElement& track_data, QWidget* parent) : MusicPlayer(parent)
{
	setTrack(track_data);
}

//Internal Private Methods

void MusicPlayer::setCustomStyle() {
	this->setStyleSheet("background-color: #131511; color: white");
	media_controls->setMaximumSize(media_controls->sizeHint());
	add_track->setStyleSheet("background-color: #233517; color: white");
	remove_track->setStyleSheet("background-color: #233517; color: white");

	QFont button_font;
	button_font.setPixelSize(16);
	button_font.setFamily("Tw Cen MT Condensed");
	add_track->setFont(button_font);
	remove_track->setFont(button_font);
}

void MusicPlayer::buildLayout()
{
	QWidget* right_spacer = new QWidget();

	QVBoxLayout* playlist_controls = new QVBoxLayout();
	playlist_controls->addWidget(add_track);
	playlist_controls->addWidget(remove_track);

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(track_info, 1);
	layout->addWidget(media_controls, 1,Qt::AlignCenter);
	layout->addWidget(right_spacer, 1);
	layout->addLayout(playlist_controls, 1);

	int w1 = add_track->sizeHint().width();
	int w2 = remove_track->sizeHint().width();
	int maximum_button_width = (w1 >= w2) ? w1 : w2;
	add_track->setMaximumWidth(maximum_button_width*1.1);
	remove_track->setMaximumWidth(maximum_button_width*1.1);

	add_track->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::MinimumExpanding);
	remove_track->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::MinimumExpanding);
	this->setLayout(layout);
	this->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
}

void MusicPlayer::connections()
{
	QObject::connect(add_track, &QPushButton::clicked, this, &MusicPlayer::addTrack);
	QObject::connect(remove_track, &QPushButton::clicked, this, &MusicPlayer::removeTrack);
	QObject::connect(player, &QMediaPlayer::positionChanged, media_controls, &MediaControls::positionChanged);
	QObject::connect(player, &QMediaPlayer::durationChanged, media_controls, &MediaControls::durationChanged);
	QObject::connect(media_controls, &MediaControls::nextTrack, this, &MusicPlayer::setNextTrack);
	QObject::connect(media_controls, &MediaControls::previousTrack, this, &MusicPlayer::setPreviousTrack);
}

//Public Functions
void MusicPlayer::setTrack(PlaylistElement& track_data)
{
	player->stop();
	media_controls->setPlayIcon();

	track_info->loadData(track_data);
	player->setMedia(QUrl(track_data.sample_url.c_str()));
	media_controls->enableNextButton(false);
	media_controls->enablePreviousButton(false);
}
void MusicPlayer::setPlaylist(PlaylistData playlist) {
	if (playlist.size() > 0) {
		track_info_data = playlist;
		played_songs->clear();
		for (int i = 0; i < playlist.size(); ++i)
		{
			played_songs->addMedia(QUrl(playlist[i].sample_url.c_str()));
		}
		player->setPlaylist(played_songs);
	}
}
void MusicPlayer::setPlaylistTrack(PlaylistElement data) {
	if (!data.track_id.empty()) {
		player->stop();
		media_controls->setPlayIcon();

		int pos = track_info_data.findTrack(data.track_id);
		track_info->loadData(track_info_data[pos]);
		played_songs->setCurrentIndex(pos);

		qDebug() << "MY POS: " << pos;
		bool enable_previous = (pos == 0) ? false : true;
		media_controls->enablePreviousButton(enable_previous);

		bool enable_forward = (pos == track_info_data.size()-1) ? false : true;
		media_controls->enableNextButton(enable_forward);
	}
}
//Slots
void MusicPlayer::addTrack() {
	PlaylistElement track_data = track_info->getTrackData();
	played_songs->addMedia(QUrl(track_data.sample_url.c_str()));
	track_info_data.addTrack(track_data);
	
	media_controls->enablePreviousButton(true);
	media_controls->enableNextButton(false);
	player->setPlaylist(played_songs);

	played_songs->setCurrentIndex(played_songs->mediaCount() - 1);

	emit addTrackToPlaylist(track_data);
}
void MusicPlayer::removeTrack() {

	emit removeTrackFromPlaylist(track_info->getTrackData());

	track_info_data.erase(track_info_data.begin() + played_songs->currentIndex());
	played_songs->removeMedia(played_songs->currentIndex());

	played_songs->setCurrentIndex(0);

	media_controls->enablePreviousButton(false);
	bool activate_next_button = (played_songs->mediaCount() > 1) ? true : false;
	media_controls->enableNextButton(activate_next_button);


	if (played_songs->mediaCount()>0){
		track_info->loadData(track_info_data[0]);
		remove_track->setEnabled(true);
	}
	else {
		PlaylistElement blank_element;
		track_info->loadData(blank_element);
		track_info->content_availability->setText("");
		remove_track->setEnabled(false);
	}
}

void MusicPlayer::setNextTrack() {
	player->stop();
	media_controls->setPlayIcon();
	
	int next_index = played_songs->currentIndex()+1;
	// If next_index is not out of bounds then do the instructions below
	if (next_index < played_songs->mediaCount()) {
		played_songs->setCurrentIndex(next_index);
		track_info->loadData(track_info_data[next_index]);
		media_controls->enablePreviousButton(true);
	}
	//If next_index is out of bounds, disable the next button.
	if (next_index == played_songs->mediaCount()-1) {
		media_controls->enableNextButton(false);
	}
}

void MusicPlayer::setPreviousTrack() {
	player->stop();
	media_controls->setPlayIcon();

	int previous_index = played_songs->currentIndex() - 1;
	// If previous_index is not out of bounds then do the instructions below
	if (previous_index > 0) {
		played_songs->setCurrentIndex(previous_index);
		track_info->loadData(track_info_data[previous_index]);
		media_controls->enableNextButton(true);
	}
	if (previous_index == 0) {
		played_songs->setCurrentIndex(previous_index);
		track_info->loadData(track_info_data[previous_index]);
		media_controls->enableNextButton(true);
		media_controls->enablePreviousButton(false);
	}
}