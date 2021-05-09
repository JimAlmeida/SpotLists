#pragma once
#include <qwidget.h>
#include <QtMultimedia/qmediaplayer.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qslider.h>
#include <qstyle.h>
#include <qboxlayout.h>
#include <qgridlayout.h>
#include "PlaylistElementGUI.h"
#include <string>
#include "SoundLoader.h"

class MediaControls : public QWidget {
	Q_OBJECT
private:
	QMediaPlayer* player = nullptr;

	QToolButton* play = nullptr;
	QToolButton* previous = nullptr;
	QToolButton* next = nullptr;

	QSlider* track_progress = nullptr;
	QSlider* volume = nullptr;


	void setPlayIcon();
	void setPauseIcon();
	void setForwardIcon();
	void setBackwardIcon();
	void buildLayout();
	void connections();
	void setCustomStyle();

public:
	//Do these constructors make sense?
	MediaControls(std::string& url, QWidget* parent = nullptr);
	MediaControls(QMediaPlayer* media, QWidget* parent = nullptr);

	//These ones do.
	MediaControls(QWidget* parent = nullptr);
	MediaControls(PlaylistElement& track_data, QWidget* parent = nullptr);
	MediaControls(PlaylistElement& track_data, QMediaPlayer* media, QWidget* parent);

	void setTrack(PlaylistElement& track_data);

public slots:
	void playOrPause();
	void sliderValueChanged(int value);
	void durationChanged(int duration);
	void positionChanged(int position);
	void volumeChanged(int volume);
};