#pragma once
#include "Repository_interface.h"
#include <string>
#include "Domain.h"

class File_repository : public Repository_interface
{
private:
	string filename;
	

public:
	vector<Movie> read_all_from_file();
	void write_all_to_file(vector<Movie> movies);
	
	File_repository(string filename) : filename{filename} {};
	
	int get_length() override;
	void add_entity(Movie movie) override;
	void delete_entity(Movie movie_key) override;
	void update_entity(Movie new_movie) override;
	Movie get_by_name(string name) override;
	std::vector<Movie> get_all() override;
	string get_filename();
};

