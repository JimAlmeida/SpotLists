#include "SpotifyFilter.h"

std::string SpotifyFilter::filterATEndpoint(QJsonDocument api_response) {
	assert(api_response.object().contains("access_token"));
	return api_response["access_token"].toString().toStdString();
}
std::vector<PlaylistElement> SpotifyFilter::filterSearchArtistEndpoint(QJsonDocument api_response) {
	//filters artist_id, name and artist images
	QJsonObject artists = api_response["artists"].toObject();
	QJsonArray items = artists["items"].toArray();

	std::vector<PlaylistElement> elements(items.size());
	for (int i = 0; i < items.size(); ++i) {
		PlaylistElement pl;

		QJsonObject artist = items[i].toObject();
		QJsonArray image_array = artist["images"].toArray();

		//Storing information
		pl.artist = SpotifyFilter::filterArtistInfo(artist, "name");
		pl.artist_id = SpotifyFilter::filterArtistInfo(artist, "id");
		pl.artist_img = SpotifyFilter::filterImgInfo(image_array);

		elements[i] = pl;
	}
	
	return elements;
}
std::vector<PlaylistElement> SpotifyFilter::filterSearchTrackEndpoint(QJsonDocument api_response) {
	//filters artist_id, name and artist images
	QJsonObject tracks = api_response["tracks"].toObject();
	QJsonArray items = tracks["items"].toArray();

	std::vector<PlaylistElement> elements(items.size());
	for (int i = 0; i < items.size(); ++i) {

		QJsonObject track = items[i].toObject();
		QJsonArray artists = track["artists"].toArray();
		QJsonObject album = track["album"].toObject();
		QJsonArray image_array = album["images"].toArray();
		
		int s = artists.size();

		PlaylistElement pl;
		pl.track_artist = SpotifyFilter::filterMultipleArtists(artists, "name");
		pl.track_artist_id = SpotifyFilter::filterMultipleArtists(artists, "id");
		pl.album = SpotifyFilter::filterAlbumInfo(album, "name");
		pl.album_id = SpotifyFilter::filterAlbumInfo(album, "id");
		pl.album_img = SpotifyFilter::filterImgInfo(image_array);
		pl.track = SpotifyFilter::filterTrackInfo(track, "name");
		pl.track_id = SpotifyFilter::filterTrackInfo(track, "id");
		pl.sample_url = SpotifyFilter::filterTrackInfo(track, "preview_url");

		elements[i] = pl;
	}

	return elements;
}
std::vector<PlaylistElement> SpotifyFilter::filterGetArtistAlbumsEndpoint(QJsonDocument api_response, PlaylistElement& pl = PlaylistElement()) {
	QJsonArray albums = api_response["items"].toArray();
	std::vector<PlaylistElement> elements(albums.size());

	if (albums.size() > 0) {
		//Iterating over each album
		for (int i = 0; i < albums.size(); ++i) {
			QJsonObject album = albums[i].toObject();
			QJsonArray image_array = album["images"].toArray();
			QJsonArray artists = album["artists"].toArray();

			pl.album = SpotifyFilter::filterAlbumInfo(album, "name");
			pl.album_id = SpotifyFilter::filterAlbumInfo(album, "id");
			pl.album_img = SpotifyFilter::filterImgInfo(image_array);
			pl.album_artist = SpotifyFilter::filterMultipleArtists(artists, "name");
			pl.album_artist_id = SpotifyFilter::filterMultipleArtists(artists, "id");

			elements[i] = pl;
		}
	}
	return elements;
}
std::vector<PlaylistElement> SpotifyFilter::filterGetAlbumTracksEndpoint(QJsonDocument api_response, PlaylistElement& pl = PlaylistElement()) {
	QJsonArray tracks = api_response["items"].toArray();
	std::vector<PlaylistElement> elements(tracks.size());

	if (tracks.size() > 0) {
		//Iterate over each of the album's tracks
		for (int i = 0; i < tracks.size(); ++i) {
			QJsonObject track = tracks[i].toObject();
			QJsonArray artists = track["artists"].toArray();

			//Storing information
			pl.track_artist = SpotifyFilter::filterMultipleArtists(artists, "name");
			pl.track_artist_id = SpotifyFilter::filterMultipleArtists(artists, "id");
			pl.track = SpotifyFilter::filterTrackInfo(track, "name");
			pl.track_id = SpotifyFilter::filterTrackInfo(track, "id");
			pl.sample_url = SpotifyFilter::filterTrackInfo(track, "preview_url");

			elements[i] = pl;
		}
	}
	return elements;
}
PlaylistElement SpotifyFilter::filterGetTrackEndpoint(QJsonDocument api_response) {
	PlaylistElement pl;

	QJsonObject track = api_response.object();
	QJsonArray artists = track["artists"].toArray();

	//Storing information
	pl.track_artist = SpotifyFilter::filterMultipleArtists(artists, "name");
	pl.track_artist_id = SpotifyFilter::filterMultipleArtists(artists, "name");
	pl.track = SpotifyFilter::filterTrackInfo(track, "name");
	pl.track_id = SpotifyFilter::filterTrackInfo(track, "id");
	pl.sample_url = SpotifyFilter::filterTrackInfo(track, "preview_url");

	return pl;
}
std::vector<PlaylistElement> SpotifyFilter::filterGetArtistTTEndpoint(QJsonDocument api_response) {
	QJsonArray tracks = api_response["tracks"].toArray();
	std::vector<PlaylistElement> elements(tracks.size());

	if (tracks.size() > 0) {
		for (int i = 0; i < tracks.size(); ++i) {
			SpotifyImage im;
			PlaylistElement pl;

			QJsonObject track = tracks[i].toObject();
			QJsonObject album = track["album"].toObject();
			QJsonArray image_array = album["images"].toArray();
			QJsonArray artists = track["artists"].toArray();

			//Storing information
			pl.track_artist = SpotifyFilter::filterMultipleArtists(artists, "name");
			pl.track_artist_id = SpotifyFilter::filterMultipleArtists(artists, "id");
			pl.album = SpotifyFilter::filterAlbumInfo(album, "name");
			pl.album_id = SpotifyFilter::filterAlbumInfo(album, "id");
			pl.album_img = SpotifyFilter::filterImgInfo(image_array);
			pl.track = SpotifyFilter::filterTrackInfo(track, "name");
			pl.track_id = SpotifyFilter::filterTrackInfo(track, "id");
			pl.sample_url = SpotifyFilter::filterTrackInfo(track, "preview_url");

			elements[i] = pl;
		}
	}
	return elements;
}

//private functions
SpotifyImage SpotifyFilter::filterImgInfo(QJsonArray& image_array) {
	SpotifyImage im;
	if (image_array.size() > 0) {
		QJsonObject large_image = image_array[0].toObject();
		QJsonObject medium_image = image_array[1].toObject();
		QJsonObject small_image = image_array[2].toObject();
		QString large_image_url = large_image["url"].toString();
		QString medium_image_url = medium_image["url"].toString();
		QString small_image_url = small_image["url"].toString();

		im.large_image = large_image_url.toStdString();
		im.medium_image = medium_image_url.toStdString();
		im.small_image = small_image_url.toStdString();
	}
	return im;
}
std::vector<std::string> SpotifyFilter::filterMultipleArtists(QJsonArray& artist_array, const char* info) {
	std::vector<std::string> artist_info(artist_array.size());
	if (artist_array.size() > 0) {
		for (int j = 0; j < artist_array.size(); ++j) {
			QJsonObject artist = artist_array[j].toObject();
			artist_info[j] = artist[info].toString().toStdString();
		}
	}
	return artist_info;
}
std::string SpotifyFilter::filterTrackInfo(QJsonObject& track, const char* info) {
	if (track.contains(info)) {
		return track[info].toString().toStdString();
	}
	else {
		return "Error: Track not found";
	}
}
std::string SpotifyFilter::filterAlbumInfo(QJsonObject& album, const char* info) {
	if (album.contains(info)) {
		return album[info].toString().toStdString();
	}
	else {
		return "Error: Album not found";
	}
}
std::string SpotifyFilter::filterArtistInfo(QJsonObject& artist, const char* info) {
	if (artist.contains(info)) {
		return artist[info].toString().toStdString();
	}
	else {
		return "Error: Album not found";
	}
}