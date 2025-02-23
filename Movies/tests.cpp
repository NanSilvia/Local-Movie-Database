#include "tests.h"
#include "Dynamic_vector.h"
#include "Domain.h"
#include "Repository.h"
#include "File_repository.h"
#include "Service.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void test_all()
{
	test__dynamic_vector();
	test__Movie();
	test__Repository();
	test__Service();
	test__File_repository();
	
}

void test__dynamic_vector()
{
	test__dynamic_vector_constructor__valid_capacity__dynamic_vector_created();
	test__get_length__valid_dynamic_vector__valid_length();
	test__add_element__valid_element__element_at_the_end_position();
	test__delete_element__element_in_dynamic_vector__element_not_it_dynamic_vector();
	test__update_element__movie_with_diferent_genre__movie_modified_in_dynamic_vector();
	test__resize__dynamic_vector__dynamic_vector_with_capacity_doubled();
	test__dynamic_vector_copy_constructor__valid_dynamic_vector__dynamic_vector_copy_created();
}



void test__dynamic_vector_constructor__valid_capacity__dynamic_vector_created()
{
	Dynamic_vector<int> dynamic_vector{ 2 };
	assert(dynamic_vector.get_length() == 0);
}

void test__get_length__valid_dynamic_vector__valid_length()
{
	Dynamic_vector<int> dynamic_vector;
	dynamic_vector.add_element(1);
	assert(dynamic_vector.get_length() == 1);
}

void test__add_element__valid_element__element_at_the_end_position()
{
	Dynamic_vector<int> dynamic_vector;
	dynamic_vector.add_element(5);
	assert(dynamic_vector[0] == 5);
}

void test__delete_element__element_in_dynamic_vector__element_not_it_dynamic_vector()
{
	Dynamic_vector<int> dynamic_vector;
	dynamic_vector.add_element(5);
	dynamic_vector.delete_element(5);
	assert(dynamic_vector.get_length() == 0);
}

void test__update_element__movie_with_diferent_genre__movie_modified_in_dynamic_vector()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	Movie movie_modified{ "asdf", "mare", 11111, 555, "par.mp4" };
	Dynamic_vector<Movie> dynamic_vector;
	dynamic_vector.add_element(movie);
	dynamic_vector.update_element(movie_modified);
	assert(dynamic_vector[0].get_genre() == movie_modified.get_genre());
}

void test__resize__dynamic_vector__dynamic_vector_with_capacity_doubled()
{
	Dynamic_vector<int> dynamic_vector{1};
	dynamic_vector.add_element(1);
	dynamic_vector.add_element(2);
	assert(dynamic_vector.get_capacity() == 2);
}

void test__dynamic_vector_copy_constructor__valid_dynamic_vector__dynamic_vector_copy_created()
{
	Dynamic_vector<int> dynamic_vector;
	dynamic_vector.add_element(1);
	dynamic_vector.add_element(2);
	Dynamic_vector<int> copy_vector{ dynamic_vector };
	assert(copy_vector[1] == 2);
}

void test__Movie() {
	test__get_title__valid_movie__valid_title();
	test__get_year_of_release__valid_movie__valid_year_of_release();
	test__get_number_of_likes__valid_movie__valid_number_of_likes();
	test__get_trailer__valid_movie__valid_trailer();
	test__set_title__valid_movie__valid_title();
	test__set_year_of_release__valid_movie__valid_year_of_release();
	test__set_number_of_likes__valid_movie__valid_number_of_likes();
	test__set_trailer__valid_movie__valid_trailer();
	test__set_genre__valid_movie__valid_genre();
	test__print_format__valid_movie__valid_printing_format();
	test__operator_insert__valid_ifstream__movie_read();
	test__operator_extraction__valid_ifstream__movie_read();
}

void test__get_title__valid_movie__valid_title()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	assert(movie.get_title() == "asdf");
}

void test__get_year_of_release__valid_movie__valid_year_of_release()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	assert(movie.get_year_of_release() == 1000);
}

void test__get_number_of_likes__valid_movie__valid_number_of_likes()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	assert(movie.get_number_of_likes() == 2222222);
}

void test__get_trailer__valid_movie__valid_trailer()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	assert(movie.get_trailer() == "asdf.mp4");
}

void test__set_title__valid_movie__valid_title()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	movie.set_title("asdff");
	assert(movie.get_title() == "asdff");
}

void test__set_year_of_release__valid_movie__valid_year_of_release()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	movie.set_year_of_release(1111);
	assert(movie.get_year_of_release() == 1111);
}

void test__set_number_of_likes__valid_movie__valid_number_of_likes()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	movie.set_number_of_likes(2);
	assert(movie.get_number_of_likes() == 2);
}

void test__set_trailer__valid_movie__valid_trailer()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	movie.set_trailer("broas");
	assert(movie.get_trailer() == "broas");
}

void test__set_genre__valid_movie__valid_genre()
{
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	movie.set_genre("broas");
	assert(movie.get_genre() == "broas");
}

void test__print_format__valid_movie__valid_printing_format()
{
	Movie movie{ "a", "s", 1, 2, "f.mp4" };
	assert(movie.print_format() == "a s 1 2 f.mp4");
}

void test__operator_extraction__valid_ifstream__movie_read()
{
	ifstream file("test.txt");
	Movie movie;
	file >> movie;
	file.close();
	assert(movie.get_genre() == "d");
}

void test__operator_insert__valid_ifstream__movie_read()
{
	ofstream file("test.txt");
	Movie movie_to_write{ "d","d",3,3,"d" }, movie_to_read{};
	file << movie_to_write;
	file.close();
	ifstream out("test.txt");
	out >> movie_to_read;
	out.close();
	assert(movie_to_read.get_genre() == movie_to_write.get_genre());
}

void test__Repository(){
	test__get_length__valid_repository__valid_length();
	test__add_entity__valid_entity__entity_at_the_end_position();
	test__delete_entity__entity_in_Repository__entity_not_it_Repository();
	test__update_entity__movie_with_diferent_genre__movie_modified_in_Repository();
	test__get_by_name__valid_name__movie_with_that_name();
}

void test__get_length__valid_repository__valid_length()
{
	Repository repository;
	assert(repository.get_length() == 0);
}

void test__add_entity__valid_entity__entity_at_the_end_position()
{
	Repository repository;
	Movie movie{ "a", "s", 1, 2, "f.mp4" };
	repository.add_entity(movie);
	assert(repository.get_length() == 1);
}



void test__delete_entity__entity_in_Repository__entity_not_it_Repository()
{
	Repository repository;
	Movie movie{ "a", "s", 1, 2, "f.mp4" };
	repository.add_entity(movie);
	repository.delete_entity(movie);
	assert(repository.get_length() == 0);
}

void test__update_entity__movie_with_diferent_genre__movie_modified_in_Repository()
{
	Repository repository;
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	Movie movie_modified{ "asdf", "mare", 11111, 555, "par.mp4" };
	repository.add_entity(movie);
	repository.update_entity(movie_modified);
	std::vector<Movie> movies = repository.get_all();
	assert(movies[0].get_trailer() == "par.mp4");
}

void test__get_by_name__valid_name__movie_with_that_name() {
	Repository repository;
	Movie movie{ "name", "asdfff", 1000, 2222222, "asdf.mp4" };
	repository.add_entity(movie);
	assert(repository.get_by_name("name") == movie);
}

void test__Service()
{
	test__service_add_entity__valid_entity__entity_at_the_end_position();
	test__service_delete_entity__entity_in_Service__entity_not_it_Service();
	test__service_update_entity__movie_with_diferent_genre__movie_modified_in_Service();
	test__service_add_to_watchlist__valid_movie__movie_at_the_end_of_watchlist();
	test__service_get_first_movie_for_printing__valid_service__first_movie_from_repository();
	test__service_get_next_movie_for_printing__current_position_smaller_than_number_of_movies__next_movie_from_repository();
	test__service_get_next_movie_for_printing__current_position_equal_to_number_of_movies__next_movie_from_repository();
	test__get_filtered_movies__valid_genre_and_number_of_likes__a_vector_of_filtered_movies();
	test__initialize_repository__filename__repository_initialized();
}


void test__service_add_entity__valid_entity__entity_at_the_end_position()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	service.service_add_movie("asdf", "asdfff", 1000, 2222222, "asdf.mp4");
	std::vector<Movie> movies = service.get_all();
	assert(movies[0].get_trailer() == "asdf.mp4");
}


void test__service_delete_entity__entity_in_Service__entity_not_it_Service()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	service.service_add_movie("asdf", "asdfff", 1000, 2222222, "asdf.mp4");
	service.service_delete_movie("asdf");
	std::vector<Movie> movies = service.get_all();
	assert(movies.size() == 0);
}

void test__service_update_entity__movie_with_diferent_genre__movie_modified_in_Service()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	service.service_add_movie("asdf", "asdfff", 1000, 2222222, "asdf.mp4");
	service.service_update_movie("asdf", "asdfff", 1000, 2222222, "par.mp4");
	std::vector<Movie> movies = service.get_all();
	assert(movies[0].get_trailer() == "par.mp4");
}

void test__service_add_to_watchlist__valid_movie__movie_at_the_end_of_watchlist()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	service.service_add_movie("asdf", "asdfff", 1000, 2222222, "asdf.mp4");
	service.service_add_to_watchlist("asdf");
	std::vector<Movie> movies = service.get_all_movies_from_watchlist();
	assert(movies[0].get_trailer() == "asdf.mp4");
}

void test__service_get_first_movie_for_printing__valid_service__first_movie_from_repository()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	Movie movie{ "asdf", "asdfff", 1000, 2222222, "asdf.mp4" };
	service.service_add_movie("asdf", "asdfff", 1000, 2222222, "asdf.mp4");
	Movie first_movie = service.service_get_first_movie_for_printing();
	assert(first_movie.get_trailer() == "asdf.mp4");
}

void test__service_get_next_movie_for_printing__current_position_smaller_than_number_of_movies__next_movie_from_repository()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	service.service_add_movie("asdfffff", "asdfff", 1000, 2222222, "asdf.mp4");
	service.service_add_movie("asdf", "asdfff", 1000, 2222222, "asdf.mp4");
	Movie next_movie = service.service_get_next_movie_for_printing();
	next_movie = service.service_get_next_movie_for_printing();
	assert(next_movie.get_title() == "asdf");
}

void test__service_get_next_movie_for_printing__current_position_equal_to_number_of_movies__next_movie_from_repository()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	service.service_add_movie("asdf", "asdfff", 1000, 2222222, "asdf.mp4");
	Movie next_movie = service.service_get_next_movie_for_printing();
	next_movie = service.service_get_next_movie_for_printing();
	assert(next_movie.get_title() == "asdf");
}

void test__get_filtered_movies__valid_genre_and_number_of_likes__a_vector_of_filtered_movies()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	service.service_add_movie("asdf", "asdfff", 1000, 1000, "asdf.mp4");
	service.service_add_movie("asdf", "asdfff", 5000, 5000, "asdf.mp4");
	vector<Movie> movies = service.get_filtered_movies("asdfff", 2000);
	assert(movies.size() == 1);
}


void test__initialize_repository__filename__repository_initialized()
{
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};
	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	service.initialize_repository("test.txt");
	service.service_add_movie("asdf", "asdfff", 5000, 5000, "asdf.mp4");
	vector<Movie> movies = service.get_all();
	Movie movie{ "d", "d" , 3, 3, "d" };
	assert(movies[0] == movie);
}

void test__File_repository()
{
	test__File_repository__get_length__valid_repository__valid_length();
	test__File_repository__delete_entity__valid_movie_key__movie_deleted();
	test__File_repository__update_entity__valid_movie_key__movie_deleted();
	test__File_repository__get_by_name__valid_name__movie_with_that_name();
}

void test__File_repository__get_length__valid_repository__valid_length()
{
	File_repository repository{ "test.txt" };
	assert(repository.get_length() == 2);
}

void test__File_repository__delete_entity__valid_movie_key__movie_deleted()
{
	File_repository repository{ "test.txt" };
	Movie movie{ "asdf","asdfff",5000,5000,"asdf.mp4" };
	repository.delete_entity(movie);
	assert(repository.get_length() == 1);
}

void test__File_repository__update_entity__valid_movie_key__movie_deleted()
{
	File_repository repository{ "test.txt" };
	Movie movie{ "d","dd",33,33,"dddd" };
	repository.update_entity(movie);
	assert(repository.get_all()[0] == movie);
}

void test__File_repository__get_by_name__valid_name__movie_with_that_name()
{
	File_repository repository{ "test.txt" };
	Movie movie = repository.get_by_name("d");
	assert(movie.get_genre() == "dd");
}




