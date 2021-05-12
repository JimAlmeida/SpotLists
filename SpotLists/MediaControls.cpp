#include "MediaControls.h"

//Constructors
MediaControls::MediaControls(QWidget* parent) : QWidget(parent) {
	play = new QToolButton(parent = this);
	previous = new QToolButton(parent = this);
	next = new QToolButton(parent = this);
	track_progress = new QSlider(parent = this);
	volume = new QSlider(parent = this);
	player = new QMediaPlayer(parent = this);

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

MediaControls::MediaControls(std::string& url, QWidget* parent) : MediaControls(parent)
{
	player = SoundLoader::loadSongFromURL(url);
}

MediaControls::MediaControls(QMediaPlayer* media, QWidget* parent) : MediaControls(parent)
{
	//overwrites base media player with an external one
	player = media;
}

MediaControls::MediaControls(PlaylistElement& track_data, QWidget* parent) : MediaControls(parent)
{
	setTrack(track_data);
}

MediaControls::MediaControls(PlaylistElement& track_data, QMediaPlayer* media, QWidget* parent) : MediaControls(parent)
{
	//overwrites base media player with an external one
	player = media;
	setTrack(track_data);
}

//Internal Private Methods
void MediaControls::setPlayIcon() {
	play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void MediaControls::setPauseIcon() {
	play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
}

void MediaControls::setForwardIcon() {
	next->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
}

void MediaControls::setBackwardIcon() {
	previous->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
}

void MediaControls::setCustomStyle() {
	this->setStyleSheet("background-color: #181818; color: white");

	play->setStyleSheet("background-color: #585858; border-radius: 14px;");
	play->setMinimumWidth(2 * play->sizeHint().width());
	play->setMinimumHeight(1.5 * play->sizeHint().height());

	previous->setStyleSheet("background-color: #585858; border-radius: 4px;");
	previous->setMinimumWidth(2 * previous->sizeHint().width());
	previous->setMaximumHeight(1.5 * previous->sizeHint().height());

	next->setStyleSheet("background-color: #585858; border-radius: 4px;");
	next->setMinimumWidth(2 * next->sizeHint().width());
	next->setMaximumHeight(1.5 * next->sizeHint().height());

	track_progress->setMinimumWidth(this->sizeHint().width() * 2);

	this->setPlayIcon();
	this->setBackwardIcon();
	this->setForwardIcon();
}

void MediaControls::buildLayout()
{
	previous->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
	play->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
	next->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

	QGridLayout* base_layout = new QGridLayout();
	base_layout->addWidget(previous, 0, 0, 1, 2, Qt::AlignRight);
	base_layout->addWidget(play, 0, 2, 1, 2, Qt::AlignCenter);
	base_layout->addWidget(next, 0, 4, 1, 2, Qt::AlignLeft);
	base_layout->addWidget(track_progress, 1, 0, 1, 6);
	base_layout->addWidget(volume, 0, 6, 2, 1);

	this->setLayout(base_layout);
}

void MediaControls::connections()
{
	QObject::connect(play, &QToolButton::clicked, this, &MediaControls::playOrPause);
	QObject::connect(track_progress, &QSlider::valueChanged, this, &MediaControls::sliderValueChanged);
	QObject::connect(volume, &QSlider::valueChanged, this, &MediaControls::volumeChanged);
	QObject::connect(next, &QToolButton::clicked, this, &MediaControls::requestNextTrack);
	QObject::connect(previous, &QToolButton::clicked, this, &MediaControls::requestPreviousTrack);
}

//Public Functions
void MediaControls::setTrack(PlaylistElement& track_data)
{
	//qDebug() << track_data.display().c_str();
	player->setMedia(QUrl(track_data.sample_url.c_str()));
}

//Slots
void MediaControls::sliderValueChanged(int value) {
	//qDebug() << "My value is: " << value << "And my duration: " << player->position();
	if (value / 100 != player->position() / 100) {
		player->setPosition(value);
	}
}

void MediaControls::durationChanged(int duration) {
	track_progress->setMaximum(duration);
}

void MediaControls::positionChanged(int position) {
	if (!track_progress->isSliderDown()) {
		track_progress->setValue(position);
	}
	if (position == player->duration()) {
		this->setPlayIcon();
	}
}

void MediaControls::volumeChanged(int volume) {
	player->setVolume(volume);
}
void MediaControls::playOrPause() {
	if (player->state() == QMediaPlayer::State::PausedState || player->state() == QMediaPlayer::State::StoppedState) {
		player->play();
		setPauseIcon();
	}
	else {
		player->pause();
		setPlayIcon();
	}
}


void MediaControls::requestNextTrack() {
	emit nextTrack();
}
void MediaControls::requestPreviousTrack() {
	emit previousTrack();
}
