#pragma once
#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QBoxLayout>

#include "Playlist.h"
#include "PlaylistData.h"


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

	void loadData(PlaylistData& p_data);
	void loadData(std::vector<PlaylistElement> query_results);
	void loadData(std::string filepath);
	void saveData(std::string filepath);

public slots:
	void addTrack(PlaylistElement track_data);
	void removeTrack(PlaylistElement track_data);

signals:
	//This signal requests the MainWindow to load a track into the Media Player.
	void sendSongToPlayer(PlaylistElement data);
	void sendPlaylistToPlayer(PlaylistElement selected_element, PlaylistData data);
};
#endif