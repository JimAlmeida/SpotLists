#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "PlaylistElement.h"
#include "ImageLoader.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qgridlayout.h>
#include <qfont.h>

class PlaylistElementGUI: public QWidget {
	Q_OBJECT
private:
	QLabel* cover;
	QLabel* track;
	QLabel* artist;
	PlaylistElement track_data;
	void buildlayout();
	void setCustomStyle();
protected:
	void mouseReleaseEvent(QMouseEvent* event) override;
public:
	PlaylistElementGUI(QWidget* parent = nullptr);
	PlaylistElementGUI(const PlaylistElement& data, QWidget* parent = nullptr);
	void loadData(const PlaylistElement& data);
	PlaylistElement getTrackData();
signals:
	void onSelected(PlaylistElement data);
};