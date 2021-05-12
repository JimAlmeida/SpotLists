#pragma once
#ifndef PLAYLISTDATA_H
#define PLAYLISTDATA_H

#include <vector>
#include <algorithm>

#include <QFile>
#include <QTextStream>

#include "PlaylistElement.h"

typedef std::vector<PlaylistElement>::const_iterator const_iterator;

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

	void addTrack(PlaylistElement track_data);
	void removeTrack(PlaylistElement track_data);

	inline std::string getPlaylistName() { return playlist_name; }
	inline void setPlaylistName(std::string p_name) { playlist_name = p_name; }

	static PlaylistData readPlaylist(const char* filename);
	static bool savePlaylist(const char* filename, PlaylistData& playlist);

	void loadData(std::vector<PlaylistElement>& _elements);
	int findTrack(std::string track_id);

	//functions to give STL Vector-like behaviour
	inline const_iterator begin() { return elements.begin();}
	inline const_iterator end() { return elements.end(); }
	inline void erase(const_iterator pos) { elements.erase(pos); }
	PlaylistElement& operator[](int i);
	size_t size();
};
#endif