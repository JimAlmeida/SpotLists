#pragma once
#include <string>
#include <exception>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

struct SpotifyImage {
	std::string large_image;
	std::string medium_image;
	std::string small_image;
};

struct PlaylistElement {
public:
	//Artist Information
	std::string artist;
	std::string artist_id;
	std::vector<std::string> album_artist;
	std::vector<std::string> album_artist_id;
	std::vector<std::string> track_artist;
	std::vector<std::string> track_artist_id;
	SpotifyImage artist_img;
	//Album Information
	std::string album;
	std::string album_id;
	SpotifyImage album_img;
	//Track Information
	std::string track;
	std::string track_id;
	std::string sample_url;

	std::string display() {
		std::string album_artists = "";
		for (auto& artist : album_artist) {
			album_artists += artist;
			album_artists += ", ";
		}
		std::string track_artists = "";
		for (auto& artist : track_artist) {
			track_artists += artist;
			track_artists += ", ";
		}
		std::string album_artists_ids = "";
		for (auto& artist : album_artist_id) {
			album_artists_ids += artist;
			album_artists_ids += ", ";
		}
		std::string track_artists_ids = "";
		for (auto& artist : track_artist_id) {
			track_artists_ids += artist;
			track_artists_ids += ", ";
		}

		return
			"Artist: " + artist + '\n' +
			"Artist ID: " + artist_id + '\n' +
			"Album: " + album + '\n' +
			"Album ID: " + album_id + '\n' +
			"Track: " + track + '\n' +
			"Track ID: " + track_id + '\n' +
			"Sample URL: " + sample_url + '\n' +
			"Artist Img (Large): " + artist_img.large_image + '\n' +
			"Artist Img (Medium): " + artist_img.medium_image + '\n' +
			"Artist Img (Small): " + artist_img.small_image + '\n' +
			"Album Img (Large): " + album_img.large_image + '\n' +
			"Album Img (Medium): " + album_img.medium_image + '\n' +
			"Album Img (Small): " + album_img.small_image + '\n' +
			"Album Artists: " + album_artists + '\n' +
			"Album Artists IDs: " + album_artists_ids + '\n' +
			"Track Artists: " + track_artists + '\n' +
			"Track Artists IDs: " + track_artists_ids + '\n'
		;
	}
	static QJsonObject toJson(const PlaylistElement& pl) {
		QJsonValue _artist(pl.artist.c_str());
		QJsonValue _artist_id(pl.artist_id.c_str());
		QJsonValue _album(pl.album.c_str());
		QJsonValue _album_id(pl.album_id.c_str());
		QJsonValue _track(pl.track.c_str());
		QJsonValue _track_id(pl.track_id.c_str());
		QJsonValue _sample_url(pl.sample_url.c_str());

		QJsonArray _album_artist;
		for (int i = 0; i < pl.album_artist.size(); ++i) {
			QJsonValue v(pl.album_artist[i].c_str());
			_album_artist.push_back(v);
		}
		QJsonArray _album_artist_id;
		for (int i = 0; i < pl.album_artist_id.size(); ++i) {
			QJsonValue v(pl.album_artist_id[i].c_str());
			_album_artist_id.push_back(v);
		}
		QJsonArray _track_artist;
		for (int i = 0; i < pl.track_artist.size(); ++i) {
			QJsonValue v(pl.track_artist[i].c_str());
			_track_artist.push_back(v);
		}
		QJsonArray _track_artist_id;
		for (int i = 0; i < pl.track_artist_id.size(); ++i) {
			QJsonValue v(pl.track_artist_id[i].c_str());
			_track_artist_id.push_back(v);
		}

		QJsonArray _artist_img;
		//follows same order of image size as the Spotify API
		_artist_img.push_back(QJsonValue(pl.artist_img.large_image.c_str()));
		_artist_img.push_back(QJsonValue(pl.artist_img.medium_image.c_str()));
		_artist_img.push_back(QJsonValue(pl.artist_img.small_image.c_str()));

		QJsonArray _album_img;
		//follows same order of image size as the Spotify API
		_album_img.push_back(QJsonValue(pl.album_img.large_image.c_str()));
		_album_img.push_back(QJsonValue(pl.album_img.medium_image.c_str()));
		_album_img.push_back(QJsonValue(pl.album_img.small_image.c_str()));

		QJsonObject root;
		root.insert("artist", _artist);
		root.insert("artist_id", _artist_id);
		root.insert("album", _album);
		root.insert("album_id", _album_id);
		root.insert("track", _track);
		root.insert("track_id", _track_id);
		root.insert("sample_url", _sample_url);
		root.insert("album_artist", _album_artist);
		root.insert("album_artist_id", _album_artist_id);
		root.insert("track_artist", _track_artist);
		root.insert("track_artist_id", _track_artist_id);
		root.insert("artist_img", _artist_img);
		root.insert("album_img", _album_img);

		return root;
	}
	static PlaylistElement fromJson(const QJsonObject& root) {
		PlaylistElement pl;
		if (root.contains("album")) {
			pl.album = root["album"].toString().toStdString();
		}
		if (root.contains("album_id")) {
			pl.album_id = root["album_id"].toString().toStdString();
		}
		if (root.contains("track")) {
			pl.track = root["track"].toString().toStdString();
		}
		if (root.contains("track_id")) {
			pl.track_id = root["track_id"].toString().toStdString();
		}
		if (root.contains("sample_url")) {
			pl.sample_url = root["sample_url"].toString().toStdString();
		}
		if (root.contains("artist")) {
			pl.artist = root["artist"].toString().toStdString();
		}
		if (root.contains("artist_id")) {
			pl.artist_id = root["artist_id"].toString().toStdString();
		}
		if (root.contains("album_artist")) {
			QJsonArray _album_artist = root["album_artist"].toArray();
			for (int i = 0; i < _album_artist.size(); ++i) {
				pl.album_artist.push_back(_album_artist[i].toString().toStdString());
			}
		}
		if (root.contains("album_artist_id")) {
			QJsonArray _album_artist_id = root["album_artist_id"].toArray();
			for (int i = 0; i < _album_artist_id.size(); ++i) {
				pl.album_artist_id.push_back(_album_artist_id[i].toString().toStdString());
			}
		}
		if (root.contains("track_artist")) {
			QJsonArray _track_artist = root["track_artist"].toArray();
			for (int i = 0; i < _track_artist.size(); ++i) {
				pl.track_artist.push_back(_track_artist[i].toString().toStdString());
			}
		}
		if (root.contains("track_artist_id")) {
			QJsonArray _track_artist_id = root["track_artist_id"].toArray();
			for (int i = 0; i < _track_artist_id.size(); ++i) {
				pl.track_artist_id.push_back(_track_artist_id[i].toString().toStdString());
			}
		}
		if (root.contains("album_img")) {
			QJsonArray _album_img = root["album_img"].toArray();
			pl.album_img.large_image = _album_img[0].toString().toStdString();
			pl.album_img.medium_image = _album_img[1].toString().toStdString();
			pl.album_img.small_image = _album_img[2].toString().toStdString();
		}
		if (root.contains("artist_img")) {
			QJsonArray _artist_img = root["artist_img"].toArray();
			pl.artist_img.large_image = _artist_img[0].toString().toStdString();
			pl.artist_img.medium_image = _artist_img[1].toString().toStdString();
			pl.artist_img.small_image = _artist_img[2].toString().toStdString();
		}
		return pl;
	}
	inline bool operator==(const PlaylistElement& rhs) {
		return this->track_id == rhs.track_id && this->album_id == rhs.album_id && this->artist_id == rhs.artist_id;
	}
	inline bool operator!=(const PlaylistElement& rhs) { return !(*this == rhs); }
	inline bool operator==(PlaylistElement& rhs) {
		return this->track_id == rhs.track_id && this->album_id == rhs.album_id && this->artist_id == rhs.artist_id;
	}
	inline bool operator!=(PlaylistElement& rhs) { return !(*this == rhs); }
};

