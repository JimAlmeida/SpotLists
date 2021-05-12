#pragma once
#ifndef PLAYLIST_H
#define PLAYLIST_H


#include <vector>

#include <QFile>
#include <QTextStream>
#include <QWidget>

#include "PlaylistData.h"
#include "PlaylistElement.h"
#include "PlaylistElementGUI.h"


class Playlist: public QWidget {
	Q_OBJECT
private:
	PlaylistData data;
	std::vector<PlaylistElementGUI*> playlist;
	void disconnectAll();
	void connections();
public:
	Playlist(QWidget* parent = nullptr);
	Playlist(PlaylistData& _elements, QWidget* parent = nullptr);

	void loadData(PlaylistData& _elements);
	void clearLayout();
	void clearElements();
	void buildGridLayout(int number_of_columns);
	void buildListLayout();

	PlaylistElementGUI* operator[](int i);
	size_t size();

signals:
	void elementSelected(PlaylistElement data);
};
#endif