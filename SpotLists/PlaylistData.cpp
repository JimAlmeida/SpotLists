#include "PlaylistData.h"

//Public Functions
PlaylistData::PlaylistData()
{
}

PlaylistData::PlaylistData(std::vector<PlaylistElement>& _elements, std::string plist_name)
{
	playlist_name = plist_name;
	loadData(_elements);
}

void PlaylistData::loadData(std::vector<PlaylistElement>& _elements) {
	elements = _elements;
}

PlaylistElement& PlaylistData::operator[](int i) {
	return elements[i];
}

size_t PlaylistData::size() {
	return elements.size();
}

PlaylistData PlaylistData::readPlaylist(const char* filename) {
	//takes filename without extension
	QByteArray raw_data = PlaylistData::readFromDisk(filename);
	QJsonDocument decoded_json_data = PlaylistData::fromBase64(raw_data);
	QJsonObject root = decoded_json_data.object();
	QJsonArray items = root["items"].toArray();

	std::vector<PlaylistElement> _elements;
	for (auto& item : items) {
		_elements.push_back(PlaylistElement::fromJson(item.toObject()));
	}

	return PlaylistData(_elements);
}

bool PlaylistData::savePlaylist(const char* filename, PlaylistData& playlist) {
	//Assemble JSON
	QJsonDocument json_data = PlaylistData::toJson(playlist);
	//Convert JSON String to BASE64 encoded string
	QByteArray encoded_string = PlaylistData::toBase64(json_data);
	//Save BASE64 encoded string to file
	return PlaylistData::saveToDisk(filename, encoded_string);
}

//Private Functions
QJsonDocument PlaylistData::toJson(const PlaylistData& plist) {
	QJsonObject root;
	QJsonArray playlist_items;

	for (auto& e : plist.elements) {
		playlist_items.push_back(PlaylistElement::toJson(e));
	}

	root.insert("playlist_name", plist.playlist_name.c_str());
	root.insert("items", playlist_items);

	return QJsonDocument(root);
}

QByteArray PlaylistData::toBase64(QJsonDocument& json_data) {
	return json_data.toJson().toBase64();
}

bool PlaylistData::saveToDisk(const char* filename, QByteArray& data) {
	//takes filename without extension
	//adds extension belo

	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	QTextStream out(&file);
	out << data;

	file.close();
	return true;
}

QByteArray PlaylistData::readFromDisk(const char* filename) {
	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return "";

	QTextStream in(&file);
	QString contents = in.readAll();
	file.close();

	return contents.toStdString().c_str();
}

QJsonDocument PlaylistData::fromBase64(QByteArray& file_data) {
	return QJsonDocument::fromJson(QByteArray::fromBase64(file_data));
}

PlaylistData PlaylistData::fromJson(QJsonDocument& data) {
	QJsonObject root = data.object();
	QJsonArray items = root["items"].toArray();

	std::string playlist_name = root["playlist_name"].toString().toStdString();

	std::vector<PlaylistElement> _elements;
	for (auto& item : items) {
		_elements.push_back(PlaylistElement::fromJson(item.toObject()));
	}

	return PlaylistData(_elements, playlist_name);
}

void PlaylistData::addTrack(PlaylistElement track_data) {
	qDebug() << "PlaylistData::addTrack()";
	qDebug() << track_data.display().c_str();
	auto it = std::find(elements.begin(), elements.end(), track_data);
	if (it == elements.end()) { elements.push_back(track_data); }
	
}

void PlaylistData::removeTrack(PlaylistElement track_data) {
	qDebug() << "PlaylistData::removeTrack()";
	qDebug() << track_data.display().c_str();
	//iterator-based item removal
	auto it = std::find(elements.begin(), elements.end(), track_data); 
	if (it!=elements.end()){elements.erase(it);}
}
