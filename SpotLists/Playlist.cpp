#include "Playlist.h"

//Public Functions
Playlist::Playlist(QWidget* parent): QWidget(parent)
{
}

Playlist::Playlist(PlaylistData& _elements, QWidget* parent): QWidget(parent)
{
	loadData(_elements);
}

void Playlist::loadData(PlaylistData& _elements) {
	data = _elements;
	disconnectAll();
	clearLayout();
	clearElements();
	for (int i = 0; i < _elements.size(); ++i) {
		playlist.push_back(new PlaylistElementGUI(data[i], this));
	}
	connections();
}

void Playlist::clearElements() {
	for (int i = 0; i < playlist.size(); ++i) {
		delete playlist[i];
	}
	playlist.clear();
}

PlaylistElementGUI* Playlist::operator[](int i) {
	return playlist[i];
}

size_t Playlist::size() {
	return data.size();
}

//Private Functions
void Playlist::connections() {
	for (auto& e : playlist) {
		QObject::connect(e, &PlaylistElementGUI::onSelected, this, [=](PlaylistElement data) {emit elementSelected(data); });
	}
}

void Playlist::disconnectAll() {
	for (auto& e : playlist) {
		QObject::disconnect(e, &PlaylistElementGUI::onSelected, nullptr, nullptr);
	} 
}

void Playlist::buildListLayout() {
	QGridLayout* base_layout = new QGridLayout();
	for (int i = 0; i < playlist.size(); ++i) {
		playlist[i]->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
		base_layout->addWidget(playlist[i], i, 0, Qt::AlignLeft);
	}
	QWidget* spacer = new QWidget(this);
	spacer->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
	base_layout->addWidget(spacer, playlist.size(), 0);
	
	this->setLayout(base_layout);
}

void Playlist::clearLayout() {
	if (this->layout()) {
		for (int i = 0; i < playlist.size(); ++i) {
			this->layout()->removeWidget(playlist[i]);
		}
		delete this->layout();
	}
}

void Playlist::buildGridLayout(int n_cols) {
	QGridLayout* base_layout = new QGridLayout();
	if (n_cols <= 1) {
		buildListLayout();
	}
	else {
		int i = 0;
		size_t p_size = playlist.size();

		int n_rows = p_size % n_cols == 0 ? p_size / n_cols : p_size / n_cols + 1;
		for (int row = 0; row < n_rows; ++row) {
			for (int col = 0; col < n_cols; ++col) {
				if (i < p_size) {
					base_layout->addWidget(playlist[i], row, col, Qt::AlignLeft);
					++i;
				}
			}
		}

		QWidget* spacer = new QWidget(this);
		spacer->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
		base_layout->addWidget(spacer, n_rows, 0, 1, n_cols);

		this->setLayout(base_layout);
	}
}

void Playlist::addTrack() {

}
void Playlist::removeTrack() {

}