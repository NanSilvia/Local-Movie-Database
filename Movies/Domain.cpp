#include "Domain.h"
#include <vector>
#include <sstream>

using namespace std;


Movie::Movie(string title, string genre, int year_of_release, int number_of_likes, string trailer)
{
	this->title = title;
	this->genre = genre;
	this->year_of_release = year_of_release;
	this->number_of_likes = number_of_likes;
	this->trailer = trailer;
}

Movie::Movie(const Movie& movie)
{
	this->title = movie.title;
	this->genre = movie.genre;
	this->year_of_release = movie.year_of_release;
	this->number_of_likes = movie.number_of_likes;
	this->trailer = movie.trailer;
}

string Movie::get_title()
{
	return this->title;
}

string Movie::get_genre()
{
	return this->genre;
}

int Movie::get_year_of_release()
{
	return this->year_of_release;
}

int Movie::get_number_of_likes()
{
	return this->number_of_likes;
}

string Movie::get_trailer()
{
	return this->trailer;
}

void Movie::set_title(string new_title)
{
	this->title = new_title;
}

void Movie::set_genre(string new_genre)
{
	this->genre = new_genre;
}

void Movie::set_year_of_release(int new_year_of_release)
{
	this->year_of_release = new_year_of_release;
}

void Movie::set_number_of_likes(int new_number_of_likes)
{
	this->number_of_likes = new_number_of_likes;
}

void Movie::set_trailer(string new_trailer)
{
	this->trailer = new_trailer;
}

bool Movie::operator==(const Movie& other)
{
	return this->title == other.title;
}

string Movie::print_format()
{
	return this->title + " - " + this->genre + " - " + to_string(this->year_of_release) + " - " + to_string(this->number_of_likes) + " - " + this->trailer;
}

vector<string> split_into_words(string input, char delimiter)
{
	vector <string> result;
	stringstream ss(input);
	string variable;
	while (getline(ss, variable, delimiter))
		result.push_back(variable);

	return result;
}

std::istream& operator>>(std::istream& input_stream, Movie& movie)
{
	string line;
	getline(input_stream, line);
	vector<string> variables = split_into_words(line, ',');
	if (variables.size() != 5) // make sure all the starship data was valid
		return input_stream;
	movie.title = variables[0];
	movie.genre = variables[1];
	movie.year_of_release = stoi(variables[2]);
	movie.number_of_likes = stoi(variables[3]);
	movie.trailer = variables[4];
	return input_stream;
}

std::ostream& operator<<(std::ostream& output_stream, const Movie& movie)
{
	output_stream << movie.title + "," + movie.genre + "," + to_string(movie.year_of_release) + "," + to_string(movie.number_of_likes) + "," + movie.trailer + "\n";
	return output_stream;
}


