#include "MoviesGUI.h"
#include <QtWidgets\qmessagebox.h>
#include <qdebug.h>
#include <QDesktopServices.h>
#include <qurl.h>
using namespace std;

MoviesGUI::MoviesGUI(Service& service, Mylist_table_model* model, QWidget* parent) : QMainWindow(parent), model{ model }, service{ service }
{
	ui.setupUi(this);
	this->populate_list();
	this->connect_signals_and_slots();
	this->secondary_window = new Secondary_window{ this->model };
}

void MoviesGUI::connect_signals_and_slots()
{
	QObject::connect(this->ui.delete_button, &QPushButton::clicked, this, &MoviesGUI::delete_movie);
	QObject::connect(this->ui.add_button, &QPushButton::clicked, this, &MoviesGUI::add_movie);
	QObject::connect(this->ui.movies_list_widget, &QListWidget::itemSelectionChanged, [this]() {
		int selected_index = this->get_selected_index();
		if (selected_index < 0)
			return;
		Movie selected_movie = this->service.get_all()[selected_index];
		this->ui.title_line_edit->setText(QString::fromStdString(selected_movie.get_title()));
		this->ui.genre_line_edit->setText(QString::fromStdString(selected_movie.get_genre()));
		this->ui.year_of_release_line_edit->setText(QString::fromStdString(to_string(selected_movie.get_year_of_release())));
		this->ui.number_of_likes_line_edit->setText(QString::fromStdString(to_string(selected_movie.get_number_of_likes())));
		this->ui.trailer_line_edit->setText(QString::fromStdString(selected_movie.get_trailer()));
		});
	QObject::connect(this->ui.update_button, &QPushButton::clicked, this, &MoviesGUI::update_movie);
	QObject::connect(this->ui.next_button, &QPushButton::clicked, this, &MoviesGUI::next_movie);
	QObject::connect(this->ui.save_button, &QPushButton::clicked, this, &MoviesGUI::save_movie);
	QObject::connect(this->ui.open_button, &QPushButton::clicked, this, &MoviesGUI::open_watchlist);
	QObject::connect(this->ui.filter_button, &QPushButton::clicked, this, &MoviesGUI::filter_watchlist);
	QObject::connect(this->ui.undo_button, &QPushButton::clicked, this, &MoviesGUI::undo);
	QObject::connect(this->ui.redo_button, &QPushButton::clicked, this, &MoviesGUI::redo);

	QShortcut* shortcut_undo = new QShortcut(QKeySequence("Ctrl+Z"), this);
	QObject::connect(shortcut_undo, &QShortcut::activated, this, &MoviesGUI::undo);
	QShortcut* shortcut_redo = new QShortcut(QKeySequence("Ctrl+Y"), this);
	QObject::connect(shortcut_redo, &QShortcut::activated, this, &MoviesGUI::redo);

	QObject::connect(this->ui.new_window_button, &QPushButton::clicked, this, [this]() {this->secondary_window->show(); });
}

void MoviesGUI::populate_list()
{
	this->ui.movies_list_widget->clear();
	vector<Movie> movies = this->service.get_all();
	for (Movie& movie : movies) {
		this->ui.movies_list_widget->addItem(QString::fromStdString(movie.print_format()));
	}
}

int MoviesGUI::get_selected_index() const
{
	QModelIndexList selected_indexes = this->ui.movies_list_widget->selectionModel()->selectedIndexes();
	if (selected_indexes.size() == 0)
	{
		this->ui.title_line_edit->clear();
		this->ui.genre_line_edit->clear();
		this->ui.year_of_release_line_edit->clear();
		this->ui.number_of_likes_line_edit->clear();
		this->ui.trailer_line_edit->clear();
		return -1;
	}

	return selected_indexes.at(0).row();
}

void MoviesGUI::add_movie()
{
	string title = this->ui.title_line_edit->text().toStdString();
	string genre = this->ui.genre_line_edit->text().toStdString();
	int year_of_release = stoi(this->ui.year_of_release_line_edit->text().toStdString());
	int number_of_likes = stoi(this->ui.number_of_likes_line_edit->text().toStdString());
	string trailer = this->ui.trailer_line_edit->text().toStdString();
	try {
		this->service.service_add_movie(title, genre, year_of_release, number_of_likes, trailer);
	}
	catch (exception& exception) {
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	this->populate_list();
	int last_element = this->service.get_all().size() - 1;
	this->ui.movies_list_widget->setCurrentRow(last_element);
}

void MoviesGUI::delete_movie()
{
	string title = this->ui.title_line_edit->text().toStdString();
	try {
		this->service.service_delete_movie(title);
	}
	catch (exception& exception) {
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	this->populate_list();
}

void MoviesGUI::update_movie()
{
	string title = this->ui.title_line_edit->text().toStdString();
	string genre = this->ui.genre_line_edit->text().toStdString();
	int year_of_release = stoi(this->ui.year_of_release_line_edit->text().toStdString());
	int number_of_likes = stoi(this->ui.number_of_likes_line_edit->text().toStdString());
	string trailer = this->ui.trailer_line_edit->text().toStdString();
	try {
		this->service.service_update_movie(title, genre, year_of_release, number_of_likes, trailer);
	}
	catch (exception& exception) {
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	this->populate_list();
}

void MoviesGUI::next_movie()
{
	Movie movie = this->service.service_get_next_movie_for_printing();
	this->ui.title_line_edit_user->setText(QString::fromStdString(movie.get_title()));
	this->ui.genre_line_edit_user->setText(QString::fromStdString(movie.get_genre()));
	this->ui.year_of_release_line_edit_user->setText(QString::fromStdString(to_string(movie.get_year_of_release())));
	this->ui.number_of_likes_line_edit_user->setText(QString::fromStdString(to_string(movie.get_number_of_likes())));
	this->ui.trailer_line_edit_user->setText(QString::fromStdString(movie.get_trailer()));
}

void MoviesGUI::save_movie()
{
	string title = this->ui.title_line_edit_user->text().toStdString();
	try {
		this->service.service_add_to_watchlist(title);
	}
	catch(exception& exception){
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	vector<Movie> movies = this->service.get_all_movies_from_watchlist();
	this->ui.watchlist_list_widget->clear();
	for (Movie& movie : movies) {
		this->ui.watchlist_list_widget->addItem(QString::fromStdString(movie.print_format()));
	}
	this->model->layoutChanged();
}

void MoviesGUI::open_watchlist()
{
	string filename = this->service.get_filename();
	QDesktopServices::openUrl(QUrl(QString::fromStdString(filename), QUrl::TolerantMode));
}

void MoviesGUI::filter_watchlist()
{
	string genre = this->ui.filter_genre_line_edit->text().toStdString();
	int number_of_likes = stoi(this->ui.filter_number_of_likes_line_edit->text().toStdString());
	vector<Movie> movies = this->service.get_filtered_movies(genre, number_of_likes);	
	this->ui.filtered_list_widget->clear();
	for (Movie movie : movies)
		this->ui.filtered_list_widget->addItem(QString::fromStdString(movie.print_format()));
}

void MoviesGUI::undo()
{
	try {
		this->service.service_undo();
	}
	catch (const exception& exception) {
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	this->populate_list();
}

void MoviesGUI::redo()
{
	try {
		this->service.service_redo();
	}
	catch (const exception& exception) {
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	this->populate_list();
}
