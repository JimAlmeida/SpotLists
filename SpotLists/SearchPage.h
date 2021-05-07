#pragma once
#include <qwidget.h>
#include <vector>
#include "PlaylistElementGUI.h"
#include "PlaylistElement.h"
#include "Playlist.h"
#include "PlaylistData.h"
#include "ContentPage.h"
#include <qscrollarea.h>

class SearchPage : public QWidget {
	Q_OBJECT
private:
	PlaylistData artist_results;
	PlaylistData track_results;
	Playlist* artist_elements = nullptr;
	Playlist* track_elements = nullptr;
	QLabel* title = nullptr;
	QLabel* artist_section_title = nullptr;
	QLabel* track_section_title = nullptr;

	QScrollArea* artist_scroll = nullptr;
	QScrollArea* track_scroll = nullptr;

	void buildLayout();
	void connections();
	void setCustomStyle();

public:
	SearchPage(QWidget* parent=nullptr);
	SearchPage(PlaylistData _artist_data, PlaylistData _track_data, QWidget* parent=nullptr);
	SearchPage(std::vector<PlaylistElement> _artist_results, std::vector<PlaylistElement> _track_results, QWidget* parent = nullptr);
	void loadData(PlaylistData _artist_data, PlaylistData _track_data);
	void loadData(std::vector<PlaylistElement> _artist_results, std::vector<PlaylistElement> _track_results);

signals:
	//This signal requests the MainWindow to fetch Album information and load it into a Content Page
	void requestContentPage(PlaylistElement data, ContentType type);
	//This signal requests the MainWindow to load a track into the Media Player.
	void sendSongToPlayer(PlaylistElement data);
};