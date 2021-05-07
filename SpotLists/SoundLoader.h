#pragma once
#include <QtCore/qbytearray.h>
#include "HTTPDispatcherFactory.h"
#include "HTTPRequestFactory.h"
#include <QtMultimedia/qmediaplayer.h>
#include <QtCore/qbuffer.h>

class SoundLoader {
public:
	static QMediaPlayer* loadSongFromURL(std::string url);
};