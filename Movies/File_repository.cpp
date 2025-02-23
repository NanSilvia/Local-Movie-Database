#include "File_repository.h"
#include <fstream>
#include <iostream>
#include "custom_exceptions.h"

vector<Movie> File_repository::read_all_from_file()
{
	ifstream file{ this->filename };
	vector<Movie> movies;
	Movie movie{};
	while (file >> movie) {
		movies.push_back(movie);
	}
	file.close();
	return movies;
}

void File_repository::write_all_to_file(vector<Movie> movies)
{
	ofstream file{ this->filename };
	for (Movie movie : movies)
		file << movie;
	file.close();
}

int File_repository::get_length() 
{
	return this->read_all_from_file().size();
}

void File_repository::add_entity(Movie movie)
{
	vector<Movie> movies = this->read_all_from_file();
	if (find(movies.begin(), movies.end(), movie) != movies.end())
		throw Repository_duplicate_exception("Duplicate element!\n");
	movies.push_back(movie);
	this->write_all_to_file(movies);
	
}

void File_repository::delete_entity(Movie movie_key)
{
	vector<Movie> movies = this->read_all_from_file();
	auto iterator = std::find(movies.begin(), movies.end(), movie_key);
	if (iterator != movies.end())
		movies.erase(iterator);
	else
		throw Repository_entity_not_found_exception("inexistent movie\n");
	this->write_all_to_file(movies);
}

void File_repository::update_entity(Movie new_movie)
{
	vector<Movie> movies = this->read_all_from_file();
	auto iterator = std::find(movies.begin(), movies.end(), new_movie);
	if (iterator != movies.end())
		*iterator = new_movie;
	this->write_all_to_file(movies);
}

Movie File_repository::get_by_name(string name)
{
	vector<Movie> movies = this->read_all_from_file();
	auto iterator = std::find_if(movies.begin(), movies.end(), [name](Movie movie) {return movie.get_title() == name; });
	if (iterator != movies.end())
		return *iterator;}

std::vector<Movie> File_repository::get_all()
{
	return this->read_all_from_file();
}

string File_repository::get_filename()
{
	return this->filename;
}
