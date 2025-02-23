#include "MoviesGUI.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "Validator_movie.h"
#include "Service.h"
#include "GUI.h"
#include "MoviesGUI.h"
#include <fstream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	Repository_interface* repository = new Repository{};
	Repository_interface* watchlist = new Repository{};

	ifstream configuration_file{"configuration.txt"};
	string line_repository;
	getline(configuration_file, line_repository);
	if (line_repository != "inmemory")
		repository = new File_repository{ line_repository };
	string line_watchlist;
	getline(configuration_file, line_watchlist);
	if (line_watchlist.substr(line_watchlist.find_last_of(".") + 1) == "html") {
		ofstream file(line_watchlist);
		file << "";
		file.close();
		watchlist = new HTML_repository(line_watchlist);
	}
	else if (line_watchlist.substr(line_watchlist.find_last_of(".") + 1) == "csv")
		watchlist = new File_repository(line_watchlist);

	Validator_movie* validator = new Validator_movie{};
	Service service{ repository, watchlist, validator };
	
	Mylist_table_model* model = new Mylist_table_model(watchlist);

	Secondary_window* secondary_window = new Secondary_window(model);

	MoviesGUI gui{service, model };

	gui.show();

	return a.exec();
}
