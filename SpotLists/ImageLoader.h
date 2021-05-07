#pragma once
#include <QtCore/qbytearray.h>
#include <QtGui/qpixmap.h>
#include "HTTPDispatcherFactory.h"
#include "HTTPRequestFactory.h"
#include <memory>

class ImageLoader {
public:
	static QPixmap loadImageFromURL(std::string url, const int height=64);
};