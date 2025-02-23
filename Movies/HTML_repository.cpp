#include "HTML_repository.h"
#include "custom_exceptions.h"
using namespace std;

vector<Movie> HTML_repository::read_all_from_file()
{
	string html_string{};
	ifstream input_stream(this->filename);
	while (!input_stream.eof()) {
		string line;
		getline(input_stream, line);
		html_string += line + "\n";
	}
	input_stream.close();
	regex base_regex("<td>(.*)</td>");
	vector<string> fields{};
	for (auto iterator = sregex_iterator(html_string.begin(), html_string.end(), base_regex);
		iterator != sregex_iterator(); ++iterator) {
		smatch matched = *iterator;
		string field = matched.str();
		field.erase(0, 4);	// sterge <td>
		field.erase(field.end() - 5, field.end()); // sterge </td>

		fields.push_back(field);
	}
	int ENTITY_FIELDS = 5;
	int TITLE_INDEX = 0, GENRE_INDEX = 1, YEAROFRELEASE_INDEX = 2, LIKES_INDEX = 3, TRAILER_INDEX = 4;
	vector<Movie> movies{};
	for (size_t i = 0; i < fields.size(); i += ENTITY_FIELDS)
		movies.push_back(Movie(fields[i + TITLE_INDEX], fields[i + GENRE_INDEX],
			stoi(fields[i + YEAROFRELEASE_INDEX]), std::stoi(fields[i + LIKES_INDEX]), fields[i + TRAILER_INDEX]));
	return movies;
}

void HTML_repository::write_all_to_file(vector<Movie> movies)
{
	string html_string{};
	html_string += "<!DOCTYPE html>\n";
	html_string += "\t<html>\n";
	html_string += "\t\t<head>\n";
	html_string += "\t\t\t<title>Movies</title>\n";
	html_string += "\t\t</head>\n";
	html_string += "\t<body>\n";
	html_string += "\t<table border=\"1\">\n";
	html_string += "\t<tr>\n";
	html_string += "\t\t<th>Title</th>\n";
	html_string += "\t\t<th>Genre</th>\n";
	html_string += "\t\t<th>YearOfRelease</th>\n";
	html_string += "\t\t<th>Likes</th>\n";
	html_string += "\t\t<th>Trailer</th>\n";
	html_string += "\t</tr>\n";
	for_each(movies.begin(), movies.end(), [&](Movie& movie) {
		html_string += "\t<tr>\n";
		html_string += "\t\t<td>" + movie.get_title() + "</td>\n";
		html_string += "\t\t<td>" + movie.get_genre() + "</td>\n";
		html_string += "\t\t<td>" + std::to_string(movie.get_year_of_release()) + "</td>\n";
		html_string += "\t\t<td>" + std::to_string(movie.get_number_of_likes()) + "</td>\n";
		html_string += "\t\t<td>" + movie.get_trailer() + "</td>\n";
		html_string += "\t</tr>\n";
		});
	html_string += "\t</table>\n";
	html_string += "\t</body>\n";
	html_string += "\t</html>\n";
	ofstream outputStream(this->filename);
	outputStream << html_string;
	outputStream.close();
}

void HTML_repository::add_entity(Movie movie)
{
	vector<Movie> movies = this->read_all_from_file();
	if (find(movies.begin(), movies.end(), movie) != movies.end())
		throw Repository_duplicate_exception("Duplicate element!\n");
	movies.push_back(movie);
	this->write_all_to_file(movies);
}

Movie HTML_repository::get_by_name(string name)
{
	return Movie();
}

std::vector<Movie> HTML_repository::get_all()
{
	return this->read_all_from_file();
}

string HTML_repository::get_filename()
{
	return this->filename;
}
