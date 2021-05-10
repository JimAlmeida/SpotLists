#pragma once
#include <qwidget.h>
#include <qmediaplayer.h>
#include <qmediaplaylist.h>
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
#include "PlaylistData.h"

class MusicPlayer: public QWidget {
	Q_OBJECT
private:
	QMediaPlayer* player = nullptr;

	MediaControls* media_controls = nullptr;

	QPushButton* add_track = nullptr;
	QPushButton* remove_track = nullptr;

	PlaylistData track_info_data;
	QMediaPlaylist* played_songs = nullptr;
	
	PlaylistElementGUI* track_info = nullptr;
	
	void setPlayIcon();
	void setPauseIcon();
	void setForwardIcon();
	void setBackwardIcon();
	void buildLayout();
	void connections();
	void setCustomStyle();

public:
	MusicPlayer(QWidget* parent = nullptr);
	MusicPlayer(PlaylistElement& track_data, QWidget* parent=nullptr);

	void setTrack(PlaylistElement& track_data);
	void setPlaylist(PlaylistData playlist);
	void setPlaylistTrack(PlaylistElement data);

signals:
	void addTrackToPlaylist(PlaylistElement track_data);
	void removeTrackFromPlaylist(PlaylistElement track_data);

public slots:
	void addTrack();
	void removeTrack();
	void setNextTrack();
	void setPreviousTrack();
};