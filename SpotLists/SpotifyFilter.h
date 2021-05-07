#pragma once

#include <string>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include "SpotifyFilter.h"
#include "QtCore/qdebug.h"
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsonobject>
#include "PlaylistElement.h"

class SpotifyFilter {
public:
	static std::string filterATEndpoint(QJsonDocument api_response);
	static std::vector<PlaylistElement> filterSearchArtistEndpoint(QJsonDocument api_response);
	static std::vector<PlaylistElement> filterSearchTrackEndpoint(QJsonDocument api_response);
	static std::vector<PlaylistElement> filterGetArtistTTEndpoint(QJsonDocument api_response);
	static std::vector<PlaylistElement> filterGetArtistAlbumsEndpoint(QJsonDocument api_response, PlaylistElement& pl);
	static std::vector<PlaylistElement> filterGetAlbumTracksEndpoint(QJsonDocument api_response, PlaylistElement& pl);
	static PlaylistElement filterGetTrackEndpoint(QJsonDocument api_response);
private:
	static SpotifyImage filterImgInfo(QJsonArray& image_array);
	static std::vector<std::string> filterMultipleArtists(QJsonArray& artist_array, const char* info);
	static std::string filterTrackInfo(QJsonObject& track, const char* info);
	static std::string filterAlbumInfo(QJsonObject& album, const char* info);
	static std::string filterArtistInfo(QJsonObject& artist, const char* info);
};