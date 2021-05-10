#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "ImageLoader.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qgridlayout.h>
#include <qfont.h>
#include "PlaylistElement.h"

class PlaylistElementGUI: public QWidget {
	Q_OBJECT
private:
	QLabel* cover;
	QLabel* track;
	QLabel* artist;
	QLabel* content_availability;
	PlaylistElement track_data;
	
	void buildlayout();
	void setCustomStyle();
	void setCustomSizePolicy();
	void setContentNotAvailable();
	void setContentAvailable();

	void loadTrackData(const PlaylistElement& data);
	void loadCoverImage(const PlaylistElement& data);
	void loadArtistData(const PlaylistElement& data);
	void assessContentAvailability(const PlaylistElement& data);

protected:
	void mouseReleaseEvent(QMouseEvent* event) override;
public:
	PlaylistElementGUI(QWidget* parent = nullptr);
	PlaylistElementGUI(const PlaylistElement& data, QWidget* parent = nullptr);
	void loadData(const PlaylistElement& data);
	PlaylistElement getTrackData();
	friend class MusicPlayer;

signals:
	void onSelected(PlaylistElement data);

};