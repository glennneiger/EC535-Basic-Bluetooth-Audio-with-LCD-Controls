#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QGridLayout>
#include <stdlib.h>
#include <QDir>
#include <QString>
#include <QStringList>
#include <string>

// gui class - generates a user interface on the gumstix touch screen
class gui;

class gui : public QWidget
{
	Q_OBJECT

public:
	gui(QWidget *parent = 0);

// Declare button handlers
private slots:
	void play_handler();
	void pause_handler();
	void start_handler();
	void stop_handler();

private:
	// Declare widgets to be displayed
	QGridLayout* layout;
	QListWidget* songs;
	QStringList* songList;
	QPushButton* play;
	QPushButton* pause;
	QPushButton* start;
	QPushButton* stop;

	// Variables for song name retrieval and script calls
	int state;
	QString dirName;
	QDir dir;

};



#endif
