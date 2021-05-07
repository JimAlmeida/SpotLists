#pragma once
#include "Playlist.h"
#include "PlaylistData.h"
#include <qwidget.h>
#include <qscrollarea.h>
#include <qlabel.h>
#include <qboxlayout.h>

class PlaylistWidget : public QWidget {
	Q_OBJECT
private:
	PlaylistData playlist_data;
	Playlist* playlist_elements;
	QScrollArea* playlist_scroll = nullptr;

	QLabel* playlist_title = nullptr;
	QLabel* number_of_tracks = nullptr;

	void buildLayout();
	void connections();
	void setCustomStyle();
public:
	PlaylistWidget(QWidget* parent = nullptr);
	PlaylistWidget(PlaylistData p_data, QWidget* parent = nullptr);
	PlaylistWidget(std::vector<PlaylistElement> p_data, QWidget* parent = nullptr);
	void loadData(PlaylistData p_data);
	void loadData(std::vector<PlaylistElement> query_results);
	void loadData(std::string filepath);
	void saveData(std::string filepath);

public slots:
	void addTrack();
	void removeTrack();

signals:
	//This signal requests the MainWindow to load a track into the Media Player.
	void sendSongToPlayer(PlaylistElement data);
};
