#ifndef CONTENTPAGE_H
#define CONTENTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include "PlaylistElement.h"
#include "PlaylistElementGUI.h"
#include "Playlist.h"
#include "PlaylistData.h"
#include "ImageLoader.h"
#include "ContentType.h"


class ContentPage : public QWidget {
	Q_OBJECT
private:
	QLabel* page_title;
	QLabel* content_cover; //artist or album cover
	PlaylistData playlist_data;
	Playlist* playlist_elements;
	ContentType page_content;

	QScrollArea* scroller = nullptr;

	void buildLayout();
	void connections();
	void setCustomStyle();
public:
	ContentPage(ContentType content_type, QWidget* parent = nullptr);
	ContentPage(ContentType content_type, PlaylistData p_data, QWidget* parent = nullptr);
	ContentPage(ContentType content_type, std::vector<PlaylistElement> p_data, QWidget* parent = nullptr);

	void loadData(ContentType content_type, PlaylistData p_data);
	void loadData(ContentType content_type, std::vector<PlaylistElement> p_data);

public slots:
	void elementSelected(PlaylistElement data);
	void loadContent(ContentType content_type, PlaylistData data);

signals:
	void requestContent(PlaylistElement data, ContentType type);
	void sendSongToPlayer(PlaylistElement data);
};
#endif 