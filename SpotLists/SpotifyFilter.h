#pragma once
#ifndef SPOTIFYFILTER_H
#define SPOTIFYFILTER_H

#include <string>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonObject>

#include "SpotifyFilter.h"
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
#endif