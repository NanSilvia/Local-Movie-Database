#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MoviesGUI.h"
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qshortcut.h>
#include "Secondary_window.h"
#include "Mylist_table_model.h"

class MoviesGUI : public QMainWindow
{
	Q_OBJECT

public:
	MoviesGUI(Service& service, Mylist_table_model* model, QWidget *parent = Q_NULLPTR);

private:
	Service& service;
	Ui::MoviesGUIClass ui;
	Secondary_window* secondary_window;
	Mylist_table_model* model;

	void connect_signals_and_slots();

	void populate_list();
	int get_selected_index() const;
	void add_movie();
	void delete_movie();
	void update_movie();
	void next_movie();
	void save_movie();
	void open_watchlist();
	void filter_watchlist();
	void undo();
	void redo();
};
