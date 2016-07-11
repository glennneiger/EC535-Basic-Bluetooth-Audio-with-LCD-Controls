#include <gui.h>

// Constructor to generate the GUI
gui::gui(QWidget *parent) : QWidget(parent)
{
	// Create the songs list widget
	songs = new QListWidget(this);

	// Search the directory for songs
	dirName = "/media/card/project/mp3s/";
	dir.setPath(dirName);
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	dir.setSorting(QDir::Name);
	songList = new QStringList();
	*songList = dir.entryList();

	// Add all the song names into the songs list widget
	int songNum = songList->size();
	for(int i = 0; i < songNum; i++)
	{
		QListWidgetItem *item = new QListWidgetItem();
		item->setText((*songList)[i]);
		qDebug() << (*songList)[i];
		songs->insertItem(i,item);
	}

	// Create a new grid layout for widgets to be added to
	layout = new QGridLayout(this);

	// Create play button and connect it to a button handler
	play = new QPushButton("Play", this);
	connect(play, SIGNAL(clicked()), this, SLOT(play_handler()));

	// Create pause button and connect it to a button handler
	pause = new QPushButton("Pause", this);
	connect(pause, SIGNAL(clicked()), this, SLOT(pause_handler()));

	// Create start button and connect it to a button handler
	start = new QPushButton("Start", this);
	connect(start, SIGNAL(clicked()), this, SLOT(start_handler()));

	// Create stop button and connect it to a button handler
	stop = new QPushButton("Stop", this);
	connect(stop, SIGNAL(clicked()), this, SLOT(stop_handler()));

	// Add all widgets to the layout and set the layout
	layout->addWidget(songs, 0, 0, -1, 1);
	layout->addWidget(play, 1, 1);
	layout->addWidget(pause, 2, 1);
	layout->addWidget(start, 0, 1);
	layout->addWidget(stop, 3, 1);
	this->setLayout(layout);

	state = 0;
}

// Play button handler
void gui::play_handler()
{
	// If  a song is paused, play it and set state to playing
	if(state == 2)
	{
		int status = system("ash music_control.sh -g");
		state = 1;
	}
}

// Pause button handler
void gui::pause_handler()
{
	// If a song is playing, pause it and set state to paused
	if(state == 1)
	{
		int status = system("ash music_control.sh -p");
		state = 2;
	}
}

// Start button handler
void gui::start_handler()
{
	// If there is no song playing, start a song and set the state to playing
	if(state==0)
	{
		std::string file = "ash /media/card/project/scripts/music_control.sh -s /media/card/project/mp3s/" + songs->currentItem()->text().toStdString();
		int status = system(file.c_str());
		state = 1;
	}
	// If there is a song playing, stop it first, then start the new one
	else
	{
		stop_handler();
		start_handler();
	}
}

// Stop button handler
void gui::stop_handler()
{
	// If there is a paused song, play it 
	if(state == 2)
	{
		play_handler();
	}
	// Then if there is a song playing, stop it and set state to stopped
	if(state!=0)
	{
		int status = system("ash music_control.sh -k");
		state = 0;
	}
}
