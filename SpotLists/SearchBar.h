#pragma once
#ifndef TOPBAR_H
#define TOPBAR_H

#include <string>

#include <QWidget>
#include <QMediaPlayer>
#include <QToolButton>
#include <QLabel>
#include <QStyle>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QToolBar>


class TopBar: public QToolBar {
	Q_OBJECT;
private:
	QLineEdit* search_box = nullptr;
	QLabel* logo_label = nullptr;
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
};
#endif