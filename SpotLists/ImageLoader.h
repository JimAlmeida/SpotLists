#pragma once
#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <QByteArray>
#include <QPixmap>
#include "HTTPDispatcherFactory.h"
#include "HTTPRequestFactory.h"
#include <memory>

class ImageLoader {
public:
	static QPixmap loadImageFromURL(std::string url, const int height=64);
};
#endif