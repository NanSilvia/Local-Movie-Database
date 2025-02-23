#pragma once
#include "Repository.h"
#include "File_repository.h"
#include "HTML_repository.h"
#include "Validator_movie.h"
#include "Action.h"
#include <stack>


class Service {
	private:
		Repository_interface* repository;
		Repository_interface* watchlist;
		int current_position;
		Validator_movie* validator;

		stack<Action*> undo_actions;
		stack<Action*> redo_actions;

	public:
		Service(Repository_interface* repository, Repository_interface* watchlist, Validator_movie* validator) : repository{ repository }, watchlist{ watchlist }, current_position{ 0 }, validator{validator} {};
		~Service();
		void service_add_movie(string title, string genre, int year_of_release, int number_of_likes, string trailer);
		void service_delete_movie(string title);
		void service_update_movie(string title, string genre, int year_of_release, int number_of_likes, string trailer);
		void service_add_to_watchlist(string name);
		Movie service_get_first_movie_for_printing();
		Movie service_get_next_movie_for_printing();
		std::vector<Movie> get_all();
		std::vector<Movie> get_all_movies_from_watchlist();
		std::vector<Movie> get_filtered_movies(string genre, int minimum_number_of_likes);
		void initialize_repository(string filename);
		void initialize_watchlist(string filename);
		string get_filename();
		void service_undo();
		void service_redo();
};