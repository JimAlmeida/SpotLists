#include "SpotifyFlow.h"

SpotifyFlow::SpotifyFlow() {
	d = HTTPDispatcherFactory::createInstance();
	r = HTTPRequestFactory::createInstance();
	//About this token: Normally it is not wise to hard-code security tokens like the one below. 
	//It is for this reason that the GitHub repository is private. 
	//Either you store this in a environment variable or in a Key Vault like the Azure Key Vault.
	//However since this is a closed project and there is an installer which packages the .exe and all .dlls
	//I will leave this token as is.
	api = new SpotifyAPI(d, r, "Basic NjJhMjE0ZTY0OWRjNDYxY2I4NGY3MDQxNjE3MWFkNTQ6NGQwNGVjNjhmZWEwNGQ3OTgxY2ZlNWVhMWJlYzRkMTM=");
}

SpotifyFlow::SpotifyFlow(IHTTPDispatcher* dispatcher, IHTTPRequest* request): d(dispatcher), r(request) {
	//About this token: Normally it is not wise to hard-code security tokens like the one below. 
	//It is for this reason that the GitHub repository is private. 
	//Either you store this in a environment variable or in a Key Vault like the Azure Key Vault.
	//However since this is a closed project and there is an installer which packages the .exe and all .dlls
	//I will leave this token as is.
	api = new SpotifyAPI(d, r, "Basic NjJhMjE0ZTY0OWRjNDYxY2I4NGY3MDQxNjE3MWFkNTQ6NGQwNGVjNjhmZWEwNGQ3OTgxY2ZlNWVhMWJlYzRkMTM=");
}

SpotifyFlow::~SpotifyFlow() {
	delete d;
	delete r;
	delete api;
}

std::vector<PlaylistElement> SpotifyFlow::searchByTrack(std::string track_name) {
	std::string bearer = obtainToken();

	auto raw_search_results = api->searchByTrack(track_name, bearer);
	std::vector<PlaylistElement> tracks = SpotifyFilter::filterSearchTrackEndpoint(raw_search_results);

	return tracks;
}

std::vector<PlaylistElement> SpotifyFlow::searchByArtist(std::string artist_name) {
	std::string bearer = obtainToken();

	auto raw_search_results = api->searchByArtist(artist_name, bearer);
	std::vector<PlaylistElement> artists = SpotifyFilter::filterSearchArtistEndpoint(raw_search_results);

	return artists;
}

std::vector<PlaylistElement> SpotifyFlow::searchAlbums(PlaylistElement& element) {
	std::string bearer = obtainToken();

	auto raw_search_results = api->getArtistAlbums(element.artist_id, bearer);
	std::vector<PlaylistElement> albums = SpotifyFilter::filterGetArtistAlbumsEndpoint(raw_search_results, element);

	return albums;
}

std::vector<PlaylistElement> SpotifyFlow::searchAlbumsTracks(PlaylistElement& element) {
	std::string bearer = obtainToken();

	auto raw_search_results = api->getAlbumTracks(element.album_id, bearer, "US");
	std::vector<PlaylistElement> album_tracks = SpotifyFilter::filterGetAlbumTracksEndpoint(raw_search_results, element);

	return album_tracks;
}

std::string SpotifyFlow::obtainToken() {
	if (bearer_token.empty()) {
		auto raw_token_results = api->getAccessToken();
		bearer_token = SpotifyFilter::filterATEndpoint(raw_token_results);
	}
	return bearer_token;
}