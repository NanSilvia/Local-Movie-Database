#pragma once
#include "Dynamic_vector.h"
#include "Domain.h"
#include <vector>
#include "Repository_interface.h"
class Repository : public Repository_interface{
	private:
		std::vector<Movie> entities;
	public:
		Repository();
		int get_length() override;
		void add_entity(Movie movie) override;
		void delete_entity(Movie movie_key) override;
		void update_entity(Movie new_movie) override;
		Movie get_by_name(string name) override;
		std::vector<Movie> get_all() override;
};