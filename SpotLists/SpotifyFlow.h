#pragma once

#include "SpotifyAPI.h"
#include "SpotifyFilter.h"
#include "IHTTPRequest.h"
#include "IHTTPDispatcher.h"
#include "HTTPDispatcherFactory.h"
#include "HTTPRequestFactory.h"

class SpotifyFlow {
private:
	IHTTPRequest* r;
	IHTTPDispatcher* d;
	SpotifyAPI* api;

public:
	SpotifyFlow();
	SpotifyFlow(IHTTPDispatcher* dispatcher, IHTTPRequest* request);
	~SpotifyFlow();

	std::vector<PlaylistElement> searchByTrack(std::string track_name);
	std::vector<PlaylistElement> searchByArtist(std::string artist_name);
	std::vector<PlaylistElement> searchAlbums(PlaylistElement& element);
	std::vector<PlaylistElement> searchAlbumsTracks(PlaylistElement& element);
	std::string obtainToken();
};
