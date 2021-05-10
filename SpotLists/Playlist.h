#pragma once
#include "PlaylistElement.h"
#include "PlaylistData.h"
#include <vector>
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include <qwidget.h>
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
	PlaylistElementGUI* operator[](int i);
	size_t size();
	void buildListLayout();
	void clearLayout();
	void clearElements();
	void buildGridLayout(int number_of_columns);

signals:
	void elementSelected(PlaylistElement data);
};