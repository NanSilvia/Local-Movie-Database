#include "Action.h"

void Action_add::execute_undo()
{
	this->repository->delete_entity(this->added_movie);
}

void Action_add::execute_redo()
{
	this->repository->add_entity(this->added_movie);
}

void Action_delete::execute_undo()
{
	this->repository->add_entity(this->deleted_movie);
}

void Action_delete::execute_redo()
{
	this->repository->delete_entity(this->deleted_movie);
}

void Action_update::execute_undo()
{
	Movie movie = this->repository->get_by_name(this->updated_movie.get_title());
	this->repository->update_entity(this->updated_movie);
	this->updated_movie = movie;
}

void Action_update::execute_redo()
{
	Movie movie = this->repository->get_by_name(this->updated_movie.get_title());
	this->repository->update_entity(this->updated_movie);
	this->updated_movie = movie;
}
