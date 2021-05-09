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
#include "MediaControls.h"

class MusicPlayer: public QWidget {
	Q_OBJECT
private:
	QMediaPlayer* player = nullptr;

	MediaControls* media_controls = nullptr;

	QPushButton* add_track = nullptr;
	QPushButton* remove_track = nullptr;

	PlaylistElementGUI* track_info = nullptr;
	
	void setPlayIcon();
	void setPauseIcon();
	void setForwardIcon();
	void setBackwardIcon();
	void buildLayout();
	void connections();
	void setCustomStyle();

public:
	//These ones do.
	MusicPlayer(QWidget* parent = nullptr);
	MusicPlayer(PlaylistElement& track_data, QWidget* parent=nullptr);

	void setTrack(PlaylistElement& track_data);

signals:
	void addTrackToPlaylist(PlaylistElement track_data);
	void removeTrackFromPlaylist(PlaylistElement track_data);

public slots:
	void addTrack();
	void removeTrack();
};