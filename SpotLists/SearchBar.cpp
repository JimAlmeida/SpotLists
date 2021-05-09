#include "SearchBar.h"

TopBar::TopBar(QWidget* parent): QToolBar(parent)
{
	search_box = new QLineEdit();
	search_by_track = new QRadioButton("Track");
	search_by_artist = new QRadioButton("Artist");
	std_label = "Search artists and tracks with this search box...";
	logo_label = new QLabel(this);
	open_file = new QToolButton(this);
	save_file = new QToolButton(this);
	navigate_bckwd = new QToolButton(this);
	navigate_fwd = new QToolButton(this);

	buildLayout();
	connections();
	setCustomStyle();
}

void TopBar::buildLayout() {
	this->addWidget(logo_label);

	this->addSeparator();

	this->addWidget(open_file);
	this->addWidget(save_file);
	this->addWidget(navigate_bckwd);
	this->addWidget(navigate_fwd);

	this->addSeparator();

	this->addWidget(search_box);

}
void TopBar::connections() {
	//When the user presses enter inside the search box, the signal startSearch is emitted with the current text inside the search box.
	QObject::connect(search_box, &QLineEdit::returnPressed, this, [&]() {emit startSearch(search_box->text().toStdString()); });
	QObject::connect(open_file, &QToolButton::clicked, this, [&]() {emit openFile(); });
	QObject::connect(save_file, &QToolButton::clicked, this, [&]() {emit saveFile(); });
	QObject::connect(navigate_bckwd, &QToolButton::clicked, this, [&]() {emit goBack(); });
	QObject::connect(navigate_fwd, &QToolButton::clicked, this, [&]() {emit goForward(); });
}
void TopBar::setCustomStyle() {
	setDefaultSearchBoxStyle();
	open_file->setIcon(QIcon("images/open.png"));
	save_file->setIcon(QIcon("images/save.png"));
	navigate_fwd->setIcon(QIcon("images/forward.png"));
	navigate_bckwd->setIcon(QIcon("images/back.png"));
	//open_file->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
	//save_file->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
	//navigate_fwd->setIcon(style()->standardIcon(QStyle::SP_ArrowForward));
	//navigate_bckwd->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));

	QSize recommended_size = this->sizeHint();
	QSize top_bar_size = QSize(recommended_size.width(), recommended_size.height() * 1.4);
	this->setMinimumSize(top_bar_size);
	search_box->setMinimumHeight(recommended_size.height()*0.8);
	qDebug() << search_box->height();

	logo_label->setPixmap(QPixmap("images/Logo.png").scaledToHeight(recommended_size.height(), Qt::SmoothTransformation));
}

void TopBar::setDefaultSearchBoxStyle() {
	search_box->setText(std_label);
	search_box->setStyleSheet("border: 2px solid white; border-radius: 10px; color: white; padding-left: 3px");
	
}