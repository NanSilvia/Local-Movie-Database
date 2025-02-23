#include "Service.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>


void Service::service_add_movie(string title, string genre, int year_of_release, int number_of_likes, string trailer)
{
	Movie movie{ title, genre, year_of_release, number_of_likes, trailer };
	this->validator->validate_movie(movie);
	this->repository->add_entity(movie);

	Action* action = new Action_add{ this->repository, movie };
	this->undo_actions.push(action);
	while (!this->redo_actions.empty())
		this->redo_actions.pop();
}

void Service::service_delete_movie(string title)
{
	Movie movie_key{ title,"",0,0,"" };
	Movie movie = this->repository->get_by_name(title);
	this->repository->delete_entity(movie_key);

	Action* action = new Action_delete{ this->repository, movie };
	this->undo_actions.push(action);
	while (!this->redo_actions.empty())
		this->redo_actions.pop();
}

void Service::service_update_movie(string title, string genre, int year_of_release, int number_of_likes, string trailer)
{
	Movie new_movie{ title, genre, year_of_release, number_of_likes, trailer };
	this->validator->validate_movie(new_movie);
	Movie old_movie = this->repository->get_by_name(title);
	this->repository->update_entity(new_movie);

	Action* action = new Action_update{ this->repository, old_movie };
	this->undo_actions.push(action);
	while (!this->redo_actions.empty())
		this->redo_actions.pop();
}

void Service::service_add_to_watchlist(string name)
{
	this->watchlist->add_entity(this->repository->get_by_name(name));
}

Movie Service::service_get_first_movie_for_printing()
{
	this->current_position = 0;
	return this->repository->get_all()[this->current_position];
}

Movie Service::service_get_next_movie_for_printing()
{
	Movie current_movie;
	if (this->current_position != this->repository->get_length()) {
		current_movie = this->repository->get_all()[this->current_position];
		this->current_position++;
	}
	else {
		current_position = 0;
		current_movie = this->repository->get_all()[this->current_position];
		this->current_position++;
	}
	return current_movie;
}

std::vector<Movie> Service::get_all()
{
	return this->repository->get_all();
}

std::vector<Movie> Service::get_all_movies_from_watchlist()
{
	return this->watchlist->get_all();
}

std::vector<Movie> Service::get_filtered_movies(string genre, int minimum_number_of_likes)
{
	std::vector<Movie> movies =  this->repository->get_all();
	std::vector<Movie> filtered_movies(movies.size());
	auto iterator = std::copy_if(movies.begin(), movies.end(), filtered_movies.begin(), [genre, minimum_number_of_likes](Movie movie) {return movie.get_genre() == genre && minimum_number_of_likes < movie.get_number_of_likes(); });
	filtered_movies.resize(std::distance(filtered_movies.begin(), iterator));
	return filtered_movies;
}

void Service::initialize_repository(string filename)
{
	this->repository = new File_repository{ filename };
}

void Service::initialize_watchlist(string filename)
{
	if (filename.substr(filename.find_last_of(".") + 1) == "html") {
		ofstream file(filename);
		file << "";
		file.close();
		this->watchlist = new HTML_repository(filename);
	}
	else if (filename.substr(filename.find_last_of(".") + 1) == "csv")
		this->watchlist = new File_repository(filename);
}

string Service::get_filename()
{
	return this->watchlist->get_filename();
}

void Service::service_undo()
{
	if (this->undo_actions.empty())
		throw exception("No more undos.\n");
	Action* action = this->undo_actions.top();
	this->undo_actions.pop();
	this->redo_actions.push(action);
	action->execute_undo();
}

void Service::service_redo()
{
	if (this->redo_actions.empty())
		throw exception("No more redos.\n");
	Action* action = this->redo_actions.top();
	this->redo_actions.pop();
	this->undo_actions.push(action);
	action->execute_redo();
}
