#include "Repository.h"
#include <algorithm>
#include <vector> 
#include "custom_exceptions.h"
Repository::Repository()
{
}

int Repository::get_length() 
{
	return this->entities.size();
}

void Repository::add_entity(Movie movie)
{
	if (find(this->entities.begin(), this->entities.end(), movie) != this->entities.end())
		throw Repository_duplicate_exception("Duplicate element!\n");
	this->entities.push_back(movie);
}

void Repository::delete_entity(Movie movie_key) 
{
	auto iterator = std::find(this->entities.begin(), this->entities.end(), movie_key);
	if (iterator != this->entities.end())
		this->entities.erase(iterator);
	else {
		throw Repository_entity_not_found_exception("inexistent movie");
	}
}

void Repository::update_entity(Movie new_movie)
{
	auto iterator = std::find(this->entities.begin(), this->entities.end(), new_movie);
	if (iterator != this->entities.end())
		*iterator = new_movie;
}

Movie Repository::get_by_name(string name)
{
	auto iterator = std::find_if(this->entities.begin(), this->entities.end(), [name](Movie movie) {return movie.get_title() == name; });
	if (iterator != this->entities.end())
		return *iterator;}

std::vector<Movie> Repository::get_all()
{
	std::vector<Movie> copy_vector = this->entities;
	return copy_vector;
}
