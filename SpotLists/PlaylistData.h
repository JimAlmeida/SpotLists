#pragma once

#pragma once
#include "PlaylistElement.h"
#include <vector>
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>

class PlaylistData {
private:
	std::vector<PlaylistElement> elements;
	std::string playlist_name = "My Playlist";

	static QJsonDocument toJson(const PlaylistData& plist);
	static QByteArray toBase64(QJsonDocument& json_data);
	static bool saveToDisk(const char* filename, QByteArray& data);

	static QByteArray readFromDisk(const char* filename);
	static QJsonDocument fromBase64(QByteArray& file_data);
	static PlaylistData fromJson(QJsonDocument& data);

public:
	PlaylistData();
	PlaylistData(std::vector<PlaylistElement>& _elements, std::string plist_name="My Playlist");

	inline std::string getPlaylistName() { return playlist_name; }
	inline void setPlaylistName(std::string p_name) { playlist_name = p_name; }

	static PlaylistData readPlaylist(const char* filename);
	static bool savePlaylist(const char* filename, PlaylistData& playlist);

	void loadData(std::vector<PlaylistElement>& _elements);
	PlaylistElement& operator[](int i);
	size_t size();
};