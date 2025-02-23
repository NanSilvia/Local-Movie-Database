#pragma once
#include <vector>
#include "Domain.h"
class Repository_interface
{
public:
	virtual int get_length() = 0;
	virtual void add_entity(Movie movie) = 0;
	virtual void delete_entity(Movie movie_key) = 0;
	virtual void update_entity(Movie new_movie) = 0;
	virtual Movie get_by_name(string name) = 0;
	virtual std::vector<Movie> get_all() = 0;
	virtual string get_filename() { return ""; };
};

