#pragma once
#include "Repository_interface.h"
#include "Domain.h"

class Action
{
public:
	virtual void execute_undo() = 0;
	virtual void execute_redo() = 0;
};

class Action_add : public Action
{

private:
	Repository_interface* repository;
	Movie added_movie;

public:
	Action_add(Repository_interface* repository, const Movie& added_movie) : repository(repository), added_movie(added_movie) {}

	void execute_undo() override;
	void execute_redo() override;
};

class Action_delete : public Action
{

private:
	Repository_interface* repository;
	Movie deleted_movie;

public:
	Action_delete(Repository_interface* repository, const Movie& deleted_movie) : repository(repository), deleted_movie(deleted_movie) {}

	void execute_undo() override;
	void execute_redo() override;
};

class Action_update : public Action
{

private:
	Repository_interface* repository;
	Movie updated_movie;

public:
	Action_update(Repository_interface* repository, const Movie& updated_movie) : repository(repository), updated_movie(updated_movie) {}

	void execute_undo() override;
	void execute_redo() override;
};
