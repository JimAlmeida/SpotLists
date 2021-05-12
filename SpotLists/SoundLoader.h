#pragma once
#ifndef SOUNDLOADER_H
#define SOUNDLOADER_H

#include <QBuffer>
#include <QByteArray>
#include <QMediaPlayer>

#include "HTTPDispatcherFactory.h"
#include "HTTPRequestFactory.h"


class SoundLoader {
public:
	static QMediaPlayer* loadSongFromURL(std::string url);
};
#endif // !SOUNDLOADER_H

