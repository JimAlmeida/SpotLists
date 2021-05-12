#pragma once
#ifndef SPOTIFYAPI_H
#define SPOTIFYAPI_H
#include <string>

#include <QJsonDocument>

#include "IHTTPDispatcher.h"
#include "IHTTPRequest.h"


class SpotifyAPI {
private:
	IHTTPDispatcher* dispatcher;
	IHTTPRequest* http_request;
	std::string encoded_authorization; //base64 client id and client secret;
	QJsonDocument sendGetRequest();
	QJsonDocument sendPostRequest();
public:
	SpotifyAPI(IHTTPDispatcher* d, IHTTPRequest* hr, std::string e_auth);
	QJsonDocument getAccessToken();
	QJsonDocument searchByArtist(std::string artist, std::string bearer_token);
	QJsonDocument searchByTrack(std::string track, std::string bearer_token);
	QJsonDocument getArtistTopTracks(std::string artist_id, std::string bearer_token, std::string market="BR");
	QJsonDocument getArtistAlbums(std::string artist_id, std::string bearer_token, std::string market = "BR");
	QJsonDocument getAlbumTracks(std::string album_id, std::string bearer_token, std::string market = "BR");
	QJsonDocument getTrack(std::string track_id, std::string bearer_token, std::string market = "BR");
	
};
#endif

