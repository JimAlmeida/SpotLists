#pragma once
#include <qwidget.h>
#include <qmediaplayer.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <qslider.h>
#include <qstyle.h>
#include <qboxlayout.h>
#include <qgridlayout.h>
#include <qlineedit.h>
#include <qtoolbar.h>
#include <string>

class TopBar: public QToolBar {
	Q_OBJECT;
private:
	QLineEdit* search_box = nullptr;
	QRadioButton* search_by_track = nullptr;
	QRadioButton* search_by_artist = nullptr;
	QLabel* search_label = nullptr;
	QLabel* query_label = nullptr;
	QString std_label;

	QToolButton* open_file = nullptr;
	QToolButton* save_file = nullptr;
	QToolButton* navigate_bckwd = nullptr;
	QToolButton* navigate_fwd = nullptr;

	void setDefaultSearchBoxStyle();
	void buildLayout();
	void connections();
	void setCustomStyle();
public:
	TopBar(QWidget* parent = nullptr);

signals:
	void startSearch(std::string query);
	void openFile();
	void saveFile();
	void goBack();
	void goForward();

public slots:
	void textEdited(QString text);
};