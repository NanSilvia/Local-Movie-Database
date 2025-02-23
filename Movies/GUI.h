#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
class GUI : public QWidget
{
private:
	Service& service;

	QListWidget* movie_list_widget;
	QLineEdit* title_line_edit, *genre_line_edit, *year_of_release_line_edit, *number_of_likes_line_edit, *trailer_line_edit;
	QPushButton* add_button, * delete_button, * update_button, * filter_button;

public:
	GUI(Service& service);

private:
	void initializeGUI();
	void populate_list();
	void connect_signals_and_slots();
	
	int get_selected_index() const;
	void add_movie();
	void delete_movie();
};

