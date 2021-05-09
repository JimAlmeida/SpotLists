#include "SpotifyAPI.h"
#include <sstream>

SpotifyAPI::SpotifyAPI(IHTTPDispatcher* d, IHTTPRequest* hr, std::string e_auth) : dispatcher(d), http_request(hr), encoded_authorization(e_auth) {}

QJsonDocument SpotifyAPI::sendGetRequest() {
	NetworkReply r = dispatcher->get(http_request);
	QString body = QString(r.content.c_str());
	qDebug() << "API Response:";
	qDebug() << body;
	return QJsonDocument::fromJson(body.toUtf8());
}

QJsonDocument SpotifyAPI::sendPostRequest() {
	NetworkReply r = dispatcher->post(http_request);
	QString body = QString(r.content.c_str());
	qDebug() << "API Response:";
	qDebug() << body;
	return QJsonDocument::fromJson(body.toUtf8());
}

QJsonDocument SpotifyAPI::getAccessToken() {
	http_request->setUrl("https://accounts.spotify.com/api/token");
	http_request->setHeader("Authorization", encoded_authorization);
	http_request->setPayload("grant_type", "client_credentials");
	http_request->enableHTTPS(true);

	QJsonDocument search_results = sendPostRequest();
	return search_results;
}

QJsonDocument SpotifyAPI::searchByArtist(std::string artist, std::string bearer_token) {
	http_request->setUrl("https://api.spotify.com/v1/search");
	http_request->setHeader("Authorization", "Bearer " + bearer_token);

	http_request->clearParameters();
	http_request->addParameter("q", artist);
	http_request->addParameter("type", "artist");
	http_request->addParameter("market", "BR");

	http_request->enableHTTPS(true);

	QJsonDocument search_results = sendGetRequest();
	return search_results;
}
QJsonDocument SpotifyAPI::searchByTrack(std::string track, std::string bearer_token){
	http_request->setUrl("https://api.spotify.com/v1/search");
	http_request->setHeader("Authorization", "Bearer " + bearer_token);

	http_request->clearParameters();
	http_request->addParameter("q", track);
	http_request->addParameter("type", "track");
	http_request->addParameter("market", "BR");

	http_request->enableHTTPS(true);

	QJsonDocument search_results = sendGetRequest();
	return search_results;
}
QJsonDocument SpotifyAPI::getArtistTopTracks(std::string artist_id, std::string bearer_token, std::string market){
	http_request->setUrl("https://api.spotify.com/v1/artists/" + artist_id + "/top-tracks");
	http_request->setHeader("Authorization", "Bearer " + bearer_token);

	http_request->clearParameters();
	http_request->addParameter("market", "BR");

	http_request->enableHTTPS(true);

	QJsonDocument search_results = sendGetRequest();
	return search_results;

}
QJsonDocument SpotifyAPI::getArtistAlbums(std::string artist_id, std::string bearer_token, std::string market){
	http_request->setUrl("https://api.spotify.com/v1/artists/" + artist_id + "/albums");
	http_request->setHeader("Authorization", "Bearer " + bearer_token);

	http_request->clearParameters();
	http_request->addParameter("market", market);

	http_request->enableHTTPS(true);

	QJsonDocument search_results = sendGetRequest();
	return search_results;
}

QJsonDocument SpotifyAPI::getAlbumTracks(std::string album_id, std::string bearer_token, std::string market) {
	http_request->setUrl("https://api.spotify.com/v1/albums/" + album_id + "/tracks");
	http_request->setHeader("Authorization", "Bearer " + bearer_token);

	http_request->clearParameters();
	http_request->addParameter("market", market);

	http_request->enableHTTPS(true);

	QJsonDocument search_results = sendGetRequest();
	return search_results;
}

QJsonDocument SpotifyAPI::getTrack(std::string track_id, std::string bearer_token, std::string market){
	http_request->setUrl("https://api.spotify.com/v1/tracks/" + track_id);
	http_request->setHeader("Authorization", "Bearer " + bearer_token);

	http_request->clearParameters();
	http_request->addParameter("market", market);

	http_request->enableHTTPS(true);

	QJsonDocument search_results = sendGetRequest();
	return search_results;
}