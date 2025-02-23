#include "GUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <vector>
#include <string>
#include <qmessagebox.h>
#include <exception>
using namespace std;

GUI::GUI(Service& service) : service{ service }
{
	this->initializeGUI();
	this->populate_list();
	this->connect_signals_and_slots();
}

void GUI::initializeGUI()
{
	this->movie_list_widget = new QListWidget{};
	this->title_line_edit = new QLineEdit{};
	this->genre_line_edit = new QLineEdit{};
	this->year_of_release_line_edit = new QLineEdit{};
	this->number_of_likes_line_edit = new QLineEdit{};
	this->trailer_line_edit = new QLineEdit{};
	this->add_button = new QPushButton{"Add"};
	this->delete_button = new QPushButton{"Delete"};
	this->update_button = new QPushButton{"Update"};
	this->filter_button = new QPushButton{"Filter"};
	
	QVBoxLayout* main_layout = new QVBoxLayout{ this };
	
	main_layout->addWidget(this->movie_list_widget);
	
	QFormLayout* movie_details_layout = new QFormLayout{};
	movie_details_layout->addRow("Title", this->title_line_edit);
	movie_details_layout->addRow("Genre",this->genre_line_edit );
	movie_details_layout->addRow("Year of release", this->year_of_release_line_edit);
	movie_details_layout->addRow("Number of likes", this->number_of_likes_line_edit);
	movie_details_layout->addRow("Trailer", this->trailer_line_edit);
	
	main_layout->addLayout(movie_details_layout);
	
	QGridLayout* buttons_layout = new QGridLayout{};
	buttons_layout->addWidget(this->add_button, 0, 0);
	buttons_layout->addWidget(this->delete_button, 0, 1);
	buttons_layout->addWidget(this->update_button, 0, 2);
	buttons_layout->addWidget(this->filter_button, 1, 1);
	main_layout->addLayout(buttons_layout);

}

void GUI::populate_list()
{
	this->movie_list_widget->clear();
	vector<Movie> movies = this->service.get_all();
	for (Movie& movie : movies) {
		this->movie_list_widget->addItem(QString::fromStdString(movie.print_format()));
	}
}

void GUI::connect_signals_and_slots()
{
	QObject::connect(this->movie_list_widget, &QListWidget::itemSelectionChanged, [this]() {
			int selected_index = this->get_selected_index();
			if (selected_index < 0)
				return;
			Movie selected_movie = this->service.get_all()[selected_index];
			this->title_line_edit->setText(QString::fromStdString(selected_movie.get_title()));
			this->genre_line_edit->setText(QString::fromStdString(selected_movie.get_genre()));
			this->year_of_release_line_edit->setText(QString::fromStdString(to_string(selected_movie.get_year_of_release())));
			this->number_of_likes_line_edit->setText(QString::fromStdString(to_string(selected_movie.get_number_of_likes())));
			this->trailer_line_edit->setText(QString::fromStdString(selected_movie.get_trailer()));
		});
	QObject::connect(this->add_button,&QPushButton::clicked, this, &GUI::add_movie);
	QObject::connect(this->delete_button, &QPushButton::clicked, this, &GUI::delete_movie);
}

int GUI::get_selected_index() const
{
	QModelIndexList selected_indexes = this->movie_list_widget->selectionModel()->selectedIndexes();
	if (selected_indexes.size() == 0)
	{
		this->title_line_edit->clear();
		this->genre_line_edit->clear();
		this->year_of_release_line_edit->clear();
		this->number_of_likes_line_edit->clear();
		this->trailer_line_edit->clear();
		return -1;
	}

	return selected_indexes.at(0).row();
}

void GUI::add_movie()
{
	string title = this->title_line_edit->text().toStdString();
	string genre = this->genre_line_edit->text().toStdString();
	int year_of_release = stoi(this->year_of_release_line_edit->text().toStdString());
	int number_of_likes = stoi(this->number_of_likes_line_edit->text().toStdString());
	string trailer = this->trailer_line_edit->text().toStdString();
	try {
		this->service.service_add_movie(title, genre, year_of_release, number_of_likes, trailer);
	}
	catch (exception& exception) {
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	this->populate_list();
	int last_element = this->service.get_all().size() - 1;
	this->movie_list_widget->setCurrentRow(last_element);
}

void GUI::delete_movie()
{
	string title = this->title_line_edit->text().toStdString();
	try {
		this->service.service_delete_movie(title);
	}
	catch (exception& exception) {
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
	this->populate_list();
}

