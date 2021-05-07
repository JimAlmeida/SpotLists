#include "SearchBar.h"

TopBar::TopBar(QWidget* parent): QToolBar(parent)
{
	search_box = new QLineEdit();
	search_by_track = new QRadioButton("Track");
	search_by_artist = new QRadioButton("Artist");
	search_label = new QLabel("Search");
	query_label = new QLabel("Query Options");
	std_label = "Search artists and tracks with this search box...";

	open_file = new QToolButton(this);
	save_file = new QToolButton(this);
	navigate_bckwd = new QToolButton(this);
	navigate_fwd = new QToolButton(this);

	buildLayout();
	connections();
	setCustomStyle();
}

void TopBar::buildLayout() {
	this->addWidget(open_file);
	this->addWidget(save_file);
	this->addWidget(navigate_bckwd);
	this->addWidget(navigate_fwd);

	this->addSeparator();

	this->addWidget(search_label);
	this->addWidget(search_box);

}
void TopBar::connections() {
	//When the user presses enter inside the search box, the signal startSearch is emitted with the current text inside the search box.
	QObject::connect(search_box, &QLineEdit::returnPressed, this, [&]() {emit startSearch(search_box->text().toStdString()); });
	QObject::connect(search_box, &QLineEdit::textEdited, this, &TopBar::textEdited);
	QObject::connect(open_file, &QToolButton::clicked, this, [&]() {emit openFile(); });
	QObject::connect(save_file, &QToolButton::clicked, this, [&]() {emit saveFile(); });
	QObject::connect(navigate_bckwd, &QToolButton::clicked, this, [&]() {emit goBack(); });
	QObject::connect(navigate_fwd, &QToolButton::clicked, this, [&]() {emit goForward(); });
}
void TopBar::setCustomStyle() {
	setDefaultSearchBoxStyle();
	open_file->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
	save_file->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
	navigate_fwd->setIcon(style()->standardIcon(QStyle::SP_ArrowForward));
	navigate_bckwd->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));

	this->setMinimumSize(this->sizeHint());
	qDebug() << this->sizeHint();
}

void TopBar::textEdited(QString text) {
	search_box->setStyleSheet("color: black");
}

void TopBar::setDefaultSearchBoxStyle() {
	search_box->setText(std_label);
	search_box->setStyleSheet("color: grey");
}