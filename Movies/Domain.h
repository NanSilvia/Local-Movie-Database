#pragma once
#include <string>

using namespace std;

class Movie {
	private:
		string title;
		string genre;
		int year_of_release;
		int number_of_likes;
		string trailer;
	public:
		Movie(string title = "", string genre = "", int year_of_release = 0, int number_of_likes = 0, string trailer = "");
		Movie(const Movie& movie);
		string get_title();
		string get_genre();
		int get_year_of_release();
		int get_number_of_likes();
		string get_trailer();

		void set_title(string new_title);
		void set_genre(string new_genre);
		void set_year_of_release(int new_year_of_release);
		void set_number_of_likes(int new_number_of_likes);
		void set_trailer(string new_trailer);

		bool operator==(const Movie& other);

		string print_format();
		friend std::istream& operator>>(std::istream& input_stream, Movie& movie);
		friend std::ostream& operator<<(std::ostream& output_stream, const Movie& movie);
};