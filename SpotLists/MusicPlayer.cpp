#include "MusicPlayer.h"

//Constructors
MusicPlayer::MusicPlayer(QWidget* parent): QWidget(parent) {
	play = new QToolButton(parent = this);
	previous = new QToolButton(parent = this);
	next = new QToolButton(parent = this);
	track_progress = new QSlider(parent = this);
	volume = new QSlider(parent = this);
	player = new QMediaPlayer(parent = this);
	track_info = new PlaylistElementGUI(parent = this);

	buildLayout();
	connections();
	setCustomStyle();

	volume->setOrientation(Qt::Vertical);
	volume->setRange(0, 100);
	volume->setValue(100);

	track_progress->setOrientation(Qt::Horizontal);
	track_progress->setTracking(false); //only change the song when the user releases the slider. This is standard in Spotify's own application.
	track_progress->setMaximum(player->duration());
}

MusicPlayer::MusicPlayer(std::string& url, QWidget* parent) : QWidget(parent)
{
	play = new QToolButton(parent = this);
	previous = new QToolButton(parent = this);
	next = new QToolButton(parent = this);

	track_progress = new QSlider(parent = this);
	volume = new QSlider(parent = this);

	player = SoundLoader::loadSongFromURL(url);
}

MusicPlayer::MusicPlayer(QMediaPlayer* media, QWidget* parent) : QWidget(parent)
{
	play = new QToolButton(parent = this);
	previous = new QToolButton(parent = this);
	next = new QToolButton(parent = this);

	track_progress = new QSlider(parent = this);
	volume = new QSlider(parent = this);
	player = media;
}

MusicPlayer::MusicPlayer(PlaylistElement& track_data, QWidget* parent) : MusicPlayer(parent)
{
	setTrack(track_data);
}

//Internal Private Methods
void MusicPlayer::setPlayIcon() {
	play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void MusicPlayer::setPauseIcon() {
	play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
}

void MusicPlayer::setForwardIcon(){
	next->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
}

void MusicPlayer::setBackwardIcon() {
	previous->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
}

void MusicPlayer::setCustomStyle() {
	this->setStyleSheet("background-color: #181818; color: white");

	play->setStyleSheet("background-color: #585858; border: none");
	play->setMinimumWidth(2 * play->sizeHint().width());
	play->setMinimumHeight(1.5 * play->sizeHint().height());

	previous->setStyleSheet("background-color: #585858; border: none");
	previous->setMinimumWidth(2 * previous->sizeHint().width());
	previous->setMinimumHeight(1.5 * previous->sizeHint().height());

	next->setStyleSheet("background-color: #585858; border: none");
	next->setMinimumWidth(2 * next->sizeHint().width());
	next->setMinimumHeight(1.5 * next->sizeHint().height());

	this->setPlayIcon();
	this->setBackwardIcon();
	this->setForwardIcon();
}

void MusicPlayer::buildLayout()
{
	QGridLayout* base_layout = new QGridLayout();
	base_layout->addWidget(previous, 0, 0, 1, 2);
	base_layout->addWidget(play, 0, 2, 1, 2);
	base_layout->addWidget(next, 0, 4, 1, 2);
	base_layout->addWidget(track_progress, 1, 0, 1, 6);
	base_layout->addWidget(volume, 0, 6, 2, 1);

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(track_info);
	layout->addLayout(base_layout);

	this->setLayout(layout);
}

void MusicPlayer::connections()
{
	QObject::connect(play, &QToolButton::clicked, this, &MusicPlayer::playOrPause);
	QObject::connect(track_progress, &QSlider::valueChanged, this, &MusicPlayer::sliderValueChanged);
	QObject::connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::positionChanged);
	QObject::connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayer::durationChanged);
	QObject::connect(volume, &QSlider::valueChanged, this, &MusicPlayer::volumeChanged);
}

//Public Functions
void MusicPlayer::setTrack(PlaylistElement& track_data)
{
	player->setMedia(QUrl(track_data.sample_url.c_str()));
	track_info->loadData(track_data);
}

//Slots
void MusicPlayer::sliderValueChanged(int value) {
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