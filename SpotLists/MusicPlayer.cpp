#include "MusicPlayer.h"

//Constructors
MusicPlayer::MusicPlayer(QWidget* parent): QWidget(parent) {
	player = new QMediaPlayer(this);
	media_controls = new MediaControls(player, this);
	track_info = new PlaylistElementGUI(parent = this);
	add_track = new QPushButton("Add Track to Playlist", this);
	remove_track = new QPushButton("Remove Track from Playlist", this);

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
}

//Public Functions
void MusicPlayer::setTrack(PlaylistElement& track_data)
{
	player->stop();
	player->setMedia(QUrl(track_data.sample_url.c_str()));
	track_info->loadData(track_data);
}

//Slots
/*void MusicPlayer::sliderValueChanged(int value) {
	qDebug() << "My value is: " << value << "And my duration: " << player->position();
	if (value/100 != player->position()/100) {
		player->setPosition(value);
	}
}

void MusicPlayer::durationChanged(int duration) {
	track_progress->setMaximum(duration);
}

void MusicPlayer::positionChanged(int position) {
	if (!track_progress->isSliderDown()) {
		track_progress->setValue(position);
	}
	if (position == player->duration()) {
		this->setPlayIcon();
	}
}

void MusicPlayer::volumeChanged(int volume) {
	player->setVolume(volume);
}

void MusicPlayer::playOrPause() {
	if (player->state() == QMediaPlayer::State::PausedState || player->state() == QMediaPlayer::State::StoppedState) {
		this->setPauseIcon();
		player->play();
	}
	else {
		this->setPlayIcon();
		player->pause();
	}
}
*/
void MusicPlayer::addTrack() {
	emit addTrackToPlaylist(track_info->getTrackData());
}
void MusicPlayer::removeTrack() {
	emit removeTrackFromPlaylist(track_info->getTrackData());
}