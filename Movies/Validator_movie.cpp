#include "Validator_movie.h"
#define MINIMUM_WORD_SIZE 3

void Validator_movie::validate_movie(Movie& movie)
{
	string errors;
	if (movie.get_title().size() < MINIMUM_WORD_SIZE)
		errors += "invalid title\n";
	if (movie.get_genre().size() < MINIMUM_WORD_SIZE)
		errors += "invalid genre\n";
	if (movie.get_number_of_likes() < 0)
		errors += "invalid number of likes\n";
	if (movie.get_year_of_release() < 0)
		errors += "invalid year of release\n";
	if (movie.get_trailer().size() < MINIMUM_WORD_SIZE)
		errors += "invalid trailer\n";
	if (errors.size() > 0)
		throw Validation_exception(errors);
}
